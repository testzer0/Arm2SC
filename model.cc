#include "model.h"
#include <stdlib.h>
#include <cstring>
#include <random>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <climits>

/**
 * random - Generates a uniformly randomly distributed integer in the
 * range [range_from, range_to], and returns it.
 */
int random(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);
    return distr(generator);
}


process::process(proc_t pid) : proc_id(pid)
{
	next_event_num = 1;
	finished = false;
	have_taken_wrong_branch = false;
	last_fetched_event = closest_aci_event = NULL;
	ins_tree_root = NULL;
	memset(closest_write, 0, MEMSIZE*sizeof(event *));
	memset(closest_reg_write, 0, NREGS*sizeof(event *));
	memset(regs, 0, NREGS*sizeof(uint32_t));
	closest_aci_event = NULL;
}

/**
 * add_event - Adds the event to the set of active events and 
 * returns its index in the active_events vector.
 */
int process::add_event(struct event *e) 
{
	int sz = active_events.size();
	e->index = sz;
	e->proc = proc_id;
	active_events.push_back(e);
	return sz;
}

/**
 * remove_event - removes an event from the set of active events and returns 
 * it. For O(1) execution, this may move around (and change the indices 
 * of) other events of the process. This should not need locking since only
 * one thread mutates a process' structures.
 */
int process::remove_event(struct event *e) 
{
	int last = active_events.size() - 1;
	int index = e->index;
	if (active_events[index] != e)					// Not just event_nums, but pointers should match
		return -1;
	e->index = -1;									// For safety
	if (index != last) {
		active_events[index] = active_events[last];	// Move last event to index
		active_events[index]->index = index;		// Update index of last
	}
	active_events.pop_back();						// Remove old copy of last in O(1)
	return 0;
}

//================ Helper Predicates ==============\\

bool process::all_dmb_lds(struct event *e)
{
	for (struct event *ev : active_events) {
		if (ev->ins_type == DMBLD && ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_dmb_sts(struct event *e)
{
	for (struct event *ev : active_events) {
		if (ev->ins_type == DMBST && ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_dmb_sys(struct event *e)
{
	for (struct event *ev : active_events) {
		if (ev->ins_type == DMBSY && ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_writes(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == ST || ev->ins_type == STL || ev->ins_type == STX || ev->ins_type == STLX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_reads(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == LD || ev->ins_type == LDA || ev->ins_type == LDX || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_syncs(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBSY || ev->ins_type == ISB) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_srels(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == STL || ev->ins_type == STLX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_lacq_init(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != INIT && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_lacqs(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}


bool process::all_mem(struct event *e)
{	
	// More efficient to use just one loop rather than compose all_reads and all_writes
	for (struct event *ev : active_events) {
		if ((ev->ins_type == LD || ev->ins_type == LDA || ev->ins_type == LDX || ev->ins_type == LDAX ||
			ev->ins_type == ST || ev->ins_type == STL || ev->ins_type == STX || ev->ins_type == STLX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::all_barriers(struct event *e)
{
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBLD || ev->ins_type == DMBST || ev->ins_type == DMBSY || ev->ins_type == ISB) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::init_cnd(struct event *e)
{
	// The data dependenies have been already determined 
	// when the instruction was fetched.

	for (struct event *ev : e->addr_dep) {
		if (ev->status != INIT && ev->status != COMMIT)
			return false;
	}
	for (struct event *ev : e->data_dep) {
		if (ev->status != INIT && ev->status != COMMIT)
			return false;
	}
	return true;
}

bool process::isb_cnd(struct event *e)
{
	if (e->ins_type != ISB)
		return false;

	// Now we need to make sure that all events have fully 
	// determined memory footprints

	for (struct event *ev : active_events) {
		if (ev->event_num >= e->event_num || ev->status == INIT || ev->status == COMMIT) 
			continue;	// Initialized and committed instructions surely have address deps inited/commited
		for (struct event *ev_addr : ev->addr_dep) {
			if (ev_addr->status != INIT && ev_addr->status != COMMIT)
				return false; 
		}
	}

	return true;
}

bool process::com_cnd(struct event *e)
{
	for (struct event *ev : e->addr_dep) {
		if (ev->status != COMMIT)
			return false;
	}
	for (struct event *ev : e->data_dep) {
		if (ev->status != COMMIT)
			return false;
	}
	if (e->ctrl_dep && e->ctrl_dep->status != COMMIT)
		return false;

	// Also need to check poloc dependency
	if (e->addr_final != 0xFFFFFFFF) {
		for (struct event *ev : active_events) {
			if (ev->event_num < e->event_num && 
				ev->addr_final == e->addr_final && ev->status != COMMIT)
				return false;
		}
	}

	return true;
}

bool process::valid_cnd(struct event *e)
{
	if (e->ins_type != ACI)
		return false;

	// Truth value is stored in e->result (1 if TRUE, 0 if FALSE)
	uint32_t lookfor = e->event_num + 1; // look for the next fetched event
	for (struct event *ev : active_events) {
		if (ev->event_num == lookfor) {
			struct instruction *inse = e->instr, *insev = ev->instr;
			if (e->result && inse->childl != insev ||
				(!e->result) && inse->childr != insev) {
				// we _did_ fetch an event after the ACI, but it's the wrong one
				have_taken_wrong_branch = true;
				return false;
			}
		}
	}

	// Either the next instruction has not been fetched yet, or
	// has been fetched correctly.
	return true;
}

//================ Helper predicates end and compond predicates begin  ===========\\

bool process::nonacq_read_init_cnd(struct event *e)
{
	// all_syncs, all_dmb_lds, all_lacq_init
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBLD || ev->ins_type == DMBSY || ev->ins_type == ISB) &&
		 ev->event_num < e->event_num && e->status != COMMIT)		
			return false;											// all_syncs and all_dmb_lds
		else if ((ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != INIT && e->status != COMMIT)
			return false;											// all_lacq_init
	}
	return true;
}

bool process::acq_read_init_cnd(struct event *e)
{
	// all_syncs, all_srels, all_dmb_lds, all_lacq_init
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBLD || ev->ins_type == DMBSY || ev->ins_type == ISB || ev->ins_type == STL ||
			ev->ins_type == STLX) && ev->event_num < e->event_num && e->status != COMMIT)		
			return false;											// all_syncs, all_srels and all_dmb_lds
		else if ((ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != INIT && e->status != COMMIT)
			return false;											// all_lacq_init
	}
	return true;
}

bool process::st_init_cnd(struct event *e)
{
	// all_syncs, all_dmb_lds, all_dmb_sts and all_lacqs
	// also init cnd. 
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBLD || ev->ins_type == DMBST || ev->ins_type == DMBSY || ev->ins_type == ISB ||
			ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return init_cnd(e);
}

bool process::stl_init_cnd(struct event *e)
{
	// all_syncs, all_dmb_lds, all_dmb_sts and all_mem
	// also init cnd. Basically everything other than aci
	for (struct event *ev : active_events) {
		if ((ev->ins_type != ACI) && ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	// If the above holds, all po-preceeding events that write to registers are for
	// sure committed, so init_cnd should surely hold. So I think we can skip the check.
	// return init_cnd(e);
	return true;
}

bool process::read_com_cnd(struct event *e)
{
	// Just a wrapper
	return all_syncs(e) && com_cnd(e);
}

bool process::non_exc_write_com_cnd(struct event *e)
{
	// Just a wrapper
	return all_syncs(e) && com_cnd(e);
}

bool process::stx_com_cnd(struct event *e)
{
	// all_syncs, all_dmb_lds, all_lacqs, all_dmb_sts, all_syncs and com_cnd
	// also need init_cnd to ensure that data is available
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBLD || ev->ins_type == DMBST || ev->ins_type == DMBSY || ev->ins_type == ISB ||
			ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return com_cnd(e);
}

bool process::stlx_com_cnd(struct event *e)
{
	// all_syncs, all_dmb_lds, all_mem, all_dmb_sts, all_syncs and com_cnd
	// for com_cnd, we need the most recent aci to have been committed which
	// in turn needs the next-prev aci to have been committed and so on
	// all_aci + all_mem + all_barriers = all instructions
	// stlx needs everything that is po-before to be committed
	for (struct event *ev : active_events) {
		if ( ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::isb_com_cnd(struct event *e)
{
	// all_dmb_sy, isb_cnd and com_cnd
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBSY) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return com_cnd(e) && isb_cnd(e);
}

bool process::dmb_ld_com_cnd(struct event *e)
{
	// all_dmb_sy, all_reads and com_cnd
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBSY || ev->ins_type == LD || ev->ins_type == LDX ||
			ev->ins_type == LDA || ev->ins_type == LDAX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return com_cnd(e);
}

bool process::dmb_st_com_cnd(struct event *e)
{
	// all_dmb_sy, all_writes and com_cnd
	for (struct event *ev : active_events) {
		if ((ev->ins_type == DMBSY || ev->ins_type == ST || ev->ins_type == STX ||
			ev->ins_type == STL || ev->ins_type == STLX) &&
		 ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return com_cnd(e);
}

bool process::dmb_sy_com_cnd(struct event *e)
{
	// all_mem, all_barriers and all_aci from com_cnd - everything
	// that's po-before.
	for (struct event *ev : active_events) {
		if (ev->event_num < e->event_num && e->status != COMMIT)
			return false;
	}
	return true;
}

bool process::aci_com_cnd(struct event *e)
{
	// just a wrapper
	return valid_cnd(e) && all_syncs(e) && com_cnd(e);
}

bool process::assign_init_cnd(struct event *e)
{
	return st_init_cnd(e);
}

bool process::assign_com_cnd(struct event *e)
{
	return non_exc_write_com_cnd(e);
}

//================= Compound predicates end ===============\\

/**
 * fetch_next_instr - fetch an instruction.
 * Returns a pointer to the new event if successful, and 
 * returns NULL on failure.
 */
struct event *process::fetch_next_instr(struct instruction *next_ins)
{
	// verify that next_ins is in max_i
	if (max_i[0] != next_ins && max_i[1] != next_ins)
		return NULL;

	// if the previous instruction has been committed and is an aci
	// check that the value is consistent
	if (last_fetched_event && last_fetched_event->ins_type == ACI && last_fetched_event->status == COMMIT) {
		if (last_fetched_event->result && max_i[0] != next_ins ||
			!(last_fetched_event->result) && max_i[1] != next_ins)
			return NULL;
	}

	// First update max_i and finished	
	max_i[0] = next_ins->childl;
	max_i[1] = next_ins->childr;	// NULL for non-ACI instructions

	// Create an event for this instruction
	struct event *e = (struct event *)malloc_to_calloc(sizeof(event));
	if (!e) {
		std::cerr << "malloc_to_calloc() failed for event!" << std::endl;
		exit(-1);
	}

	// Fill in the basic metadata of e
	e->event_num = next_event_num++;
	e->ins_type = next_ins->ins_type;
	e->instr = next_ins;
	e->proc = proc_id;
	e->status = FETCH;

	// At this stage, we _may_ know the result of the instruction (if
	// the value is a literal). However, we dont *need* to mark it as known
	// until the instruction is initialized. Hence we defer it until then.
	// We DO, however, need to find the registers that are used (if any)
	// and deduce the addr, data and ctrl dependencies. This will also depend
	// on the type of instruction e is.
	// Finding these registers requires that find_read_write_regs have been 
	// already called for e as well as all po-preceeding instructions.

	// Mark result and addr values as unknown/un-needed
	e->result = e->addr_final = 0xFFFFFFFF;

	event *ev;

	// Find all address dependencies
	for (uint32_t reg : next_ins->regs_addr) {
		if (!(ev = closest_reg_write[reg])) 		// No write to the register yet
			continue; 
		// The closest reg write is always different for
		// every register since a single instruction writes to 
		// at most one register.
		e->addr_dep.push_back(ev);
	}

	// Find all data dependencies
	for (uint32_t reg : next_ins->regs_data) {
		if (!(ev = closest_reg_write[reg])) 		// No write to the register yet
			continue;
		// The closest reg write is always different for
		// every register since a single instruction writes to 
		// at most one register.
		e->addr_dep.push_back(ev);
	}

	e->ctrl_dep = closest_aci_event;				// Control dependency
	e->rf = NULL;									// We don't know yet

	// Update the closest_* values
	// closest_write cannot be updated yet, since we may not
	// know the address to which we write.
	if (next_ins->reg_written != 0xFFFFFFFF)
		closest_reg_write[e->instr->reg_written] = e;

	if (e->ins_type == ACI)
		closest_aci_event = e;

	add_event(e);
	last_fetched_event = e;
	return e;
}

/**
 * fetch_next_instr_nondet - Non-deterministically fetches one of the instructions from 
 * max_i, adds it to the event list, and then updates max_i for the next fetch.
 * Returns the pointer to the fetched event, which is NULL if everything has been 
 * fetched.
 */
struct event *process::fetch_next_instr_nondet()
{
	if (max_i[0] == NULL && max_i[1] == NULL)
		return NULL;
	struct instruction *next_ins;

	// if we have more than one possibility (we must have two then)
	// then check to see whether their parent(which must exist)
	// has been committed: if so, we really only have one option
	if (!last_fetched_event || last_fetched_event->ins_type != ACI) {
		next_ins = max_i[0];		
	} else if (last_fetched_event->status == COMMIT) {
		if (last_fetched_event->result)
			next_ins = max_i[0];
		else
			next_ins = max_i[1];
	} else {
		int ind = random(0,1);
		next_ins = max_i[ind];
	}

	// First update max_i and finished	
	max_i[0] = next_ins->childl;
	max_i[1] = next_ins->childr;	// NULL for non-ACI instructions

	// Create an event for this instruction
	struct event *e = (struct event *)malloc_to_calloc(sizeof(event));
	if (!e) {
		std::cerr << "malloc_to_calloc() failed for event!" << std::endl;
		exit(-1);
	}

	// Fill in the basic metadata of e
	e->event_num = next_event_num++;
	e->ins_type = next_ins->ins_type;
	e->instr = next_ins;
	e->proc = proc_id;
	e->status = FETCH;

	// At this stage, we _may_ know the result of the instruction (if
	// the value is a literal). However, we dont *need* to mark it as known
	// until the instruction is initialized. Hence we defer it until then.
	// We DO, however, need to find the registers that are used (if any)
	// and deduce the addr, data and ctrl dependencies. This will also depend
	// on the type of instruction e is.
	// Finding these registers requires that find_read_write_regs have been 
	// already called for e as well as all po-preceeding instructions.

	// Mark result and addr values as unknown/un-needed
	e->result = e->addr_final = 0xFFFFFFFF;

	event *ev;

	// Find all address dependencies
	for (uint32_t reg : next_ins->regs_addr) {
		if (!(ev = closest_reg_write[reg])) 		// No write to the register yet
			continue; 
		// The closest reg write is always different for
		// every register since a single instruction writes to 
		// at most one register.
		e->addr_dep.push_back(ev);
	}

	// Find all data dependencies
	for (uint32_t reg : next_ins->regs_data) {
		if (!(ev = closest_reg_write[reg])) 		// No write to the register yet
			continue;
		// The closest reg write is always different for
		// every register since a single instruction writes to 
		// at most one register.
		e->data_dep.push_back(ev);
	}

	e->ctrl_dep = closest_aci_event;				// Control dependency
	e->rf = NULL;									// We don't know yet

	// Update the closest_* values
	// closest_write cannot be updated yet, since we may not
	// know the address to which we write.
	if (next_ins->reg_written != 0xFFFFFFFF)
		closest_reg_write[e->instr->reg_written] = e;

	if (e->ins_type == ACI)
		closest_aci_event = e;

	add_event(e);
	last_fetched_event = e;

	#ifdef DEBUG
		std::cout << proc_id << " " << "FETCH " << e->instr->instr_id << " TYPE " << e->ins_type << std::endl;
	#endif

	return e;
}

/**
 * try_resolving_addresses - tries to resolve addresses for those
 * memory instruction whose address has not yet been resolved. Should
 * be called after every transition. 
 * IMPORTANT: Also updates closest_write.
 */
void process::try_resolving_addresses()
{
	for (struct event *e : active_events) {
		if (e->addr_final != 0xFFFFFFFF)
			continue;
		if (e->ins_type == LD || e->ins_type == LDA || e->ins_type == LDX || e->ins_type == LDAX) {
			try_to_resolve_address(e, this);
		} else if (e->ins_type == ST || e->ins_type == STL || e->ins_type == STX || e->ins_type == STLX) {
			if (try_to_resolve_address(e, this)) {
				if ((!closest_write[e->addr_final]) || closest_write[e->addr_final]->event_num < e->event_num)
					closest_write[e->addr_final] = e;
			}
		}
	}
}

/**
 * get_closest_write - returns the latest write that writes to the
 * same location that e writes to/reads from. You MUST have called
 * try_resolving_addresses before calling this function. May miss
 * cases like these:
 * 1) r1 <- 2
 * 2) r2 <- 2
 * 3) [r1] <- 3
 * 4) r3 <- [r2]
 * Here it could be the case that r2 has been resolved but not r1, and hence 
 * we may miss (3) when trying to get the closest write of (4). It is pending
 * to check if this aligns with the Flat Model.
 */
inline struct event *process::get_closest_write(struct event *e)
{
	if ((e->addr_final) == 0xFFFFFFFF) {
		std::cerr << "get_closest_write: event has no address!" << std::endl;
		exit(-1);
	}
	if (!closest_write[e->addr_final] || closest_write[e->addr_final]->event_num < e->event_num)
		return closest_write[e->addr_final]; 

	// if we are here, the closest write seen so far is _after_ e
	// search for a write _before_ e: its okay if none is found, that just means that
	// the closest write before e has committed
	struct event *ev = NULL;
	for (struct event *evc : active_events) {
		if (evc->addr_final == e->addr_final && evc->event_num < e->event_num) {
			if (!ev || ev->event_num < evc->event_num)
				ev = evc;
		}
	}

	// return the closest write found
	return ev;
}

/**
 * init_nonacq_read - tries to initialize a non-acquire 
 * event e. Returns 0xFFFFFFFF if e is incompatible or
 * any condition is not satisfied. Otherwise returns e's
 * event_num on success.
 */
uint32_t process::init_nonacq_read(struct event *e)
{
	if (!e || e->status != FETCH || (e->ins_type != LD && e->ins_type != LDX) || e->addr_final == 0xFFFFFFFF) {
		return 0xFFFFFFFF;
	} 

	// verify necessary conditions 
	if (!nonacq_read_init_cnd(e))
		return 0xFFFFFFFF;

	// try_resolving_addresses should have been called BEFORE
	// calling any init/commit functions
	event *ev;
	if ((ev = get_closest_write(e)) && ev->status == INIT) { 	// Have a local event to read from
		e->rf = ev;
		e->result = ev->result;
	} else if (!ev || ev->status == COMMIT) {					// Must read from global event
		e->rf = read_global_memory(e->addr_final, proc_id);
		e->result = e->rf->result;
	} else 														// CW is still in FECTH phase
		return 0xFFFFFFFF;

	// successful
	e->status = INIT;
	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << ' ' << " LD/LDX INIT RESULT " << e->result << endl;
	#endif
	return e->event_num;
}

/**
 * init_nonacq_read - tries to initialize a non-acquire 
 * event e. Returns 0xFFFFFFFF if e is incompatible or
 * any condition is not satisfied. Otherwise returns e's
 * event_num on success.
 */
uint32_t process::init_acq_read(struct event *e)
{
	if (!e || e->status != FETCH || (e->ins_type != LDA && e->ins_type != LDAX) || e->addr_final == 0xFFFFFFFF) {
		return 0xFFFFFFFF;
	} 

	// verify necessary conditions 
	if (!acq_read_init_cnd(e))
		return 0xFFFFFFFF;

	// try_resolving_addresses should have been called BEFORE
	// calling any init/commit functions
	event *ev;
	if ((ev = get_closest_write(e)) && ev->status == INIT) { 	// Have a local event to read from
		e->rf = ev;
		e->result = ev->result;
	} else if (!ev || e->status == COMMIT) {					// Must read from global event
		e->rf = read_global_memory(e->addr_final, proc_id);
		e->result = e->rf->result;
	} else 														// CW is still in FECTH phase
		return 0xFFFFFFFF;

	// successful
	e->status = INIT;
	return e->event_num;
}


/**
 * com_read - commit a read event.
 * returns 0xFFFFFFFF if the commit failed, and otherwise
 * returns e's event_num on success.
 */
uint32_t process::com_read(struct event *e)
{
	if (e->ins_type == LD || e->ins_type == LDA) {
		if(!read_com_cnd(e))
			return 0xFFFFFFFF;
	} else if (e->ins_type == LDX || e->ins_type == LDAX) {
		if(!read_com_cnd(e))
			return 0xFFFFFFFF;
		update_mark(e->addr_final, e);				// failure of update_mark != failure of commit
	} else 
		return 0xFFFFFFFF;

	// successful
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around

	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << ' ' << " READ COM RESULT " << e->result << endl;
	#endif

	return e->event_num;
}


/**
 * init_st - initialize store event 
 * if some condition isn't satisfied or some 
 * dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns e->event_num.
 */
uint32_t process::init_st(struct event *e)
{
	if (e->ins_type != ST || e->addr_final == 0xFFFFFFFF || e->status != FETCH)
		return 0xFFFFFFFF;
	if (!st_init_cnd(e))
		return 0xFFFFFFFF;

	// since init_cnd passed, we should be able to evaluate
	// the data dependency
	// NOTE: the addr should have already been resolved by a call
	// to try_resolving_addresses BEFORE calling this function.
	// If not done, the address 0xFFFFFFFF will cause issues.

	// first gather the register values
	uint32_t regvals[NREGS] = {0};
	memcpy(regvals, regs, NREGS*sizeof(uint32_t));

	for (struct event *ev : e->data_dep) {
		if (ev->ins_type == STX || ev->ins_type == STLX)
			regvals[ev->instr->reg_written] = ev->exc_success;
		else
			regvals[ev->instr->reg_written] = ev->result;
	}

	// resolve the result
	e->result = evaluate_exp(e->instr->operand2, regvals);
	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << " ST INIT RESULT " << e->result << endl;
	#endif

	// mark as initialized
	e->status = INIT;
	return e->event_num;
}


/**
 * init_stl - initialize store-release event 
 * If some condition isn't satisfied or some 
 * dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns e->event_num.
 */
uint32_t process::init_stl(struct event *e)
{
	if (e->ins_type != STL || e->addr_final == 0xFFFFFFFF || e->status != FETCH)
		return 0xFFFFFFFF;
	if (!stl_init_cnd(e))
		return 0xFFFFFFFF;

	// since init_cnd passed, we should be able to evaluate
	// the data dependency
	// NOTE: the addr should have already been resolved by a call
	// to try_resolving_addresses BEFORE calling this function.
	// If not done, the address 0xFFFFFFFF will cause issues.

	// first gather the register values
	uint32_t regvals[NREGS] = {0};
	memcpy(regvals, regs, NREGS*sizeof(uint32_t));
	for (struct event *ev : e->data_dep) {
		if (ev->ins_type == STX || ev->ins_type == STLX)
			regvals[ev->instr->reg_written] = ev->exc_success;
		else
			regvals[ev->instr->reg_written] = ev->result;
	}

	// resolve the result
	e->result = evaluate_exp(e->instr->operand2, regvals);

	// mark as initialized
	e->status = INIT;

	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << ' ' << " STL INIT RESULT " << e->result << endl;
	#endif

	return e->event_num;
}


/**
 * com_non_exc_write - commit non-exclusive write 
 * If some condition isn't satisfied or some 
 * dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns e->event_num.
 */
uint32_t process::com_non_exc_write(struct event *e)
{
	if ((e->ins_type != ST && e->ins_type != STL) || e->status != INIT)
		return 0xFFFFFFFF;
	if (!non_exc_write_com_cnd(e))
		return 0xFFFFFFFF;

	// mark as committed _before_ updating main memory
	e->status = COMMIT;

	// update main memory with propagated write
	write_global_memory(e->addr_final, e);

	remove_event(e);								// Once committed, no need to keep around

	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << ' ' << " ASSIGN INIT RESULT " << e->result << endl;
	#endif

	return e->event_num;
}


/**
 * com_stx - try to commit an STX event. If some condition
 * is not met, returns 0xFFFFFFFF. Otherwise returns e's
 * event_num. Also updates e's exc_success to indicate whether
 * the exclusive store succeeded.
 */
uint32_t process::com_stx(struct event *e)
{
	if (e->ins_type != STX || e->status != FETCH || e->addr_final == 0xFFFFFFFF)
		return 0xFFFFFFFF;

	if (!stx_com_cnd(e))
		return 0xFFFFFFFF;

	// first gather the register values
	uint32_t regvals[NREGS] = {0};
	memcpy(regvals, regs, NREGS*sizeof(uint32_t));
	for (struct event *ev : e->data_dep) {
		if (ev->ins_type == STX || ev->ins_type == STLX)
			regvals[ev->instr->reg_written] = ev->exc_success;
		else
			regvals[ev->instr->reg_written] = ev->result;
	}

	// resolve the result
	e->result = evaluate_exp(e->instr->operand2, regvals);

	// mark e as committed _before_ updating main memory
	// this is OK since this process is controlled by a single thread
	// We do this since we don't want some other process to read the main
	// memory and check if we are committed for some reason.
	e->status = COMMIT;

	// update global memory and use it to write e->exc_success
	// 0 should be written if successful
	e->exc_success =  !(write_global_memory(e->addr_final, e));

	remove_event(e);								// Once committed, no need to keep around

	return e->event_num;
}


/**
 * com_stlx - try to commit an STLX event. If some condition
 * is not met, returns 0xFFFFFFFF. Otherwise returns e's
 * event_num. Also updates e's exc_success to indicate whether
 * the exclusive store succeeded.
 */
uint32_t process::com_stlx(struct event *e)
{
	if (e->ins_type != STLX || e->status != FETCH || e->addr_final == 0xFFFFFFFF)
		return 0xFFFFFFFF;

	if (!stlx_com_cnd(e))
		return 0xFFFFFFFF;

	// first gather the register values
	uint32_t regvals[NREGS] = {0};
	memcpy(regvals, regs, NREGS*sizeof(uint32_t));
	for (struct event *ev : e->data_dep) {
		if (ev->ins_type == STX || ev->ins_type == STLX)
			regvals[ev->instr->reg_written] = ev->exc_success;
		else
			regvals[ev->instr->reg_written] = ev->result;
	}

	// resolve the result
	e->result = evaluate_exp(e->instr->operand2, regvals);

	// mark e as committed _before_ updating main memory
	// this is OK since this process is controlled by a single thread
	// We do this since we don't want some other process to read the main
	// memory and check if we are committed for some reason.
	e->status = COMMIT;

	// update global memory and use it to write e->exc_success
	// 0 should be written if successful
	e->exc_success =  !(write_global_memory(e->addr_final, e));

	remove_event(e);								// Once committed, no need to keep around

	return e->event_num;
}

/**
 * com_isb - try to commit an isb event.
 * Returns 0xFFFFFFFF on failure, and the event_num
 * of e on success.
 */
uint32_t process::com_isb(struct event *e)
{
	if (e->ins_type != ISB || e->status != FETCH)
		return 0xFFFFFFFF;

	if (!isb_com_cnd(e))
		return 0xFFFFFFFF;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}


/**
 * com_dmb_ld - try to commit a DMBLD event.
 * Returns 0xFFFFFFFF on failure, and the event_num
 * of e on success.
 */
uint32_t process::com_dmb_ld(struct event *e)
{
	if (e->ins_type != DMBLD || e->status != FETCH)
		return 0xFFFFFFFF;

	if (!dmb_ld_com_cnd(e))
		return 0xFFFFFFFF;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}


/**
 * com_dmb_st - try to commit a DMBST event.
 * Returns 0xFFFFFFFF on failure, and the event_num
 * of e on success.
 */
uint32_t process::com_dmb_st(struct event *e)
{
	if (e->ins_type != DMBST || e->status != FETCH)
		return 0xFFFFFFFF;

	if (!dmb_st_com_cnd(e))
		return 0xFFFFFFFF;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}


/**
 * com_dmb_sy - try to commit a DMBSY event.
 * Returns 0xFFFFFFFF on failure, and the event_num
 * of e on success.
 */
uint32_t process::com_dmb_sy(struct event *e)
{
	if (e->ins_type != DMBSY || e->status != FETCH)
		return 0xFFFFFFFF;

	if (!dmb_sy_com_cnd(e))
		return 0xFFFFFFFF;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}


/**
 * com_aci - try to commit an ACI event.
 * Returns 0xFFFFFFFF on failure and e->event_num on success.
 */
uint32_t process::com_aci(struct event *e)
{
	if (e->ins_type != ACI || e->status != FETCH)
		return 0xFFFFFFFF;

	// Evaluate the truth value of the aci instruction
	// first gather the register values
	uint32_t regvals[NREGS] = {0};
	memcpy(regvals, regs, NREGS*sizeof(uint32_t));
	for (struct event *ev : e->data_dep) {
		if (ev->ins_type == STX || ev->ins_type == STLX)
			regvals[ev->instr->reg_written] = ev->exc_success;
		else
			regvals[ev->instr->reg_written] = ev->result;
	}
	uint32_t l = evaluate_exp(e->instr->operand1, regvals), r = evaluate_exp(e->instr->operand2, regvals);
	switch (e->instr->optype) {
	case EQ:
		e->result = (l == r);
		break;
	case NEQ:
		e->result = !(l == r);
		break;
	case GEQ:
		e->result = (l >= r);
		break;
	case LEQ:
		e->result = (l <= r);
		break;
	case XOR:
		e->result = l ^ r;
		break;
	default:
		e->result = 0;
	}

	if (!aci_com_cnd(e)) {
		// we should probably check if the wrong branch was taken, and 
		// if so, abort the run.
		// Later probably we should change this to call some function that restarts 
		// the run, but for now exiting is OK.
		return 0xFFFFFFFF;
	}

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around

	#ifdef DEBUG
		std::cout << proc_id << ' ' << e->instr->instr_id << " ACI COM" << std::endl;
	#endif

	return e->event_num;
}

/**
 * com_term - try to commit a TERM event.
 * @e - The event. Pass NULL if the function should
 * search for it.
 *
 * Succeeds only if every other event has been committed. 
 * Also sets the finished flag if successful.
 * Returns 0xFFFFFFFF on failure, and e's event_num if successful.
 */
uint32_t process::com_term(struct event *e)
{
	if (!e) {
		for (struct event *ev : active_events) {
			if (ev->ins_type == TERM) {
				e = ev;
				break;
			}
		}
	}

	if (!e)
		return 0xFFFFFFFF;

	for (struct event *ev : active_events) {
		if (e != ev && ev->status != COMMIT) {
			return 0xFFFFFFFF;
		}
	}

	e->status = COMMIT;
	finished = true;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}

/**
 * take_next_possible_transition - takes whatever next possible
 * transition there is for e to take. If there is none, returns
 * 0xFFFFFFFF. Otherwise returns e's event_num
 */
uint32_t process::take_next_possible_transition(struct event *e)
{
	if (e->status == COMMIT)
		return 0xFFFFFFFF;
	switch (e->ins_type) {
	case LD:
	case LDX:
		if (e->status == FETCH) 
			return init_nonacq_read(e);
		else 
			return com_read(e);
	case LDA:
	case LDAX:
		if (e->status == FETCH)
			return init_acq_read(e);
		else
			return com_read(e);
	case ST:
		if (e->status == FETCH)
			return init_st(e);
		else
			return com_non_exc_write(e);
	case STL:
		if (e->status == FETCH)
			return init_stl(e);
		else
			return com_non_exc_write(e);
	case STX:
		return com_stx(e);
	case STLX:
		return com_stlx(e);
	case ASSIGN:
		if (e->status == FETCH)
			return init_assign(e);
		else
			return com_assign(e);
	case DMBLD:
		return com_dmb_ld(e);
	case DMBST:
		return com_dmb_st(e);
	case DMBSY:
		return com_dmb_sy(e);
	case ISB:
		return com_isb(e);
	case ACI:
		return com_aci(e);
	case TERM:
		return com_term(e);
	} 

	return 0xFFFFFFFF;
}

/**
 * init_assign - initialize assign event 
 * if some condition isn't satisfied or some 
 * dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns e->event_num.
 */
uint32_t process::init_assign(struct event *e)
{
	if (e->ins_type != ASSIGN || e->status != FETCH)
		return 0xFFFFFFFF;
	if (!assign_init_cnd(e))
		return 0xFFFFFFFF;

	// since init_cnd passed, we should be able to evaluate
	// the data dependency
	// NOTE: the addr should have already been resolved by a call
	// to try_resolving_addresses BEFORE calling this function.
	// If not done, the address 0xFFFFFFFF will cause issues.

	// first gather the register values
	uint32_t regvals[NREGS] = {0};
	memcpy(regvals, regs, NREGS*sizeof(uint32_t));

	for (struct event *ev : e->data_dep) {
		if (ev->ins_type == STX || ev->ins_type == STLX)
			regvals[ev->instr->reg_written] = ev->exc_success;
		else
			regvals[ev->instr->reg_written] = ev->result;
	}

	// resolve the result
	e->result = evaluate_exp(e->instr->operand2, regvals);
	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << ' ' << " ASSIGN INIT RESULT " << e->result << endl;
	#endif

	// mark as initialized
	e->status = INIT;
	return e->event_num;
}

/**
 * com_non_exc_write - commit assign 
 * If some condition isn't satisfied or some 
 * dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns e->event_num.
 */
uint32_t process::com_assign(struct event *e)
{
	if (e->ins_type != ASSIGN || e->status != INIT)
		return 0xFFFFFFFF;
	if (!assign_com_cnd(e))
		return 0xFFFFFFFF;

	// mark as committed
	e->status = COMMIT;

	remove_event(e);								// Once committed, no need to keep around

	#ifdef DEBUG
		cout << proc_id << " " << e->instr->instr_id << ' ' << " ASSIGN COM RESULT " << e->result << endl;
	#endif

	return e->event_num;
}


/**
 * random_execution - takes a random execution path.
 * The final values of the registers are filled into
 * regs_to_fill.
 */
void process::random_execution(struct random_execution_args *args)
{
	uint32_t *regs_to_fill = args->regs_to_fill;
	double fetch_prob = args->fetch_prob;

	std::string codefile = std::string(args->testname) + "_" + to_string(proc_id) + "_code.model";

	read_in_code(codefile.c_str());

	uint32_t res;
	string msg;

	vector<struct event *> events;
	events.push_back(NULL);						// dummy event
	bool allfetched = false;
	struct event *e;
	while (!finished) {
		if (have_taken_wrong_branch)
			return;
		try_resolving_addresses();
		if (active_events.size() && (allfetched || (double)random(1,INT_MAX) > (fetch_prob*INT_MAX))) {
			int ind = random(0, active_events.size()-1);
			res = take_next_possible_transition(active_events[ind]);
		} else {
			if ((e = fetch_next_instr_nondet()))
				events.push_back(e);
			else {
				allfetched = true;
				continue;
			}
		}
	}
	// fill in the register values
	for (int i = 0; i < NREGS; i++)
		regs_to_fill[i] = regs[i];
	bool filled[NREGS] = {0};
	for (int i = events.size()-1; i >= 1; i--) {
		e = events[i];
		if (e->instr->reg_written == 0xFFFFFFFF || filled[e->instr->reg_written])
			continue;
		else {
			regs_to_fill[e->instr->reg_written] = (e->ins_type == STX || e->ins_type == STLX)?
				e->exc_success : e->result;
			filled[e->instr->reg_written] = true;
		}
	}
}

void process::read_in_code(const char *filename)
{
	std::ifstream infile(filename);
	std::string t1, t2, t3, t4, t5, t6, t7;
	int v1, v2, v3, v4, v5, v6, v7;

	// initial register assignments
	while (true) {
		infile >> t1;
		if (t1 == "REGDONE")
			break;
		// if we are here, t1 must be REGASSIGN
		assert(t1 == "REGASSIGN");
		infile >> t2 >> t3;
		v2 = std::stoi(t2);
		v3 = std::stoi(t3);
		assert(v2 >= 0 && v2 < NREGS);
		regs[v2] = (uint32_t)v3;
	}

	vector<struct instruction **> tofill;				// pointers which need to be filled
	vector<std::string> labels;							// label names to help fill them
	vector<std::string> label_instr;					// separate label list for label-to-instr map
	vector<struct instruction *> instrs;				// corresponding instructions

	// read in the code
	// for now, since it has not been clearly decided how to translate the CMP+BEQ
	// statements to ACI, we don't handle them [TODO]
	bool seenterm = false, havelabel;
	struct instruction *last = NULL, *cur;
	uint32_t instr_id = 1;
	std::string label;
	while (!seenterm) {
		havelabel = false;
		infile >> t1;

		if (t1 == "LABEL") {
			// this signifies no new instruction, but that we must mark the next instruction with the
			// given label
			infile >> label;
			havelabel = true;
			// read next line's first word into t1
			infile >> t1;
		}

		cur = (struct instruction *)malloc_to_calloc(sizeof(struct instruction));
		cur->instr_id = instr_id++;
		cur->parent = last;									// NOTE: change after including ACI
		cur->childl = cur->childr = NULL;
		cur->operand1 = cur->operand2 = NULL;
		if (last) {
			// if last is BEQ, then the child should be childr, else childl
			// the way to check this is to check whether the last ins was an ACI
			if (last->ins_type == ACI)
				last->childr = cur;
			else
				last->childl = cur;
		}
		else {
			ins_tree_root = cur;
			max_i[0] = cur;
		}

		/* 
		 * For now, all the litmus tests use registers or literal values: none has any complicated
		 * expressions. Further, since we aren't parsing ACI instructions for now, every parsed instr
		 * is a child of the previous one. This needs to be changed later. [TODO]
		 */
		if (t1 == "LD") {
			infile >> t2 >> t3;
			// t2 has to be reg
			infile >> t4 >> t5;
			
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand1->right = NULL;

			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->ins_type = LD;
			if (t4 == "REG")
				cur->operand2->type = REG;
			else													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 == "ST") {
			infile >> t2 >> t3;
			infile >> t4 >> t5;
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->ins_type = ST;
			if (t2 == "REG")
				cur->operand1->type = REG;
			else 													// NUM
				cur->operand1->type = VAL;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand2->right = NULL;
			if (t4 == "REG") 
				cur->operand2->type = REG;
			else 													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 =="LDA") {
			infile >> t2 >> t3;
			// t2 has to be reg
			infile >> t4 >> t5;
			
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand1->right = NULL;

			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->ins_type = LDA;
			if (t4 == "REG")
				cur->operand2->type = REG;
			else													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 =="STL") {
			infile >> t2 >> t3;
			infile >> t4 >> t5;
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));							// doesn't write any regs
			cur->ins_type = STL;
			if (t2 == "REG")
				cur->operand1->type = REG;
			else 													// NUM
				cur->operand1->type = VAL;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand2->right = NULL;
			if (t4 == "REG") 
				cur->operand2->type = REG;
			else 													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 =="LDX") {
			infile >> t2 >> t3;
			// t2 has to be reg
			infile >> t4 >> t5;

			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand1->right = NULL;

			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->ins_type = LDX;
			if (t4 == "REG")
				cur->operand2->type = REG;
			else													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 == "STX") {
			infile >> t2 >> t3;										// t2 has to be REG
			infile >> t4 >> t5;
			infile >> t6 >> t7;
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->reg_for_exc_st = (uint32_t)stoi(t3);					// success/failure written here
			cur->ins_type = STX;
			if (t4 == "REG")
				cur->operand1->type = REG;
			else 													// NUM
				cur->operand1->type = VAL;
			cur->operand1->value = (uint32_t)stoi(t5);
			cur->operand1->left = cur->operand2->right = NULL;
			if (t6 == "REG") 
				cur->operand2->type = REG;
			else 													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t7);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 =="LDAX") {
			infile >> t2 >> t3;
			// t2 has to be reg
			infile >> t4 >> t5;
			
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand1->right = NULL;

			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->ins_type = LDAX;
			if (t4 == "REG")
				cur->operand2->type = REG;
			else													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 == "STLX") {
			infile >> t2 >> t3;										// t2 has to be REG
			infile >> t4 >> t5;
			infile >> t6 >> t7;
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->reg_for_exc_st = (uint32_t)stoi(t3);					// success/failure written here
			cur->ins_type = STLX;
			if (t4 == "REG")
				cur->operand1->type = REG;
			else 													// NUM
				cur->operand1->type = VAL;
			cur->operand1->value = (uint32_t)stoi(t5);
			cur->operand1->left = cur->operand2->right = NULL;
			if (t6 == "REG") 
				cur->operand2->type = REG;
			else 													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t7);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 == "ASSIGN") {
			cur->ins_type = ASSIGN;
			infile >> t2 >> t3;
			// t2 must be reg
			infile >> t4 >> t5;
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand1->value = (uint32_t)stoi(t3);
			cur->operand1->left = cur->operand1->right = NULL;

			if (t4 == "REG")
				cur->operand2->type = REG;
			else													// NUM
				cur->operand2->type = VAL;
			cur->operand2->value = (uint32_t)stoi(t5);
			cur->operand2->left = cur->operand2->right = NULL;
		} else if (t1 == "DMBLD") {
			cur->operand1 = NULL;
			cur->operand2 = NULL;
			cur->ins_type = DMBLD;
		} else if (t1 == "DMBST") {
			cur->operand1 = NULL;
			cur->operand2 = NULL;
			cur->ins_type = DMBST;
		} else if (t1 == "DMBSY") {
			cur->operand1 = NULL;
			cur->operand2 = NULL;
			cur->ins_type = DMBSY;
		} else if (t1 == "ISB") {
			cur->operand1 = NULL;
			cur->operand2 = NULL;
			cur->ins_type = ISB;
		} else if (t1 == "TERM") {
			cur->operand1 = NULL;
			cur->operand2 = NULL;
			cur->ins_type = TERM;
			seenterm = true;
		} else if (t1 == "BEQ") {
			// is an ACI statement
			cur->ins_type = ACI;
			infile >> t2;						// label to jump to
			// the python script has made sure that the operands are now r0 and r1
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->left = cur->operand1->right = NULL;
			cur->operand2->left = cur->operand2->right = NULL;
			cur->operand1->type = cur->operand2->type = REG;
			cur->operand1->value = 0;
			cur->operand2->value = 1;
			cur->optype = EQ;

			// mark cur->childl as needing the result of the read label
			tofill.push_back(&cur->childl);
			labels.push_back(t2);
		} else if (t1 == "EOR") {
			// exclusive OR; treat like an assign
			cur->ins_type = ASSIGN;
			infile >> t2 >> t3;	// t2 must be an assign
			infile >> t4 >> t5;
			infile >> t6 >> t7;
			v3 = (uint32_t)stoi(t3);
			v5 = (uint32_t)stoi(t5);
			v7 = (uint32_t)stoi(t7);
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand1->left = cur->operand1->right = NULL;
			cur->operand2->type = OP;
			cur->operand2->op = XOR;
			cur->operand2->left = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2->right = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2->left->left = cur->operand2->left->right = cur->operand2->right->left = 
				cur->operand2->right->right = NULL;
			cur->operand1->value = v3;
			cur->operand2->left->value = v5;
			cur->operand2->right->value = v7;
			cur->operand2->left->type = (t4 == "REG")? REG : VAL;
			cur->operand2->right->type = (t6 == "REG")? REG : VAL;
		} else if (t1 == "CBZ") {
			// branch if zero
			cur->ins_type = ACI;
			infile >> t2 >> t3; 	// t2 is REG
			infile >> t4; 			// the label
			v3 = (uint32_t)stoi(t3);
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand2->type = VAL;
			cur->operand1->value = v3;
			cur->operand2->value = 0;
			cur->operand1->left = cur->operand1->right = cur->operand2->left = cur->operand2->right = NULL;
			cur->optype = EQ;

			tofill.push_back(&cur->childl);
			labels.push_back(t4);
		} else if (t1 == "CBNZ") {
			// branch if zero
			cur->ins_type = ACI;
			infile >> t2 >> t3; 	// t2 is REG
			infile >> t4; 			// the label
			v3 = (uint32_t)stoi(t3);
			cur->operand1 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand2 = (struct op_parse_tree_node *)malloc_to_calloc(sizeof(struct op_parse_tree_node));
			cur->operand1->type = REG;
			cur->operand2->type = VAL;
			cur->operand1->value = v3;
			cur->operand2->value = 0;
			cur->operand1->left = cur->operand1->right = cur->operand2->left = cur->operand2->right = NULL;
			cur->optype = NEQ;

			tofill.push_back(&cur->childl);
			labels.push_back(t4);
		}

		fill_read_write_regs(cur);
		last = cur;

		if (havelabel) {
			label_instr.push_back(label);
			instrs.push_back(cur);
		}
	}

	// fill in the labels;
	for (int i = 0; i < label_instr.size(); i++) {
		for (int j = 0; j < labels.size(); j++) {
			if (label_instr[i] == labels[j]) {
				// the instr at j needs lchild from instr i
				*tofill[j] = instrs[i];
			}
		}
	}
}

// Global functions start

/**
 * get_register_deps - returns a vector of register IDs
 * which list the registers occuring in the expression
 * formed by the (sub)tree rooted at the node
 */
vector<uint32_t> get_register_deps(struct op_parse_tree_node *n)
{
	if (!n || n->type == VAL)
		return vector<uint32_t>();
	if (n->type == REG) 
		return vector<uint32_t>{n->value};
	vector<uint32_t> v1 = get_register_deps(n->left), v2 = get_register_deps(n->right);
	for (uint32_t val : v2) {
		if (std::find(v1.begin(), v1.end(), val) == v1.end())	// if it isn't there yet
			v1.push_back(val);
	}
	return v1;
}

/**
 * fill_read_write_regs - finds the registers read and written by ins
 * and updates its metadata to reflect that. This serves as a useful
 * cache since these are accessed often.
 */
void fill_read_write_regs(struct instruction *ins)
{
	ins->reg_written = 0xFFFFFFFF;							// initialize to 0xFFFFFFFF

	switch(ins->ins_type) {
	case LD:
	case LDA:
	case LDX:
	case LDAX:
		ins->regs_addr = get_register_deps(ins->operand2); 	// addr deps
		// No data deps
		assert(ins->operand1 != NULL);
		ins->reg_written = ins->operand1->value;			// regs written
		break;
	case STX:
	case STLX:
		ins->reg_written = ins->reg_for_exc_st;				// regs written
	case ST:
	case STL:
		ins->regs_addr = get_register_deps(ins->operand1); 	// addr deps
		ins->regs_data = get_register_deps(ins->operand2);	// data deps
		break;
	case ASSIGN:
		ins->regs_data = get_register_deps(ins->operand2);
		ins->reg_written = ins->operand1->value;
		break;
	case ACI:		
		// Should we allow 2 operands? allowing for now
		// data deps from both operands
		ins->regs_data = get_register_deps(ins->operand1);
		vector<uint32_t> to_merge = get_register_deps(ins->operand2);
		for (uint32_t val : to_merge) {						
			if (std::find(ins->regs_data.begin(), ins->regs_data.end(), val) == ins->regs_data.end())
				ins->regs_data.push_back(val);
		}
	}
}

/**
 * try_to_resolve_address - try to find the address to which e
 * writes or from which e reads. DONT call this for non loads/stores.
 * Also avoid calling for instructions whose addr is already determined,
 * i.e. whose addr_final is != 0xFFFFFFFF.
 */
inline bool try_to_resolve_address(struct event *e, struct process *proc)
{
	bool alldone = true;
	uint32_t vals[NREGS] = {0};
	memcpy(vals, proc->regs, NREGS*sizeof(uint32_t));
	for (event *ev : e->addr_dep) {
		if (ev->result == 0xFFFFFFFF) 							// not yet inited
			return false;
		if (ev->ins_type == STX || ev->ins_type == STLX)		// these have the truth value in exc_success
			vals[ev->instr->reg_written] = ev->exc_success;
		else													// these have their result in result
			vals[ev->instr->reg_written] = ev->result;
	}

	// If we reach here, all addr dependencies have been resolved
	// Bad things may happen if this is called for non-stores/loads

	e->addr_final = (e->ins_type == LD || e->ins_type == LDA || e->ins_type == LDX || e->ins_type == LDAX)?
		evaluate_exp(e->instr->operand2, vals) : evaluate_exp(e->instr->operand1, vals);
	return true;
}

/**
 * evaluate_exp - evaluate an expression given the values of registers
 */
uint32_t evaluate_exp(struct op_parse_tree_node *n, uint32_t regvals[NREGS])
{
	if (!n)
		return 0;
	if (n->type == VAL)
		return n->value;
	if (n->type == REG)
		return regvals[n->value];

	uint32_t l = evaluate_exp(n->left, regvals), r = evaluate_exp(n->right, regvals), val = 0;
	switch(n->op) {
	case PLUS:
		val = l+r;
		break;
	case MINUS:
		val = l-r;
		break;
	case MULT:
		val = l*r;
		break;
	case EQ:
		val = !!(l == r);
		break;
	case NEQ:
		val = !(l == r);
		break;
	case GEQ:
		val = !!(l >= r);
		break;
	case LEQ:
		val = !!(l <= r);
	case XOR:
		val = l ^ r;
		break;
	}

	return val;
}

/**
 * read_global_memory - reads global memory and returns the value
 * at index. If is_exc is set, marks the location with our proc_id
 */
inline event *read_global_memory(uint32_t index, uint32_t proc_id)
{
	std::lock_guard<std::mutex> guard(global_mutex);
	#ifdef DEBUG
		cout << proc_id << " READING " << global_memory[index]->result << " FROM " << index << endl;
	#endif
	return global_memory[index];
}

/**
 * write_global_memory - writes to global memory. May fail
 * for store exclusives. Also updates mark. Returns the
 * success indicator.
 */
inline bool write_global_memory(uint32_t index, struct event *e)
{
	std::lock_guard<std::mutex> guard(global_mutex);
	// if e is a store-exclusive, then we should check
	// whether it should succeed
	#ifdef DEBUG
		cout << e->proc << " WRITING " << e->result << " TO " << index << endl;
	#endif
	assert(e);
	if ((e->ins_type == STX || e->ins_type == STLX) && mark[index] != e->proc)
		return false;
	// go ahead with the operation and update flags
	global_memory[index] = e;
	mark[index] = BOT; 					// location has been clobbered
	return true;
}

/**
 * update_mark - update the global mark using the
 * event e. Updates the mark of the global memory if e's rf
 * is the same as the current latest event propagated to memory
 * for that location. Should be called while committing exclusive 
 * reads. Returns the success value.
 */
inline bool update_mark(uint32_t index, event *e)
{
	std::lock_guard<std::mutex> guard(global_mutex);
	// if the event last propagated to memory is e's
	// rf, then update the mark
	if (e->rf == global_memory[index]) {
		mark[index] = e->proc;
		return true;
	}
	return false;
}

/**
 * Clean up local and global state.
 * Not yet decided whether it should be per-process or global,
 * or even what it should do.
 */
void cleanup() {
	/* Does nothing for now */
}

/**
 * Initializes global memory with all values 0,
 * with a dummy event. Also initializes number of processes
 */
void init_global_memory(const char *filename)
{
	struct event *e = (struct event *)malloc_to_calloc(sizeof(struct event));
	e->event_num = 0xFFFFFFFF;
	e->instr = NULL;
	e->status = COMMIT;
	e->result = 0;
	e->addr_final = 0xFFFFFFFF;
	for (int i = 0; i < MEMSIZE; i++)
		global_memory[i] = e;

	if (!filename)
		return;

	std::ifstream infile(filename);
	std::string t1, t2, t3, t4;
	int v1, v2, v3, v4;

	infile >> t1;
	nproc = stoi(t1);

	while (true) {
		infile >> t1;
		if (t1 == "DONE")
			break;
		// if we are here, t1 must be NUM
		infile >> t2 >> t3 >> t4;
		assert(t1 == "NUM" && t3 == "VALUE");
		v2 = std::stoi(t2);
		v4 = std::stoi(t4);
		
		// create a dummy event that writes to this address
		e = (struct event *)malloc_to_calloc(sizeof(struct event));
		e->event_num = 0xFFFFFFFF;
		e->instr = NULL;
		e->status = COMMIT;
		e->result = v4;
		e->addr_final = v2;
		global_memory[v2] = e;
	}
}

/**
 * check_final_conditions - checks whether the conditions in
 * @filename are true, given @process_regs, which is an array
 * whose nproc members are pointers to arrays of length NREGS giving
 * the final values of registers.
 */
bool check_final_conditions(const char *filename, uint32_t **process_regs)
{
	std::ifstream infile(filename);
	std::string t1, t2, t3, t4;
	int v1, v2, v3, v4;

	bool holds = true;

	while (true) {
		infile >> t1;
		if (t1 == "DONE")
			break;
		else if (t1 == "GLOBAL") {
			infile >> t2 >> t3;
			v2 = stoi(t2);								// address
			v3 = stoi(t3); 								// value

			if (!global_memory[v2]) {
				if (v3) {
					holds = false;
					break;
				}
			} else {
				if (v3 != global_memory[v2]->result) {
					holds = false;
					break;
				}
			}

		} else {										// LOCAL
			infile >> t2 >> t3 >> t4;
			v2 = stoi(t2);								// process
			v3 = stoi(t3); 								// reg no
			v4 = stoi(t4); 								// value

			if (process_regs[v2][v3] != v4) {
				// check whether the process even had code which wrote to
				// this register. If so, then the check failed
				if (processes[v2].closest_reg_write[v3]) {
					holds = false;
					break;
				}
			}
		}
	}

	return holds;
}

void *random_execution_wrapper(void *args)
{
	struct random_execution_args *pargs =(struct random_execution_args *)args;

	processes[pargs->which_process].random_execution(pargs);
	return NULL;
}

/**
 * main - The main function.
 * Does nothing for now, except initialize the randomizer
 */
int main(int argc, char **argv)
{
	srand(time(NULL));
	std::string s1, s2, s3, s4, pref="cctests/";
	if (argc > 1) {
		if (argc > 2) {
			s1 = std::string(argv[2]);
			if (s1 == "-other")
				pref = "other_cctests/";
			else if (s1 == "-n")
				pref = std::string(argv[3]) + "/";
		}
		s1 = std::string(argv[1]); 
	} else {
		s1 = "2+2W";
	}
	
	s2 = pref + s1;
	s3 = s2 + "_init.model";
	s4 = s2 + "_conditions.model";
	
	init_global_memory(s3.c_str());

	uint32_t **fregs = (uint32_t **)malloc_to_calloc(nproc * sizeof(uint32_t *));
	for (int i = 0; i < nproc; i++) {
		fregs[i] = (uint32_t *)malloc_to_calloc(NREGS * sizeof(uint32_t));
		processes.push_back(process(i));
	}

	pthread_t tids[nproc];
	const char *testname = s2.c_str();

	for (int i = 0; i < nproc; i++) {
		struct random_execution_args *args = 
			(struct random_execution_args *)malloc_to_calloc(sizeof(struct random_execution_args));
		args->regs_to_fill = fregs[i];
		args->testname = testname;
		args->fetch_prob = 0.7;
		args->which_process = i;
		if (pthread_create(&tids[i], NULL, random_execution_wrapper, (void *)args)) {
			std::cerr << "pthread_create failed!" << std::endl;
			exit(-1);
		}
	}

	for (int i = 0; i < nproc; i++) {
		pthread_join(tids[i], NULL);
		if (processes[i].have_taken_wrong_branch) {
			std::cout << "unsatisfied\n";
			return 0;
		}
	}

	#ifdef DEBUG
		cout << global_memory[2]->result << ' ' << global_memory[3]->result << endl;
	#endif

	if (check_final_conditions(s4.c_str(), fregs))
		std::cout << "satisfied\n";
	else 
		std::cout << "unsatisfied\n";

	return 0;
}