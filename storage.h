uint32_t init_nonacq_read_nondet();
uint32_t init_acq_read_nondet();
uint32_t com_read_nondet();
uint32_t init_st_nondet();
uint32_t init_stl_nondet();
uint32_t com_non_exc_write_nondet();
uint32_t com_stx_nondet();
uint32_t com_stlx_nondet();
uint32_t com_isb_nondet();
uint32_t com_dmb_ld_nondet();
uint32_t com_dmb_st_nondet();
uint32_t com_dmb_sy_nondet();
uint32_t com_aci_nondet();
uint32_t init_assign_nondet();
uint32_t com_assign_nondet();

/**
 * init_nonacq_read_nondet - tries to initialize one of the existing 
 * reads nondeterministically. Returns the event_num of the initialized
 * event, and 0xFFFFFFFF if no event is found.
 */
uint32_t process::init_nonacq_read_nondet()
{
	vector<struct event *> possible_reads;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && (ev->ins_type == LD || ev->ins_type == LDX)
			&& ev->addr_final != 0xFFFFFFFF) {
			possible_reads.push_back(ev);
		}
	}
	std::random_shuffle(possible_reads.begin(), possible_reads.end()); 		// non-deterministic

	// keep trying until we find a possible read
jump_loc:
	if (++cur == possible_reads.size())
		return 0xFFFFFFFF;
	e = possible_reads[cur];
	// verify necessary conditions 
	if (!nonacq_read_init_cnd(e)) {
		goto jump_loc;
	}

	// try_resolving_addresses should have been called BEFORE
	// calling any init/commit functions
	event *ev;
	if ((ev = get_closest_write(e)) && ev->status == INIT) { 	// Have a local event to read from
		e->rf = ev;
		e->result = ev->result;
	} else if (!ev || e->status == COMMIT) {					// Must read from global event
		e->rf = read_global_memory(e->addr_final, proc_id);
		e->result = e->rf->result;
	} else  {													// CW is still in FETCH phase
		goto jump_loc;
	}

	// successful
	e->status = INIT;
	return e->event_num;
}

/**
 * init_acq_read_nondet - tries to initialize one of the existing 
 * reads nondeterministically. Returns the event_num of the initialized
 * event, and 0xFFFFFFFF if no event is found.
 */
uint32_t process::init_acq_read_nondet()
{
	vector<struct event *> possible_reads;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && (ev->ins_type == LDA || ev->ins_type == LDAX)
			&& ev->addr_final != 0xFFFFFFFF) {
			possible_reads.push_back(ev);
		}
	}
	std::random_shuffle(possible_reads.begin(), possible_reads.end()); 		// non-deterministic

	// keep trying until we find a possible read
jump_loc:
	if (++cur == possible_reads.size())
		return 0xFFFFFFFF;
	e = possible_reads[cur];
	// verify necessary conditions 
	if (!acq_read_init_cnd(e)) {
		goto jump_loc;
	}

	// try_resolving_addresses should have been called BEFORE
	// calling any init/commit functions
	event *ev;
	if ((ev = get_closest_write(e)) && ev->status == INIT) { 	// Have a local event to read from
		e->rf = ev;
		e->result = ev->result;
	} else if (!ev || e->status == COMMIT) {					// Must read from global event
		e->rf = read_global_memory(e->addr_final, proc_id);
		e->result = e->rf->result;
	} else  {													// CW is still in FETCH phase
		goto jump_loc;
	}

	// successful
	e->status = INIT;
	return e->event_num;
}

/**
 * com_read - commit a nondeterministically chosen read event.
 * returns 0xFFFFFFFF if the commit failed, and otherwise
 * returns the event_num of the committed event on success.
 */
uint32_t process::com_read_nondet()
{
	vector<struct event *> possible_reads;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == INIT && (ev->ins_type == LD || ev->ins_type == LDA ||
			ev->ins_type == LDX || ev->ins_type == LDAX)
			&& ev->addr_final != 0xFFFFFFFF) {
			possible_reads.push_back(ev);
		}
	}
	std::random_shuffle(possible_reads.begin(), possible_reads.end()); 		// non-deterministic

	// keep trying until we find a possible read
jump_loc:
	if (++cur == possible_reads.size())
		return 0xFFFFFFFF;
	e = possible_reads[cur];
	// verify necessary conditions 
	if (!read_com_cnd(e)) {
		goto jump_loc;
	}

	if (e->ins_type == LDX || e->ins_type == LDAX)
		update_mark(e->addr_final, e);

	// successful
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}

/**
 * init_st_nondet - initialize a store event randomly 
 * chosen from possible ones. If for all options, some condition 
 * isn't satisfied  or some dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns the event_num of the chosen event.
 */
uint32_t process::init_st_nondet()
{
	vector<struct event *> possible_sts;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && (ev->ins_type == ST)
			&& ev->addr_final != 0xFFFFFFFF) {
			possible_sts.push_back(ev);
		}
	}
	std::random_shuffle(possible_sts.begin(), possible_sts.end()); 		// non-deterministic

	// keep trying until we find a possible st
jump_loc:
	if (++cur == possible_sts.size())
		return 0xFFFFFFFF;
	e = possible_sts[cur];
	if (!st_init_cnd(e))
		goto jump_loc;

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
	return e->event_num;
}

/**
 * init_stl_nondet - initialize a store-release event randomly 
 * chosen from possible ones. If for all options, some condition 
 * isn't satisfied  or some dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns the event_num of the chosen event.
 * NOTE: The nondet is a misnomer: at any point, there is at most
 * one STL event that can be init-ed.
 */
uint32_t process::init_stl_nondet()
{
	struct event *e = NULL;

	// there is at most one stl event that can be init-ed : the earliest one
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && (ev->ins_type == STL)
			&& ev->addr_final != 0xFFFFFFFF) {
			if (!e || e->event_num > ev->event_num)
				e = ev;
		}
	}

	if (e)
		return init_stl(e);
	else
		return 0xFFFFFFFF;
}

/**
 * com_non_exc_write_nondet - commit a non-exclusive write randomly chosen 
 * chosen from possible ones. If for all options, some condition 
 * isn't satisfied  or some dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns the event_num of the chosen event.
 */
uint32_t process::com_non_exc_write_nondet()
{
	vector<struct event *> possible_writes;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == INIT && (ev->ins_type == ST || ev->ins_type == STL)) {
			possible_writes.push_back(ev);
		}
	}
	std::random_shuffle(possible_writes.begin(), possible_writes.end()); 		// non-deterministic

	// keep trying until we find a possible write
jump_loc:
	if (++cur == possible_writes.size())
		return 0xFFFFFFFF;
	e = possible_writes[cur];
	if (!non_exc_write_com_cnd(e))
		goto jump_loc;

	// mark as committed _before_ updating main memory
	e->status = COMMIT;

	// update main memory with propagated write
	write_global_memory(e->addr_final, e);

	remove_event(e);								// Once committed, no need to keep around

	return e->event_num;
}

/**
 * com_stx_nondet - try to non-deterministically
 * commit a fetched store exclusive. If no such event
 * is found that satisfies the needed conditions, returns 0xFFFFFFFF.
 * Otherwise returns the event's event_num.
 */
uint32_t process::com_stx_nondet()
{
	vector<struct event *> possible_stxs;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == STX && ev->addr_final != 0xFFFFFFFF) {
			possible_stxs.push_back(ev);
		}
	}
	std::random_shuffle(possible_stxs.begin(), possible_stxs.end()); 		// non-deterministic

	// keep trying until we find a possible stx
jump_loc:
	if (++cur == possible_stxs.size())
		return 0xFFFFFFFF;
	e = possible_stxs[cur];

	if (!stx_com_cnd(e))
		goto jump_loc;

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
	e->exc_success =  !!(write_global_memory(e->addr_final, e));

	remove_event(e);								// Once committed, no need to keep around

	return e->event_num;
}

/**
 * com_stlx_nondet - try to non-deterministically
 * commit a fetched stlx. If no such event
 * is found that satisfies the needed conditions, returns 0xFFFFFFFF.
 * Otherwise returns the event's event_num.
 * NOTE: As with STL, here the nondet is a misnomer: at any given moment,
 * there is at most one STLX that can be committed.
 */
uint32_t process::com_stlx_nondet()
{
	struct event *e = NULL;

	// there is at most one stlx event that can be committed now: the earliest one
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == STLX && ev->addr_final != 0xFFFFFFFF) {
			if (!e || e->event_num > ev->event_num)
				e = ev;
		}
	}

	if (e)
		return com_stlx(e);
	else 
		return 0xFFFFFFFF;
}

/**
 * com_isb_nondet - try to commit a non-deterministically
 * chosen ISB event from those that are active. Returns 0xFFFFFFFF
 * on failure and the event_num of the committed ISB on success. 
 */
uint32_t process::com_isb_nondet()
{
	vector<struct event *> possible_isbs;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == ISB) {
			possible_isbs.push_back(ev);
		}
	}
	std::random_shuffle(possible_isbs.begin(), possible_isbs.end()); 		// non-deterministic

	// keep trying until we find a possible isb
jump_loc:
	if (++cur == possible_isbs.size())
		return 0xFFFFFFFF;
	e = possible_isbs[cur];

	if (!isb_com_cnd(e))
		goto jump_loc;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}

/**
 * com_dmb_ld_nondet - try to commit a non-deterministically
 * chosen DMBLD event from those that are active. Returns 0xFFFFFFFF
 * on failure and the event_num of the committed DMBLD on success. 
 */
uint32_t process::com_dmb_ld_nondet()
{
	vector<struct event *> possible_dmb_lds;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == DMBLD) {
			possible_dmb_lds.push_back(ev);
		}
	}
	std::random_shuffle(possible_dmb_lds.begin(), possible_dmb_lds.end()); 		// non-deterministic

	// keep trying until we find a possible isb
jump_loc:
	if (++cur == possible_dmb_lds.size())
		return 0xFFFFFFFF;
	e = possible_dmb_lds[cur];

	if (!dmb_ld_com_cnd(e))
		goto jump_loc;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}

/**
 * com_dmb_ld_nondet - try to commit a non-deterministically
 * chosen DMBST event from those that are active. Returns 0xFFFFFFFF
 * on failure and the event_num of the committed DMBST on success. 
 */
uint32_t process::com_dmb_st_nondet()
{
	vector<struct event *> possible_dmb_sts;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == DMBLD) {
			possible_dmb_sts.push_back(ev);
		}
	}
	std::random_shuffle(possible_dmb_sts.begin(), possible_dmb_sts.end()); 		// non-deterministic

	// keep trying until we find a possible isb
jump_loc:
	if (++cur == possible_dmb_sts.size())
		return 0xFFFFFFFF;
	e = possible_dmb_sts[cur];

	if (!dmb_st_com_cnd(e))
		goto jump_loc;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}

/**
 * com_dmb_sy_nondet - try to commit a non-deterministically
 * chosen DMBSY event from those that are active. Returns 0xFFFFFFFF
 * on failure and the event_num of the committed DMBSY on success. 
 */
uint32_t process::com_dmb_sy_nondet()
{
	vector<struct event *> possible_dmb_sys;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == DMBLD) {
			possible_dmb_sys.push_back(ev);
		}
	}
	std::random_shuffle(possible_dmb_sys.begin(), possible_dmb_sys.end()); 		// non-deterministic

	// keep trying until we find a possible isb
jump_loc:
	if (++cur == possible_dmb_sys.size())
		return 0xFFFFFFFF;
	e = possible_dmb_sys[cur];

	if (!dmb_sy_com_cnd(e))
		goto jump_loc;

	// mark e as committed
	e->status = COMMIT;
	remove_event(e);								// Once committed, no need to keep around
	return e->event_num;
}

/**
 * com_aci_nondet - try to commit an ACI event randomly chosen
 * from the active ones. Returns 0xFFFFFFFF on failure and 
 * the event_num of the committed ACI on success.
 * NOTE: again, the nondet/random is a misnomer: at any point there
 * is at most one aci that can be committed: the earliest.
 */
uint32_t process::com_aci_nondet()
{
	struct event *e = NULL;

	// there is at most one aci event that can be committed now: the earliest one
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == ACI) {
			if (!e || e->event_num > ev->event_num)
				e = ev;
		}
	}

	if (e)
		return com_aci(e);
	else 
		return 0xFFFFFFFF;
}

/**
 * init_assign_nondet - initialize an assign event randomly 
 * chosen from possible ones. If for all options, some condition 
 * isn't satisfied  or some dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns the event_num of the chosen event.
 */
uint32_t process::init_assign_nondet()
{
	vector<struct event *> possible_assigns;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == FETCH && ev->ins_type == ASSIGN) {
			possible_assigns.push_back(ev);
		}
	}
	std::random_shuffle(possible_assigns.begin(), possible_assigns.end()); 		// non-deterministic

	// keep trying until we find a possible st
jump_loc:
	if (++cur == possible_assigns.size())
		return 0xFFFFFFFF;
	e = possible_assigns[cur];
	if (!assign_init_cnd(e))
		goto jump_loc;

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
	return e->event_num;
}

/**
 * com_assign_nondet - commit an assign randomly chosen 
 * chosen from possible ones. If for all options, some condition 
 * isn't satisfied  or some dependency isn't met, returns 0xFFFFFFFF.
 * On success, returns the event_num of the chosen event.
 */
uint32_t process::com_assign_nondet()
{
	vector<struct event *> possible_assigns;
	struct event *e;
	int cur = -1;
	for (struct event *ev : active_events) {
		if (ev->status == INIT && ev->ins_type == ASSIGN) {
			possible_assigns.push_back(ev);
		}
	}
	std::random_shuffle(possible_assigns.begin(), possible_assigns.end()); 		// non-deterministic

	// keep trying until we find a possible write
jump_loc:
	if (++cur == possible_assigns.size())
		return 0xFFFFFFFF;
	e = possible_assigns[cur];
	if (!assign_com_cnd(e))
		goto jump_loc;

	// mark as committed
	e->status = COMMIT;

	remove_event(e);								// Once committed, no need to keep around

	return e->event_num;
}
