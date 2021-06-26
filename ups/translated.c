#define NPROC 2
#ifndef NPROC
#define NPROC 2
#endif

#define NREGS 16
#define ADDRSIZE 64
#define NINS 20
#define NTIME 45
#define ASSUME(stmt) __CPROVER_assume(stmt)
#define ASSERT(stmt) __CPROVER_assert(stmt, "Assert error")

// instruction types
#define LD 1
#define LDA 2
#define LDX 3
#define LDAX 4
#define ST 5
#define STL 6
#define STX 7
#define STLX 8
#define ASSIGN 9
#define DMBSY 10
#define ISB 11
#define DMBLD 12
#define DMBST 13
#define LABEL 14
#define ACI 15
#define TERM 16

// status
#define FETCH 1
#define INIT 2
#define COMMIT 3

// type of operands
#define NUM 1
#define REG 2
#define EMPTY 3 	// only one operand -> second is EMPTY

// operations
#define ADD 1
#define SUB 2
#define MULT 3
#define EOR 4
#define EQ 5
#define NEQ 6
#define GEQ 7
#define LEQ 8


#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; })

int __get_rng();
int get_rng(int from, int to)
{
    int ret = __get_rng();
    ASSUME(ret >= from && ret <= to);
    return ret;
}

int get_decision()
{
	return get_rng(0,1);
}

#include <pthread.h>

int memory[ADDRSIZE] = {0};
int mark[ADDRSIZE];
// specific initializations will be taken care of by the py script.
pthread_mutex_t mutex;

void init_memory_random()
{
	// use if need to init memory with random values
	int i;
	for (i = 0; i < ADDRSIZE; i++)
		memory[i] = __get_rng();
}

void init_mark_pre()
{
	int i;
	for (i = 0; i < ADDRSIZE; i++)
		mark[i] = -1;
}

void init_memory_and_reg_other();		// defined by py script

int read_memory(int addr, int should_mark)
{
	// should_mark = -1 if NO
	int ret;
pthread_mutex_lock(&mutex);
	if (should_mark >= 0)
		mark[addr] = -1;
	ret = memory[addr];
pthread_mutex_unlock(&mutex);
	return ret;
}

int write_memory(int addr, int value, int should_check)
{
	// should_check = -1 if NO
	// success -> 0, failure -> 1
	int ret;
pthread_mutex_lock(&mutex);
	if (should_check >= 0 && mark[addr] != should_check) {
		ret = 1;
	} else {
		ret = 0;
		memory[addr] = value;
		mark[addr] = -1;
	}
pthread_mutex_unlock(&mutex);
	return ret;
}

struct proc_local_info{
	// We have thread-local stuff here
	int p;								// number of the process
	int registers[NREGS];				// the initial value of registers
	int events[NTIME];					// events
	int type[NINS];						// type of instr
	int status[NTIME];					// status of events
	int o1[NINS], o2[NINS], o3[NINS];	// operands
	int t1[NINS], t2[NINS], t3[NINS];	// types
	int reg_written[NTIME];				// the register written by the event
	int memory_written[NTIME];			// the address written by the event
	int memory_read[NTIME];				// the address read by the event
	int memory_write_val[NTIME];		// value written to memory by the event
	int reg_write_val[NTIME];			// value written to the register
	int next1[NINS], next2[NINS];		// next instructions' indices
	int operation[NINS];				// operations of instr
	int cur_fill;						// next index for an event to be filled in
	int done;							// whether all transitions are done
	int finished;						// done AND final register values have been written
	int allfetched;						// whether all instructions have been fetched
};

struct proc_local_info procs[NPROC];

// initializing function for remaining fields
// of proc_local_info will be added by python script.
void init_proc_local_info_pre(struct proc_local_info *p)
{
	p->cur_fill = 0;
	p->done = p->finished = p->allfetched = 0;
	int i;
	for (i = 0; i < NTIME; i++) {
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	}
	for (i = 0; i < NREGS; i++)
		p->registers[i] = 0;	// specific ones done by py script
}

void init_procs();

void init_all_procs_pre()
{
	int i;
	for (i = 0; i < NPROC; i++) {
		procs[i].p = i;
		init_proc_local_info_pre(&procs[i]);
	}
}

void check_conditions();	// defined by py script

void fetch_next_instr(struct proc_local_info *p)
{
	int next_ins, index, type, ins_ind;

	if (p->cur_fill) {
		ins_ind = p->events[p->cur_fill-1];
		type = p->type[ins_ind];

		if (type != ACI)
			next_ins = p->next1[ins_ind];
		else if (p->status[ins_ind] == COMMIT) {
			if (p->reg_write_val[ins_ind])
				next_ins = p->next1[ins_ind];
			else
				next_ins = p->next2[ins_ind];
		} else {
			if (get_decision())
				next_ins = p->next1[ins_ind];
			else
				next_ins = p->next2[ins_ind];
		}
	} else {
		next_ins = 0;
	}

	index = p->cur_fill++;
	type = p->type[next_ins];

	ASSUME(index < NTIME);

	p->status[index] = FETCH;
	p->events[index] = next_ins;

	// reg written
	if (type == ST || type == STL || type >= DMBSY)
		p->reg_written[index] = -1;
	else
		p->reg_written[index] = p->o1[next_ins];	// true for all LD, ST*X, and ASSIGNs

	if (type == TERM)
		p->allfetched = 1;
}

void init_ST(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, ir, irprime, rval, rprimeval;
	int i, in, t, s;
	int mr, mw;

	ins = p->events[ev];
	ASSUME(p->type[ins] == ST && p->status[ev] == FETCH);
	rprime = p->o1[ins];
	r = p->o2[ins];

	rval = p->registers[r];
	rprimeval = p->registers[rprime];
	ir = 1;
	irprime = 1;
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];
		// iW >= cDY, cISB, cDS, cDL
		// iW >= cL
		if ((t >= DMBSY && t <= DMBST) || t == LDA || t == LDAX)
			ASSUME(s == COMMIT);
		if (p->reg_written[i] == r) {
			ir = (s >= INIT);
			rval = p->reg_write_val[i];
		} else if (p->reg_written[i] == rprime) {
			irprime = (s >= INIT);
			rprimeval = p->reg_write_val[i];
		}
	}
	// iW >= iReg(r), iReg(rprime)
	ASSUME(ir && irprime);

	// now we can init
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;
	p->status[ev] = INIT;

	// However, check that no coherence order violation has
	// taken place.
	for (i = 0; i < NTIME; i++) {
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
			continue;
		if (i >= p->cur_fill)	// don't look beyond the last event
			break;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
			break;
	}
}

void commit_ST(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, cr, irprime, addr;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == ST && p->status[ev] == INIT);
	rprime = p->o1[ins];
	r = p->o2[ins];

	cr = 1;
	irprime = 1;
	addr = p->memory_written[ev];

	// all po-prev ins's should have well defined memory footprints (cW >= iAddr)
	int undef[NREGS] = {0};
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		if (t <= STLX) {
			int reg;
			if (t <= LDAX || t > STL)
				reg = p->o2[i];
			else
				reg = p->o1[i];
			// cW >= iAddr
			ASSUME(!undef[reg]);
			// cW >= old-cW, cR
			if (p->registers[reg] == addr)
				ASSUME(s == COMMIT);
		} else if (t == ACI) {
			// cW >= ctrl
			ASSUME(s == COMMIT);
		}

		if (p->reg_written[i] == r)
			cr = (s == COMMIT);
		else if (p->reg_written[i] == rprime)
			irprime = (s >= INIT);

		if (p->reg_written[i] != -1)
			undef[NREGS] = (s == FETCH);
	}
	// cW >= cReg(r), iReg(rprime)
	ASSUME(cr && irprime);

	// update memory and then mark as committed
	write_memory(p->memory_written[ev],p->memory_write_val[ev],-1);
	p->status[ev] = COMMIT;
}

void init_STL(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, ir, irprime, rval, rprimeval;
	int i, in, t, s;
	int mr, mw;

	ins = p->events[ev];
	ASSUME(p->type[ins] == STL && p->status[ev] == FETCH);
	rprime = p->o1[ins];
	r = p->o2[ins];

	rval = p->registers[r];
	rprimeval = p->registers[rprime];
	ir = 1;
	irprime = 1;
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];
		// iW >= cDY, cISB, cDS, cDL
		// iW >= cR, cW
		if ((t <= DMBST) && t != ASSIGN)
			ASSUME(s == COMMIT);
		if (p->reg_written[i] == r) {
			ir = (s >= INIT);
			rval = p->reg_write_val[i];
		} else if (p->reg_written[i] == rprime) {
			irprime = (s >= INIT);
			rprimeval = p->reg_write_val[i];
		}
	}
	// iW >= iReg(r), iReg(rprime)
	ASSUME(ir && irprime);

	// now we can init
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;
	p->status[ev] = INIT;

	// However, check that no coherence order violation has
	// taken place.
	for (i = 0; i < NTIME; i++) {
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
			continue;
		if (i >= p->cur_fill)	// don't look beyond the last event
			break;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
			break;
	}
}

void commit_STL(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, cr, irprime, addr;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == STL && p->status[ev] == INIT);
	rprime = p->o1[ins];
	r = p->o2[ins];

	cr = 1;
	irprime = 1;
	addr = p->memory_written[ev];

	// all po-prev ins's should have well defined memory footprints (cW >= iAddr)
	int undef[NREGS] = {0};
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		if (t <= STLX) {
			int reg;
			if (t <= LDAX || t > STL)
				reg = p->o2[i];
			else
				reg = p->o1[i];
			// cW >= iAddr
			ASSUME(!undef[reg]);
			// cW >= old-cW, cR
			if (p->registers[reg] == addr)
				ASSUME(s == COMMIT);
		} else if (t == ACI) {
			// cW >= ctrl
			ASSUME(s == COMMIT);
		}

		if (p->reg_written[i] == r)
			cr = (s == COMMIT);
		else if (p->reg_written[i] == rprime)
			irprime = (s >= INIT);

		if (p->reg_written[i] != -1)
			undef[NREGS] = (s == FETCH);
	}
	// cW >= cReg(r), iReg(rprime)
	ASSUME(cr && irprime);

	// update memory and then mark as committed
	write_memory(p->memory_written[ev],p->memory_write_val[ev],-1);
	p->status[ev] = COMMIT;
}

void commit_STX(struct proc_local_info *p, int ev)
{
	int ins, rdoubleprime, rprime, r, cr, irprime, rval, rprimeval;
	int i, in, t, s;
	int mr, mw;

	ins = p->events[ev];
	ASSUME(p->type[ins] == STX && p->status[ev] == FETCH);
	rdoubleprime = p->o1[ins];
	rprime = p->o2[ins];
	r = p->o3[ins];

	rval = p->registers[r];
	rprimeval = p->registers[rprime];
	cr = 1;
	irprime = 1;
	// all po-prev ins's should have well defined memory footprints (cW >= iAddr)
	int undef[NREGS] = {0};
	for (int i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		if (p->reg_written[i] == r) {
			cr = (s == COMMIT);
			rval = p->reg_write_val[i];
		} else if (p->reg_written[i] == rprime) {
			irprime = (s >= INIT);
			rprimeval = p->reg_write_val[i];
		}
	}
	// cW >= cReg(r), iReg(rprime)
	ASSUME(cr && irprime);

	// now we know the addr and memory value
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;

	// use them in checks
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];
		// cW >= cDY, cISB, cDS, cDL
		// cW >= cL
		if ((t >= DMBSY && t <= DMBST) || t == LDA || t == LDAX)
			ASSUME(s == COMMIT);

		if (t <= STLX) {
			int reg;
			if (t <= LDAX || t > STL)
				reg = p->o2[i];
			else
				reg = p->o1[i];
			// cW >= iAddr
			ASSUME(!undef[reg]);
			// cW >= old-cW, cR
			if (p->registers[reg] == rprimeval)
				ASSUME(s == COMMIT);
		} else if (t == ACI) {
			// cW >= ctrl
			ASSUME(s == COMMIT);
		}

		if (p->reg_written[i] != -1)
			undef[NREGS] = (s == FETCH);
	}

	// now we can commit
	p->reg_write_val[ev] = write_memory(rprimeval, rval, p->p);
	p->status[ev] = COMMIT;

	// However, check that no coherence order violation has
	// taken place.
	for (i = 0; i < NTIME; i++) {
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
			continue;
		if (i >= p->cur_fill)	// don't look beyond the last event
			break;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
			break;
	}
}

void commit_STLX(struct proc_local_info *p, int ev)
{
	int ins, rdoubleprime, rprime, r, cr, irprime, rval, rprimeval;
	int i, in, t, s;
	int mr, mw;

	ins = p->events[ev];
	ASSUME(p->type[ins] == STLX && p->status[ev] == FETCH);
	rdoubleprime = p->o1[ins];
	rprime = p->o2[ins];
	r = p->o3[ins];

	rval = p->registers[r];
	rprimeval = p->registers[rprime];
	cr = 1;
	irprime = 1;
	// all po-prev ins's should have well defined memory footprints (cW >= iAddr)
	int undef[NREGS] = {0};
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		if (p->reg_written[i] == r) {
			cr = (s == COMMIT);
			rval = p->reg_write_val[i];
		} else if (p->reg_written[i] == rprime) {
			irprime = (s >= INIT);
			rprimeval = p->reg_write_val[i];
		}
	}
	// cW >= cReg(r), iReg(rprime)
	ASSUME(cr && irprime);

	// now we know the addr and memory value
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;

	// use them in checks
	for (i = 0; i < NTIME; i++){
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];
		// cW >= cDY, cISB, cDS, cDL
		// cW >= cR, cW
		if ((t <= DMBST) && t != ASSIGN)
			ASSUME(s == COMMIT);

		if (t <= STLX) {
			int reg;
			if (t <= LDAX || t > STL)
				reg = p->o2[i];
			else
				reg = p->o1[i];
			// cW >= iAddr
			ASSUME(!undef[reg]);
			// cW >= old-cW, cR
			if (p->registers[reg] == rprimeval)
				ASSUME(s == COMMIT);
		} else if (t == ACI) {
			// cW >= ctrl
			ASSUME(s == COMMIT);
		}

		if (p->reg_written[i] != -1)
			undef[NREGS] = (s == FETCH);
	}

	// now we can commit
	p->reg_write_val[ev] = write_memory(rprimeval, rval, p->p);
	p->status[ev] = COMMIT;

	// However, check that no coherence order violation has
	// taken place.
	for (i = 0; i < NTIME; i++) {
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
			continue;
		if (i >= p->cur_fill)	// don't look beyond the last event
			break;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
			break;
	}
}

void init_ASSIGN(struct proc_local_info *p, int ev)
{
	int ins, v1, v2, r1, r2, ir1, ir2;
	int i,s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == ASSIGN && p->status[ev] == FETCH);
	ASSUME(p->t1[ins] == REG);
	if (p->t2[ins] == NUM) {
		r1 = -2;	// we don't need to look for any regwrites
		v1 = p->o2[ins];
	} else {
		r1 = p->o2[ins];
		v1 = p->registers[r1];	// initial value
	}
	if (p->t3[ins] == NUM || p->t3[ins] == EMPTY) {
		r2 = -2;
		v2 = p->o3[ins];
	} else {
		r2 = p->o3[ins];
		v2 = p->registers[r2];
	}

	ir1 = ir2 = 1;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	}
	ASSUME(ir1 && ir2);

	if (p->t3[ins] == EMPTY)
		p->reg_write_val[ev] = v1;
	else {
		switch(p->operation[ins]) {
			case ADD:
				p->reg_write_val[ev] = v1+v2;
				break;
			case SUB:
				p->reg_write_val[ev] = v1-v2;
				break;
			case MULT:
				p->reg_write_val[ev] = v1*v2;
				break;
			case EOR:
				p->reg_write_val[ev] = v1^v2;
				break;
			case EQ:
				p->reg_write_val[ev] = v1 == v2;
				break;
			case NEQ:
				p->reg_write_val[ev] = v1 != v2;
				break;
			case GEQ:
				p->reg_write_val[ev] = v1 >= v2;
				break;
			case LEQ:
				p->reg_write_val[ev] = v1 <= v2;
		}
	}

	// mark as initialized
	p->status[ev] = INIT;
}

void commit_ASSIGN(struct proc_local_info *p, int ev)
{
	int ins, r1, r2, cr1, cr2;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == ASSIGN && p->status[ev] == INIT);
	if (p->t2[ins] == NUM) {
		r1 = -2;	// we don't need to look for any regwrites
	} else {
		r1 = p->o2[ins];
	}
	if (p->t3[ins] == NUM || p->t3[ins] == EMPTY) {
		r2 = -2;
	} else {
		r2 = p->o3[ins];
	}

	cr1 = cr2 = 1;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		if (t == ACI)
			ASSUME(s == COMMIT);

		if (p->reg_written[i] == r1) {
			cr1 = (s == COMMIT);
		}
		if (p->reg_written[i] == r2) {
			cr2 = (s == COMMIT);
		}
	}
	ASSUME(cr1 && cr2);

	// mark as committed
	p->status[ev] = COMMIT;
}

void init_LD(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, memval, iw, rval, ireg;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LD && p->status[ev] == FETCH);
	rprime = p->o1[ins];
	r = p->o2[ins];

	rval = p->registers[r];
	ireg = 1;

	// find rval, and add 1 check
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	}
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// iR >= cDY, cISB, cDL
		if (t == DMBSY || t == DMBLD || t == ISB)
			ASSUME(s == COMMIT);

		// iR >= iL
		if (t == LDA || t == LDAX)
			ASSUME(s >= INIT);

		if (p->memory_written[i] == rval) {
			iw = s;
			memval = p->memory_write_val[i];
		}
	}

	// iR >= iW
	ASSUME(iw >= INIT);
	if (iw == INIT) {
		// read by forwarding
		p->reg_write_val[ev] = memval;
	} else {
		// read from memory
		p->reg_write_val[ev] = read_memory(rval, -1);
	}

	// mark as initialized
	p->status[ev] = INIT;
}

void commit_LD(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, addr, cw, cr;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LD && p->status[ev] == INIT);
	rprime = p->o1[ins];
	r = p->o2[ins];

	// cR >= iReg(r) is guaranteed due to cR >= iR and iR >= iReg(r)
	cw = 1;
	cr = 1;
	addr = p->memory_read[ev];
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cR >= ctrl
		if (t == ACI)
			ASSUME(s == COMMIT);

		if (p->memory_written[i] == addr)
			cw = (s == COMMIT);
		if (p->memory_read[i] == addr)
			cr = (s == COMMIT);
	}
	// cR >= old-cR, cW
	ASSUME(cr && cw);

	// mark as committed
	p->status[ev] = COMMIT;
}

void init_LDA(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, memval, iw, rval, ireg;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LDA && p->status[ev] == FETCH);
	rprime = p->o1[ins];
	r = p->o2[ins];

	rval = p->registers[r];
	ireg = 1;

	// find rval, and add 1 check
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	}
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// iR >= cDY, cISB, cDL, cS
		if (t == DMBSY || t == DMBLD || t == ISB || t == STL || t == STLX)
			ASSUME(s == COMMIT);

		// iR >= iL
		if (t == LDA || t == LDAX)
			ASSUME(s >= INIT);

		if (p->memory_written[i] == rval) {
			iw = s;
			memval = p->memory_write_val[i];
		}
	}

	// iR >= iW
	ASSUME(iw >= INIT);
	if (iw == INIT) {
		// read by forwarding
		p->reg_write_val[ev] = memval;
	} else {
		// read from memory
		p->reg_write_val[ev] = read_memory(rval, -1);
	}

	// mark as initialized
	p->status[ev] = INIT;
}

void commit_LDA(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, addr, cw, cr;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LDA && p->status[ev] == INIT);
	rprime = p->o1[ins];
	r = p->o2[ins];

	// cR >= iReg(r) is guaranteed due to cR >= iR and iR >= iReg(r)
	cw = 1;
	cr = 1;
	addr = p->memory_read[ev];
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cR >= ctrl
		if (t == ACI)
			ASSUME(s == COMMIT);

		if (p->memory_written[i] == addr)
			cw = (s == COMMIT);
		if (p->memory_read[i] == addr)
			cr = (s == COMMIT);
	}
	// cR >= old-cR, cW
	ASSUME(cr && cw);

	// mark as committed
	p->status[ev] = COMMIT;
}

void init_LDX(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, memval, iw, rval, ireg;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LDX && p->status[ev] == FETCH);
	rprime = p->o1[ins];
	r = p->o2[ins];

	rval = p->registers[r];
	ireg = 1;

	// find rval, and add 1 check
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	}
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// iR >= cDY, cISB, cDL
		if (t == DMBSY || t == DMBLD || t == ISB)
			ASSUME(s == COMMIT);

		// iR >= iL
		if (t == LDA || t == LDAX)
			ASSUME(s >= INIT);

		if (p->memory_written[i] == rval) {
			iw = s;
			memval = p->memory_write_val[i];
		}
	}

	// iR >= iW
	ASSUME(iw >= INIT);
	if (iw == INIT) {
		// read by forwarding
		p->reg_write_val[ev] = memval;
	} else {
		// read from memory
		p->reg_write_val[ev] = read_memory(rval, p->p);
	}

	// mark as initialized
	p->status[ev] = INIT;
}

void commit_LDX(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, addr, cw, cr;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LDX && p->status[ev] == INIT);
	rprime = p->o1[ins];
	r = p->o2[ins];

	// cR >= iReg(r) is guaranteed due to cR >= iR and iR >= iReg(r)
	cw = 1;
	cr = 1;
	addr = p->memory_read[ev];
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cR >= ctrl
		if (t == ACI)
			ASSUME(s == COMMIT);

		if (p->memory_written[i] == addr)
			cw = (s == COMMIT);
		if (p->memory_read[i] == addr)
			cr = (s == COMMIT);
	}
	// cR >= old-cR, cW
	ASSUME(cr && cw);

	// mark as committed
	p->status[ev] = COMMIT;
}

void init_LDAX(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, memval, iw, rval, ireg;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LDAX && p->status[ev] == FETCH);
	rprime = p->o1[ins];
	r = p->o2[ins];

	rval = p->registers[r];
	ireg = 1;

	// find rval, and add 1 check
	for (int i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	}
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// iR >= cDY, cISB, cDL, cS
		if (t == DMBSY || t == DMBLD || t == ISB || t == STL || t == STLX)
			ASSUME(s == COMMIT);

		// iR >= iL
		if (t == LDA || t == LDAX)
			ASSUME(s >= INIT);

		if (p->memory_written[i] == rval) {
			iw = s;
			memval = p->memory_write_val[i];
		}
	}

	// iR >= iW
	ASSUME(iw >= INIT);
	if (iw == INIT) {
		// read by forwarding
		p->reg_write_val[ev] = memval;
	} else {
		// read from memory
		p->reg_write_val[ev] = read_memory(rval, -1);
	}

	// mark as initialized
	p->status[ev] = INIT;
}

void commit_LDAX(struct proc_local_info *p, int ev)
{
	int ins, rprime, r, addr, cw, cr;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == LDAX && p->status[ev] == INIT);
	rprime = p->o1[ins];
	r = p->o2[ins];

	// cR >= iReg(r) is guaranteed due to cR >= iR and iR >= iReg(r)
	cw = 1;
	cr = 1;
	addr = p->memory_read[ev];
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cR >= ctrl
		if (t == ACI)
			ASSUME(s == COMMIT);

		if (p->memory_written[i] == addr)
			cw = (s == COMMIT);
		if (p->memory_read[i] == addr)
			cr = (s == COMMIT);
	}
	// cR >= old-cR, cW
	ASSUME(cr && cw);

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_DMBSY(struct proc_local_info *p, int ev)
{
	int ins;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == DMBSY && p->status[ev] == FETCH);

	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	}

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_ISB(struct proc_local_info *p, int ev)
{
	int ins;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == ISB && p->status[ev] == FETCH);

	// all po-prev ins's should have well defined memory footprints
	int undef[NREGS] = {0};
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		if (t <= STLX) {
			int reg;
			if (t <= LDAX || t > STL)
				reg = p->o2[i];
			else
				reg = p->o1[i];
			// cISB >= iAddr
			ASSUME(!undef[reg]);
		} else if (t == DMBSY || t == ACI) {
			// cISB >= cDY, ctrl
			ASSUME(s == COMMIT);
		}
		if (p->reg_written[i] != -1)
			undef[NREGS] = (s == FETCH);
	}

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_DMBLD(struct proc_local_info *p, int ev)
{
	int ins;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == DMBLD && p->status[ev] == FETCH);

	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	}

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_DMBST(struct proc_local_info *p, int ev)
{
	int ins;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == DMBST && p->status[ev] == FETCH);

	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	}

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_ACI(struct proc_local_info *p, int ev)
{
	int ins, v1, v2, r1, r2, ir1, ir2;
	int i, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == ACI && p->status[ev] == FETCH);

	// need to collect operand values (which need to be INITed by now)

	if (p->t1[ins] == NUM) {
		r1 = -2;	// we don't need to look for any regwrites
		v1 = p->o1[ins];
	} else {
		r1 = p->o1[ins];
		v1 = p->registers[r1];	// initial value
	}
	if (p->t3[ins] == NUM) {
		r2 = -2;
		v2 = p->o2[ins];
	} else if (p->t3[ins] == EMPTY) {
		// take second operand as 0
		r2 = -2;
		v2 = 0;
	} else {
		r2 = p->o2[ins];
		v2 = p->registers[r2];
	}

	ir1 = ir2 = 1;
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	}
	ASSUME(ir1 && ir2);

	// use reg_write_val to store the result,
	// even though no register is written...
	switch(p->operation[ins]) {
	case EQ:
		p->reg_write_val[ev] = v1 == v2;
		break;
	case NEQ:
		p->reg_write_val[ev] = v1 != v2;
		break;
	case GEQ:
		p->reg_write_val[ev] = v1 >= v2;
		break;
	case LEQ:
		p->reg_write_val[ev] = v1 <= v2;
	default:
		p->reg_write_val[ev] = 1; // take it
	}

	if (ev+1 < p->cur_fill) {
		if (p->reg_write_val[ev])
			ASSUME(p->next1[ev] == p->events[ev+1]);
		else
			ASSUME(p->next2[ev] == p->events[ev+1]);
	}
}

void commit_TERM(struct proc_local_info *p, int ev)
{
	int ins;
	int i, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == TERM && p->status[ev] == FETCH);

	// need everything to be finished
	for (i = 0; i < NTIME; i++) {
		if (i == ev)
			break;
		s = p->status[i];
		ASSUME(s == COMMIT);
	}

	// mark as committed, and set done=1
	p->status[ev] = COMMIT;
	p->done = 1;
}

void *run_proc(void *pv)
{
	struct proc_local_info *p = (struct proc_local_info *)pv;
	int i, ev;
	for (i = 0; i < NTIME; i++) {
		if (!p->allfetched && (p->cur_fill == 0 || get_decision())) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
				break;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
				break;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
				break;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
				break;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
				break;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
				break;
			case STX:
				commit_STX(p,ev);
				break;
			case STLX:
				commit_STLX(p,ev);
				break;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
				break;
			case DMBSY:
				commit_DMBSY(p,ev);
				break;
			case ISB:
				commit_ISB(p,ev);
				break;
			case DMBLD:
				commit_DMBLD(p,ev);
				break;
			case DMBST:
				commit_DMBST(p,ev);
				break;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
				break;
			case ACI:
				commit_ACI(p,ev);
				break;
			case TERM:
				commit_TERM(p,ev);
				break;
			}
		}

		if (p->done)
			break;
	}

	// we don't want runs to overflow NTIME time units
	ASSUME(p->done);

	// collect final register values
	// these will be used by the final check
	for (i = 0; i < NTIME; i++) {
		if (i == p->cur_fill)
			break;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	}

	// finished!
	p->finished = 1;
}

int main(int argc, char **argv)
{
	init_mark_pre();
	init_all_procs_pre();
	init_procs();
	init_memory_and_reg_other();

	fetch_next_instr(&procs[0]);
	fetch_next_instr(&procs[0]);
	fetch_next_instr(&procs[0]);
	fetch_next_instr(&procs[0]);
	fetch_next_instr(&procs[0]);
	fetch_next_instr(&procs[1]);
	fetch_next_instr(&procs[1]);
	fetch_next_instr(&procs[1]);
	fetch_next_instr(&procs[1]);
	fetch_next_instr(&procs[1]);
	init_ASSIGN(&procs[0],0);
	commit_ASSIGN(&procs[0],0);
	init_ASSIGN(&procs[0],2);
	commit_ASSIGN(&procs[0],2);
	init_ASSIGN(&procs[1],0);
	commit_ASSIGN(&procs[1],0);
	init_ASSIGN(&procs[1],2);
	commit_ASSIGN(&procs[1],2);
	init_ST(&procs[0],3);
	init_ST(&procs[0],1);
	init_ST(&procs[1],3);
	init_ST(&procs[1],1);
	commit_ST(&procs[0],3);
	commit_ST(&procs[1],3);
	commit_ST(&procs[0],1);
	commit_ST(&procs[1],1);
	commit_TERM(&procs[1],4);
	commit_TERM(&procs[0],4);

	// we don't want runs to overflow NTIME time units
	ASSUME(procs[0].done);
	ASSUME(procs[1].done);

	// collect final register values
	// these will be used by the final check
	int i;
	for (i = 0; i < NTIME; i++) {
		if (i == procs[0].cur_fill)
			break;
		if (procs[0].reg_written[i] != -1)
			procs[0].registers[procs[0].reg_written[i]] = procs[0].reg_write_val[i];
	}
	for (i = 0; i < NTIME; i++) {
		if (i == procs[1].cur_fill)
			break;
		if (procs[1].reg_written[i] != -1)
			procs[1].registers[procs[1].reg_written[i]] = procs[1].reg_write_val[i];
	}

	// finished!
	procs[0].finished = 1;
	procs[1].finished = 1;

	check_conditions();

	return 0;
}
void init_procs() {
    // Process 0 BEGIN
    procs[0].type[0] = ASSIGN;
    procs[0].o1[0] = 4;
    procs[0].t1[0] = REG;
    procs[0].o2[0] = 2;
    procs[0].t2[0] = NUM;
    procs[0].o3[0] = -1;
    procs[0].t3[0] = EMPTY;
    procs[0].operation[0] = EQ;
    procs[0].next1[0] = 1;
    
    procs[0].type[1] = ST;
    procs[0].o1[1] = 2;
    procs[0].t1[1] = REG;
    procs[0].o2[1] = 4;
    procs[0].t2[1] = REG;
    procs[0].next1[1] = 2;
    
    procs[0].type[2] = ASSIGN;
    procs[0].o1[2] = 5;
    procs[0].t1[2] = REG;
    procs[0].o2[2] = 1;
    procs[0].t2[2] = NUM;
    procs[0].o3[2] = -1;
    procs[0].t3[2] = EMPTY;
    procs[0].operation[2] = EQ;
    procs[0].next1[2] = 3;
    
    procs[0].type[3] = ST;
    procs[0].o1[3] = 3;
    procs[0].t1[3] = REG;
    procs[0].o2[3] = 5;
    procs[0].t2[3] = REG;
    procs[0].next1[3] = 4;
    
    procs[0].type[4] = TERM;
    procs[0].next1[4] = -1;
    
    // Process 0 END
    
    // Process 1 BEGIN
    procs[1].type[0] = ASSIGN;
    procs[1].o1[0] = 4;
    procs[1].t1[0] = REG;
    procs[1].o2[0] = 2;
    procs[1].t2[0] = NUM;
    procs[1].o3[0] = -1;
    procs[1].t3[0] = EMPTY;
    procs[1].operation[0] = EQ;
    procs[1].next1[0] = 1;
    
    procs[1].type[1] = ST;
    procs[1].o1[1] = 2;
    procs[1].t1[1] = REG;
    procs[1].o2[1] = 4;
    procs[1].t2[1] = REG;
    procs[1].next1[1] = 2;
    
    procs[1].type[2] = ASSIGN;
    procs[1].o1[2] = 5;
    procs[1].t1[2] = REG;
    procs[1].o2[2] = 1;
    procs[1].t2[2] = NUM;
    procs[1].o3[2] = -1;
    procs[1].t3[2] = EMPTY;
    procs[1].operation[2] = EQ;
    procs[1].next1[2] = 3;
    
    procs[1].type[3] = ST;
    procs[1].o1[3] = 3;
    procs[1].t1[3] = REG;
    procs[1].o2[3] = 5;
    procs[1].t2[3] = REG;
    procs[1].next1[3] = 4;
    
    procs[1].type[4] = TERM;
    procs[1].next1[4] = -1;
    
    // Process 1 END
    
}

void init_memory_and_reg_other() {
    
    procs[0].registers[2] = 1;
    procs[0].registers[3] = 0;
    procs[1].registers[2] = 0;
    procs[1].registers[3] = 1;
}

void check_conditions() {
    if (
        (memory[1] == 2) &&
        (memory[0] == 2) &&
    1)
        ASSERT(0);
}
