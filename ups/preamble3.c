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
 /* Loop 0 BEGIN */
  i = 0;
loop_label_0_0:
		memory[i] = __get_rng();
  i++;
loop_label_0_1:
		memory[i] = __get_rng();
  i++;
loop_label_0_2:
		memory[i] = __get_rng();
  i++;
loop_label_0_3:
		memory[i] = __get_rng();
  i++;
loop_label_0_4:
		memory[i] = __get_rng();
  i++;
loop_label_0_5:
		memory[i] = __get_rng();
  i++;
loop_label_0_6:
		memory[i] = __get_rng();
  i++;
loop_label_0_7:
		memory[i] = __get_rng();
  i++;
loop_label_0_8:
		memory[i] = __get_rng();
  i++;
loop_label_0_9:
		memory[i] = __get_rng();
  i++;
loop_label_0_10:
		memory[i] = __get_rng();
  i++;
loop_label_0_11:
		memory[i] = __get_rng();
  i++;
loop_label_0_12:
		memory[i] = __get_rng();
  i++;
loop_label_0_13:
		memory[i] = __get_rng();
  i++;
loop_label_0_14:
		memory[i] = __get_rng();
  i++;
loop_label_0_15:
		memory[i] = __get_rng();
  i++;
loop_label_0_16:
		memory[i] = __get_rng();
  i++;
loop_label_0_17:
		memory[i] = __get_rng();
  i++;
loop_label_0_18:
		memory[i] = __get_rng();
  i++;
loop_label_0_19:
		memory[i] = __get_rng();
  i++;
loop_label_0_20:
		memory[i] = __get_rng();
  i++;
loop_label_0_21:
		memory[i] = __get_rng();
  i++;
loop_label_0_22:
		memory[i] = __get_rng();
  i++;
loop_label_0_23:
		memory[i] = __get_rng();
  i++;
loop_label_0_24:
		memory[i] = __get_rng();
  i++;
loop_label_0_25:
		memory[i] = __get_rng();
  i++;
loop_label_0_26:
		memory[i] = __get_rng();
  i++;
loop_label_0_27:
		memory[i] = __get_rng();
  i++;
loop_label_0_28:
		memory[i] = __get_rng();
  i++;
loop_label_0_29:
		memory[i] = __get_rng();
  i++;
loop_label_0_30:
		memory[i] = __get_rng();
  i++;
loop_label_0_31:
		memory[i] = __get_rng();
  i++;
loop_label_0_32:
		memory[i] = __get_rng();
  i++;
loop_label_0_33:
		memory[i] = __get_rng();
  i++;
loop_label_0_34:
		memory[i] = __get_rng();
  i++;
loop_label_0_35:
		memory[i] = __get_rng();
  i++;
loop_label_0_36:
		memory[i] = __get_rng();
  i++;
loop_label_0_37:
		memory[i] = __get_rng();
  i++;
loop_label_0_38:
		memory[i] = __get_rng();
  i++;
loop_label_0_39:
		memory[i] = __get_rng();
  i++;
loop_label_0_40:
		memory[i] = __get_rng();
  i++;
loop_label_0_41:
		memory[i] = __get_rng();
  i++;
loop_label_0_42:
		memory[i] = __get_rng();
  i++;
loop_label_0_43:
		memory[i] = __get_rng();
  i++;
loop_label_0_44:
		memory[i] = __get_rng();
  i++;
loop_label_0_45:
		memory[i] = __get_rng();
  i++;
loop_label_0_46:
		memory[i] = __get_rng();
  i++;
loop_label_0_47:
		memory[i] = __get_rng();
  i++;
loop_label_0_48:
		memory[i] = __get_rng();
  i++;
loop_label_0_49:
		memory[i] = __get_rng();
  i++;
loop_label_0_50:
		memory[i] = __get_rng();
  i++;
loop_label_0_51:
		memory[i] = __get_rng();
  i++;
loop_label_0_52:
		memory[i] = __get_rng();
  i++;
loop_label_0_53:
		memory[i] = __get_rng();
  i++;
loop_label_0_54:
		memory[i] = __get_rng();
  i++;
loop_label_0_55:
		memory[i] = __get_rng();
  i++;
loop_label_0_56:
		memory[i] = __get_rng();
  i++;
loop_label_0_57:
		memory[i] = __get_rng();
  i++;
loop_label_0_58:
		memory[i] = __get_rng();
  i++;
loop_label_0_59:
		memory[i] = __get_rng();
  i++;
loop_label_0_60:
		memory[i] = __get_rng();
  i++;
loop_label_0_61:
		memory[i] = __get_rng();
  i++;
loop_label_0_62:
		memory[i] = __get_rng();
  i++;
loop_label_0_63:
		memory[i] = __get_rng();
  i++;
loop_label_0_64:
  /* Loop 0 END */;
}

void init_mark_pre()
{
	int i;
 /* Loop 1 BEGIN */
  i = 0;
loop_label_1_0:
		mark[i] = -1;
  i++;
loop_label_1_1:
		mark[i] = -1;
  i++;
loop_label_1_2:
		mark[i] = -1;
  i++;
loop_label_1_3:
		mark[i] = -1;
  i++;
loop_label_1_4:
		mark[i] = -1;
  i++;
loop_label_1_5:
		mark[i] = -1;
  i++;
loop_label_1_6:
		mark[i] = -1;
  i++;
loop_label_1_7:
		mark[i] = -1;
  i++;
loop_label_1_8:
		mark[i] = -1;
  i++;
loop_label_1_9:
		mark[i] = -1;
  i++;
loop_label_1_10:
		mark[i] = -1;
  i++;
loop_label_1_11:
		mark[i] = -1;
  i++;
loop_label_1_12:
		mark[i] = -1;
  i++;
loop_label_1_13:
		mark[i] = -1;
  i++;
loop_label_1_14:
		mark[i] = -1;
  i++;
loop_label_1_15:
		mark[i] = -1;
  i++;
loop_label_1_16:
		mark[i] = -1;
  i++;
loop_label_1_17:
		mark[i] = -1;
  i++;
loop_label_1_18:
		mark[i] = -1;
  i++;
loop_label_1_19:
		mark[i] = -1;
  i++;
loop_label_1_20:
		mark[i] = -1;
  i++;
loop_label_1_21:
		mark[i] = -1;
  i++;
loop_label_1_22:
		mark[i] = -1;
  i++;
loop_label_1_23:
		mark[i] = -1;
  i++;
loop_label_1_24:
		mark[i] = -1;
  i++;
loop_label_1_25:
		mark[i] = -1;
  i++;
loop_label_1_26:
		mark[i] = -1;
  i++;
loop_label_1_27:
		mark[i] = -1;
  i++;
loop_label_1_28:
		mark[i] = -1;
  i++;
loop_label_1_29:
		mark[i] = -1;
  i++;
loop_label_1_30:
		mark[i] = -1;
  i++;
loop_label_1_31:
		mark[i] = -1;
  i++;
loop_label_1_32:
		mark[i] = -1;
  i++;
loop_label_1_33:
		mark[i] = -1;
  i++;
loop_label_1_34:
		mark[i] = -1;
  i++;
loop_label_1_35:
		mark[i] = -1;
  i++;
loop_label_1_36:
		mark[i] = -1;
  i++;
loop_label_1_37:
		mark[i] = -1;
  i++;
loop_label_1_38:
		mark[i] = -1;
  i++;
loop_label_1_39:
		mark[i] = -1;
  i++;
loop_label_1_40:
		mark[i] = -1;
  i++;
loop_label_1_41:
		mark[i] = -1;
  i++;
loop_label_1_42:
		mark[i] = -1;
  i++;
loop_label_1_43:
		mark[i] = -1;
  i++;
loop_label_1_44:
		mark[i] = -1;
  i++;
loop_label_1_45:
		mark[i] = -1;
  i++;
loop_label_1_46:
		mark[i] = -1;
  i++;
loop_label_1_47:
		mark[i] = -1;
  i++;
loop_label_1_48:
		mark[i] = -1;
  i++;
loop_label_1_49:
		mark[i] = -1;
  i++;
loop_label_1_50:
		mark[i] = -1;
  i++;
loop_label_1_51:
		mark[i] = -1;
  i++;
loop_label_1_52:
		mark[i] = -1;
  i++;
loop_label_1_53:
		mark[i] = -1;
  i++;
loop_label_1_54:
		mark[i] = -1;
  i++;
loop_label_1_55:
		mark[i] = -1;
  i++;
loop_label_1_56:
		mark[i] = -1;
  i++;
loop_label_1_57:
		mark[i] = -1;
  i++;
loop_label_1_58:
		mark[i] = -1;
  i++;
loop_label_1_59:
		mark[i] = -1;
  i++;
loop_label_1_60:
		mark[i] = -1;
  i++;
loop_label_1_61:
		mark[i] = -1;
  i++;
loop_label_1_62:
		mark[i] = -1;
  i++;
loop_label_1_63:
		mark[i] = -1;
  i++;
loop_label_1_64:
  /* Loop 1 END */;
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
 /* Loop 2 BEGIN */
 i = 0;
loop_label_2_0:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_1:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_2:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_3:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_4:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_5:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_6:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_7:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_8:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_9:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_10:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_11:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_12:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_13:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_14:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_15:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_16:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_17:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_18:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_19:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_20:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_21:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_22:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_23:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_24:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_25:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_26:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_27:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_28:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_29:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_30:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_31:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_32:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_33:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_34:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_35:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_36:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_37:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_38:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_39:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_40:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_41:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_42:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_43:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_44:
		p->status[i] = 0;	// not fetched
		p->events[i] = p->memory_written[i] =
		 p->reg_written[i] = p->memory_read[i] = p->memory_write_val[i] =
		 p->reg_write_val[i] = -1;
	
 i++;
loop_label_2_45:
 /* Loop 2 END */;
 /* Loop 3 BEGIN */
  i = 0;
loop_label_3_0:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_1:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_2:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_3:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_4:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_5:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_6:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_7:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_8:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_9:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_10:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_11:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_12:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_13:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_14:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_15:
		p->registers[i] = 0;	// specific ones done by py script
  i++;
loop_label_3_16:
  /* Loop 3 END */;
}

void init_procs();

void init_all_procs_pre()
{
	int i;
 /* Loop 4 BEGIN */
 i = 0;
loop_label_4_0:
		procs[i].p = i;
		init_proc_local_info_pre(&procs[i]);
	
 i++;
loop_label_4_1:
		procs[i].p = i;
		init_proc_local_info_pre(&procs[i]);
	
 i++;
loop_label_4_2:
 /* Loop 4 END */;
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
 /* Loop 5 BEGIN */
 i = 0;
loop_label_5_0:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_1:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_2:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_3:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_4:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_5:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_6:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_7:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_8:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_9:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_10:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_11:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_12:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_13:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_14:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_15:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_16:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_17:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_18:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_19:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_20:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_21:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_22:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_23:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_24:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_25:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_26:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_27:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_28:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_29:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_30:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_31:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_32:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_33:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_34:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_35:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_36:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_37:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_38:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_39:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_40:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_41:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_42:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_43:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_44:
		if (i == ev)
   goto loop_label_5_45;
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
	
 i++;
loop_label_5_45:
 /* Loop 5 END */;
	// iW >= iReg(r), iReg(rprime)
	ASSUME(ir && irprime);

	// now we can init
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;
	p->status[ev] = INIT;

	// However, check that no coherence order violation has
	// taken place.
 /* Loop 6 BEGIN */
 i = 0;
loop_label_6_0:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_1;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_1:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_2;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_2:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_3;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_3:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_4;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_4:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_5;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_5:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_6;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_6:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_7;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_7:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_8;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_8:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_9;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_9:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_10;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_10:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_11;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_11:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_12;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_12:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_13;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_13:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_14;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_14:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_15;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_15:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_16;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_16:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_17;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_17:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_18;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_18:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_19;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_19:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_20;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_20:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_21;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_21:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_22;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_22:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_23;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_23:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_24;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_24:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_25;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_25:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_26;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_26:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_27;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_27:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_28;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_28:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_29;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_29:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_30;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_30:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_31;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_31:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_32;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_32:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_33;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_33:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_34;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_34:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_35;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_35:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_36;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_36:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_37;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_37:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_38;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_38:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_39;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_39:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_40;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_40:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_41;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_41:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_42;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_42:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_43;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_43:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_44;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_44:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_6_45;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_6_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_6_45;
	
 i++;
loop_label_6_45:
 /* Loop 6 END */;
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
 /* Loop 7 BEGIN */
 i = 0;
loop_label_7_0:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_1:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_2:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_3:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_4:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_5:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_6:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_7:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_8:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_9:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_10:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_11:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_12:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_13:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_14:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_15:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_16:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_17:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_18:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_19:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_20:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_21:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_22:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_23:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_24:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_25:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_26:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_27:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_28:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_29:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_30:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_31:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_32:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_33:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_34:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_35:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_36:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_37:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_38:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_39:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_40:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_41:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_42:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_43:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_44:
		if (i == ev)
   goto loop_label_7_45;
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
	
 i++;
loop_label_7_45:
 /* Loop 7 END */;
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
 /* Loop 8 BEGIN */
 i = 0;
loop_label_8_0:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_1:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_2:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_3:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_4:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_5:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_6:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_7:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_8:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_9:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_10:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_11:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_12:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_13:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_14:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_15:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_16:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_17:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_18:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_19:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_20:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_21:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_22:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_23:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_24:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_25:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_26:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_27:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_28:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_29:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_30:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_31:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_32:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_33:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_34:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_35:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_36:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_37:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_38:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_39:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_40:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_41:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_42:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_43:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_44:
		if (i == ev)
   goto loop_label_8_45;
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
	
 i++;
loop_label_8_45:
 /* Loop 8 END */;
	// iW >= iReg(r), iReg(rprime)
	ASSUME(ir && irprime);

	// now we can init
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;
	p->status[ev] = INIT;

	// However, check that no coherence order violation has
	// taken place.
 /* Loop 9 BEGIN */
 i = 0;
loop_label_9_0:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_1;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_1:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_2;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_2:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_3;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_3:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_4;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_4:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_5;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_5:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_6;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_6:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_7;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_7:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_8;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_8:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_9;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_9:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_10;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_10:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_11;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_11:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_12;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_12:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_13;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_13:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_14;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_14:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_15;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_15:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_16;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_16:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_17;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_17:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_18;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_18:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_19;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_19:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_20;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_20:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_21;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_21:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_22;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_22:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_23;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_23:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_24;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_24:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_25;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_25:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_26;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_26:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_27;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_27:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_28;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_28:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_29;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_29:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_30;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_30:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_31;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_31:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_32;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_32:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_33;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_33:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_34;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_34:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_35;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_35:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_36;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_36:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_37;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_37:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_38;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_38:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_39;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_39:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_40;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_40:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_41;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_41:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_42;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_42:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_43;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_43:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_44;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_44:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_9_45;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_9_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_9_45;
	
 i++;
loop_label_9_45:
 /* Loop 9 END */;
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
 /* Loop 10 BEGIN */
 i = 0;
loop_label_10_0:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_1:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_2:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_3:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_4:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_5:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_6:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_7:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_8:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_9:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_10:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_11:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_12:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_13:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_14:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_15:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_16:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_17:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_18:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_19:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_20:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_21:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_22:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_23:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_24:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_25:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_26:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_27:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_28:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_29:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_30:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_31:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_32:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_33:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_34:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_35:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_36:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_37:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_38:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_39:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_40:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_41:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_42:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_43:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_44:
		if (i == ev)
   goto loop_label_10_45;
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
	
 i++;
loop_label_10_45:
 /* Loop 10 END */;
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
 /* Loop 11 BEGIN */
 i = 0;
loop_label_11_0:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_1:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_2:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_3:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_4:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_5:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_6:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_7:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_8:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_9:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_10:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_11:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_12:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_13:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_14:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_15:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_16:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_17:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_18:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_19:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_20:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_21:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_22:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_23:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_24:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_25:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_26:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_27:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_28:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_29:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_30:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_31:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_32:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_33:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_34:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_35:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_36:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_37:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_38:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_39:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_40:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_41:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_42:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_43:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_44:
		if (i == ev)
   goto loop_label_11_45;
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
	
 i++;
loop_label_11_45:
 /* Loop 11 END */;
	// cW >= cReg(r), iReg(rprime)
	ASSUME(cr && irprime);

	// now we know the addr and memory value
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;

	// use them in checks
 /* Loop 12 BEGIN */
 i = 0;
loop_label_12_0:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_1:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_2:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_3:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_4:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_5:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_6:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_7:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_8:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_9:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_10:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_11:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_12:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_13:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_14:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_15:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_16:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_17:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_18:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_19:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_20:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_21:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_22:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_23:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_24:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_25:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_26:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_27:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_28:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_29:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_30:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_31:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_32:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_33:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_34:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_35:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_36:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_37:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_38:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_39:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_40:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_41:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_42:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_43:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_44:
		if (i == ev)
   goto loop_label_12_45;
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
	
 i++;
loop_label_12_45:
 /* Loop 12 END */;

	// now we can commit
	p->reg_write_val[ev] = write_memory(rprimeval, rval, p->p);
	p->status[ev] = COMMIT;

	// However, check that no coherence order violation has
	// taken place.
 /* Loop 13 BEGIN */
 i = 0;
loop_label_13_0:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_1;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_1:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_2;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_2:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_3;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_3:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_4;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_4:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_5;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_5:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_6;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_6:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_7;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_7:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_8;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_8:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_9;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_9:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_10;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_10:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_11;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_11:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_12;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_12:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_13;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_13:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_14;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_14:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_15;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_15:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_16;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_16:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_17;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_17:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_18;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_18:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_19;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_19:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_20;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_20:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_21;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_21:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_22;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_22:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_23;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_23:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_24;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_24:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_25;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_25:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_26;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_26:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_27;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_27:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_28;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_28:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_29;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_29:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_30;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_30:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_31;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_31:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_32;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_32:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_33;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_33:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_34;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_34:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_35;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_35:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_36;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_36:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_37;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_37:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_38;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_38:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_39;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_39:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_40;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_40:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_41;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_41:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_42;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_42:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_43;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_43:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_44;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_44:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_13_45;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_13_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_13_45;
	
 i++;
loop_label_13_45:
 /* Loop 13 END */;
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
 /* Loop 14 BEGIN */
 i = 0;
loop_label_14_0:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_1:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_2:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_3:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_4:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_5:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_6:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_7:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_8:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_9:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_10:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_11:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_12:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_13:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_14:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_15:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_16:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_17:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_18:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_19:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_20:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_21:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_22:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_23:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_24:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_25:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_26:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_27:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_28:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_29:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_30:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_31:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_32:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_33:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_34:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_35:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_36:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_37:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_38:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_39:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_40:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_41:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_42:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_43:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_44:
		if (i == ev)
   goto loop_label_14_45;
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
	
 i++;
loop_label_14_45:
 /* Loop 14 END */;
	// cW >= cReg(r), iReg(rprime)
	ASSUME(cr && irprime);

	// now we know the addr and memory value
	p->memory_write_val[ev] = rval;
	p->memory_written[ev] = rprimeval;

	// use them in checks
 /* Loop 15 BEGIN */
 i = 0;
loop_label_15_0:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_1:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_2:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_3:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_4:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_5:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_6:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_7:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_8:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_9:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_10:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_11:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_12:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_13:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_14:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_15:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_16:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_17:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_18:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_19:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_20:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_21:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_22:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_23:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_24:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_25:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_26:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_27:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_28:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_29:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_30:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_31:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_32:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_33:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_34:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_35:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_36:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_37:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_38:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_39:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_40:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_41:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_42:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_43:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_44:
		if (i == ev)
   goto loop_label_15_45;
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
	
 i++;
loop_label_15_45:
 /* Loop 15 END */;

	// now we can commit
	p->reg_write_val[ev] = write_memory(rprimeval, rval, p->p);
	p->status[ev] = COMMIT;

	// However, check that no coherence order violation has
	// taken place.
 /* Loop 16 BEGIN */
 i = 0;
loop_label_16_0:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_1;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_1:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_2;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_2:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_3;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_3:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_4;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_4:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_5;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_5:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_6;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_6:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_7;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_7:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_8;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_8:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_9;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_9:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_10;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_10:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_11;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_11:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_12;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_12:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_13;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_13:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_14;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_14:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_15;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_15:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_16;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_16:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_17;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_17:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_18;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_18:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_19;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_19:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_20;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_20:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_21;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_21:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_22;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_22:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_23;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_23:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_24;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_24:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_25;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_25:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_26;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_26:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_27;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_27:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_28;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_28:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_29;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_29:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_30;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_30:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_31;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_31:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_32;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_32:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_33;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_33:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_34;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_34:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_35;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_35:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_36;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_36:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_37;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_37:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_38;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_38:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_39;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_39:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_40;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_40:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_41;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_41:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_42;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_42:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_43;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_43:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_44;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_44:
		if (i <= ev)	// we need to start after ev, this way of writing is for CBMC-easy unroll
   goto loop_label_16_45;
		if (i >= p->cur_fill)	// don't look beyond the last event
   goto loop_label_16_45;
		in = p->events[i];
		s = p->status[i];
		mr = p->memory_read[i];
		mw = p->memory_written[i];

		// check mr before mw - an event may read and write the same address
		if (mr == rprimeval)
			ASSUME(s == FETCH);	// coh
		if (mw == rprimeval)	// this write subsumes ev
   goto loop_label_16_45;
	
 i++;
loop_label_16_45:
 /* Loop 16 END */;
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
 /* Loop 17 BEGIN */
 i = 0;
loop_label_17_0:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_1:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_2:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_3:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_4:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_5:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_6:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_7:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_8:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_9:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_10:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_11:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_12:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_13:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_14:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_15:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_16:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_17:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_18:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_19:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_20:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_21:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_22:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_23:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_24:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_25:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_26:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_27:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_28:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_29:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_30:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_31:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_32:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_33:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_34:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_35:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_36:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_37:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_38:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_39:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_40:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_41:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_42:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_43:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_44:
		if (i == ev)
   goto loop_label_17_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_17_45:
 /* Loop 17 END */;
	ASSUME(ir1 && ir2);

	if (p->t3[ins] == NUM)
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
 /* Loop 18 BEGIN */
 i = 0;
loop_label_18_0:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_1:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_2:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_3:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_4:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_5:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_6:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_7:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_8:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_9:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_10:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_11:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_12:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_13:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_14:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_15:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_16:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_17:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_18:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_19:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_20:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_21:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_22:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_23:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_24:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_25:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_26:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_27:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_28:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_29:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_30:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_31:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_32:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_33:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_34:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_35:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_36:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_37:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_38:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_39:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_40:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_41:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_42:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_43:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_44:
		if (i == ev)
   goto loop_label_18_45;
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
	
 i++;
loop_label_18_45:
 /* Loop 18 END */;
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
 /* Loop 19 BEGIN */
 i = 0;
loop_label_19_0:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_1:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_2:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_3:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_4:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_5:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_6:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_7:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_8:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_9:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_10:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_11:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_12:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_13:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_14:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_15:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_16:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_17:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_18:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_19:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_20:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_21:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_22:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_23:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_24:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_25:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_26:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_27:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_28:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_29:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_30:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_31:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_32:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_33:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_34:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_35:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_36:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_37:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_38:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_39:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_40:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_41:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_42:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_43:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_44:
		if (i == ev)
   goto loop_label_19_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_19_45:
 /* Loop 19 END */;
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
 /* Loop 20 BEGIN */
 i = 0;
loop_label_20_0:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_1:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_2:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_3:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_4:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_5:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_6:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_7:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_8:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_9:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_10:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_11:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_12:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_13:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_14:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_15:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_16:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_17:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_18:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_19:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_20:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_21:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_22:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_23:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_24:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_25:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_26:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_27:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_28:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_29:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_30:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_31:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_32:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_33:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_34:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_35:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_36:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_37:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_38:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_39:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_40:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_41:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_42:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_43:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_44:
		if (i == ev)
   goto loop_label_20_45;
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
	
 i++;
loop_label_20_45:
 /* Loop 20 END */;

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
 /* Loop 21 BEGIN */
 i = 0;
loop_label_21_0:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_1:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_2:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_3:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_4:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_5:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_6:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_7:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_8:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_9:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_10:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_11:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_12:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_13:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_14:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_15:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_16:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_17:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_18:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_19:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_20:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_21:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_22:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_23:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_24:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_25:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_26:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_27:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_28:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_29:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_30:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_31:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_32:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_33:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_34:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_35:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_36:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_37:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_38:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_39:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_40:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_41:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_42:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_43:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_44:
		if (i == ev)
   goto loop_label_21_45;
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
	
 i++;
loop_label_21_45:
 /* Loop 21 END */;
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
 /* Loop 22 BEGIN */
 i = 0;
loop_label_22_0:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_1:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_2:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_3:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_4:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_5:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_6:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_7:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_8:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_9:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_10:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_11:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_12:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_13:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_14:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_15:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_16:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_17:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_18:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_19:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_20:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_21:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_22:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_23:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_24:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_25:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_26:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_27:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_28:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_29:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_30:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_31:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_32:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_33:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_34:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_35:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_36:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_37:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_38:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_39:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_40:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_41:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_42:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_43:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_44:
		if (i == ev)
   goto loop_label_22_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_22_45:
 /* Loop 22 END */;
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
 /* Loop 23 BEGIN */
 i = 0;
loop_label_23_0:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_1:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_2:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_3:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_4:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_5:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_6:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_7:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_8:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_9:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_10:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_11:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_12:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_13:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_14:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_15:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_16:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_17:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_18:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_19:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_20:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_21:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_22:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_23:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_24:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_25:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_26:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_27:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_28:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_29:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_30:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_31:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_32:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_33:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_34:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_35:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_36:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_37:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_38:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_39:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_40:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_41:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_42:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_43:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_44:
		if (i == ev)
   goto loop_label_23_45;
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
	
 i++;
loop_label_23_45:
 /* Loop 23 END */;

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
 /* Loop 24 BEGIN */
 i = 0;
loop_label_24_0:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_1:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_2:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_3:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_4:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_5:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_6:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_7:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_8:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_9:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_10:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_11:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_12:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_13:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_14:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_15:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_16:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_17:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_18:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_19:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_20:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_21:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_22:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_23:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_24:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_25:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_26:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_27:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_28:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_29:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_30:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_31:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_32:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_33:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_34:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_35:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_36:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_37:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_38:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_39:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_40:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_41:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_42:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_43:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_44:
		if (i == ev)
   goto loop_label_24_45;
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
	
 i++;
loop_label_24_45:
 /* Loop 24 END */;
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
 /* Loop 25 BEGIN */
 i = 0;
loop_label_25_0:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_1:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_2:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_3:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_4:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_5:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_6:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_7:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_8:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_9:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_10:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_11:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_12:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_13:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_14:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_15:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_16:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_17:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_18:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_19:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_20:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_21:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_22:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_23:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_24:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_25:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_26:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_27:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_28:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_29:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_30:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_31:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_32:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_33:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_34:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_35:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_36:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_37:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_38:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_39:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_40:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_41:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_42:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_43:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_44:
		if (i == ev)
   goto loop_label_25_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_25_45:
 /* Loop 25 END */;
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
 /* Loop 26 BEGIN */
 i = 0;
loop_label_26_0:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_1:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_2:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_3:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_4:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_5:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_6:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_7:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_8:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_9:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_10:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_11:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_12:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_13:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_14:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_15:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_16:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_17:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_18:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_19:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_20:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_21:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_22:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_23:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_24:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_25:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_26:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_27:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_28:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_29:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_30:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_31:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_32:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_33:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_34:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_35:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_36:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_37:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_38:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_39:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_40:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_41:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_42:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_43:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_44:
		if (i == ev)
   goto loop_label_26_45;
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
	
 i++;
loop_label_26_45:
 /* Loop 26 END */;

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
 /* Loop 27 BEGIN */
 i = 0;
loop_label_27_0:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_1:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_2:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_3:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_4:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_5:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_6:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_7:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_8:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_9:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_10:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_11:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_12:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_13:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_14:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_15:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_16:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_17:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_18:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_19:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_20:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_21:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_22:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_23:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_24:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_25:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_26:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_27:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_28:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_29:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_30:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_31:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_32:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_33:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_34:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_35:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_36:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_37:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_38:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_39:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_40:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_41:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_42:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_43:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_44:
		if (i == ev)
   goto loop_label_27_45;
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
	
 i++;
loop_label_27_45:
 /* Loop 27 END */;
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
 /* Loop 28 BEGIN */
 i = 0;
loop_label_28_0:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_1:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_2:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_3:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_4:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_5:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_6:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_7:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_8:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_9:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_10:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_11:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_12:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_13:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_14:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_15:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_16:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_17:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_18:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_19:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_20:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_21:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_22:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_23:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_24:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_25:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_26:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_27:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_28:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_29:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_30:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_31:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_32:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_33:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_34:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_35:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_36:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_37:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_38:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_39:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_40:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_41:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_42:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_43:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_44:
		if (i == ev)
   goto loop_label_28_45;
		s = p->status[i];

		if (p->reg_written[i] == r) {
			rval = p->reg_write_val[i];
			ireg = (s >= INIT);
		}
	
 i++;
loop_label_28_45:
 /* Loop 28 END */;
	// iR >= iReg(r)
	ASSUME(ireg);
	p->memory_read[ev] = rval;

	// find CW
	iw = COMMIT;
 /* Loop 29 BEGIN */
 i = 0;
loop_label_29_0:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_1:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_2:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_3:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_4:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_5:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_6:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_7:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_8:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_9:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_10:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_11:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_12:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_13:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_14:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_15:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_16:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_17:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_18:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_19:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_20:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_21:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_22:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_23:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_24:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_25:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_26:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_27:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_28:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_29:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_30:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_31:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_32:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_33:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_34:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_35:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_36:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_37:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_38:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_39:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_40:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_41:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_42:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_43:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_44:
		if (i == ev)
   goto loop_label_29_45;
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
	
 i++;
loop_label_29_45:
 /* Loop 29 END */;

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
 /* Loop 30 BEGIN */
 i = 0;
loop_label_30_0:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_1:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_2:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_3:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_4:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_5:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_6:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_7:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_8:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_9:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_10:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_11:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_12:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_13:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_14:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_15:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_16:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_17:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_18:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_19:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_20:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_21:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_22:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_23:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_24:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_25:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_26:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_27:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_28:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_29:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_30:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_31:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_32:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_33:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_34:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_35:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_36:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_37:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_38:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_39:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_40:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_41:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_42:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_43:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_44:
		if (i == ev)
   goto loop_label_30_45;
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
	
 i++;
loop_label_30_45:
 /* Loop 30 END */;
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

 /* Loop 31 BEGIN */
 i = 0;
loop_label_31_0:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_1:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_2:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_3:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_4:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_5:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_6:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_7:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_8:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_9:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_10:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_11:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_12:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_13:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_14:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_15:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_16:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_17:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_18:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_19:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_20:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_21:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_22:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_23:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_24:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_25:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_26:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_27:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_28:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_29:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_30:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_31:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_32:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_33:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_34:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_35:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_36:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_37:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_38:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_39:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_40:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_41:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_42:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_43:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_44:
		if (i == ev)
   goto loop_label_31_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDY >= old-cDY, cDL, cDS, cISB, ctrl
		if (t == ACI || (t >= DMBSY && t <= DMBST))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_31_45:
 /* Loop 31 END */;

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
 /* Loop 32 BEGIN */
 i = 0;
loop_label_32_0:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_1:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_2:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_3:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_4:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_5:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_6:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_7:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_8:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_9:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_10:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_11:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_12:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_13:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_14:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_15:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_16:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_17:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_18:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_19:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_20:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_21:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_22:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_23:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_24:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_25:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_26:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_27:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_28:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_29:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_30:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_31:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_32:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_33:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_34:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_35:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_36:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_37:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_38:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_39:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_40:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_41:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_42:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_43:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_44:
		if (i == ev)
   goto loop_label_32_45;
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
	
 i++;
loop_label_32_45:
 /* Loop 32 END */;

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_DMBLD(struct proc_local_info *p, int ev)
{
	int ins;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == DMBLD && p->status[ev] == FETCH);

 /* Loop 33 BEGIN */
 i = 0;
loop_label_33_0:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_1:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_2:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_3:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_4:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_5:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_6:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_7:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_8:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_9:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_10:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_11:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_12:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_13:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_14:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_15:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_16:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_17:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_18:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_19:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_20:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_21:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_22:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_23:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_24:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_25:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_26:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_27:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_28:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_29:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_30:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_31:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_32:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_33:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_34:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_35:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_36:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_37:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_38:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_39:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_40:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_41:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_42:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_43:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_44:
		if (i == ev)
   goto loop_label_33_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDL >= cDY, ctrl, cR
		if (t == ACI || t == DMBSY || t <= LDAX)
			ASSUME(s == COMMIT);
	
 i++;
loop_label_33_45:
 /* Loop 33 END */;

	// mark as committed
	p->status[ev] = COMMIT;
}

void commit_DMBST(struct proc_local_info *p, int ev)
{
	int ins;
	int i, in, t, s;

	ins = p->events[ev];
	ASSUME(p->type[ins] == DMBST && p->status[ev] == FETCH);

 /* Loop 34 BEGIN */
 i = 0;
loop_label_34_0:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_1:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_2:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_3:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_4:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_5:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_6:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_7:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_8:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_9:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_10:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_11:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_12:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_13:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_14:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_15:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_16:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_17:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_18:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_19:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_20:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_21:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_22:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_23:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_24:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_25:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_26:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_27:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_28:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_29:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_30:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_31:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_32:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_33:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_34:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_35:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_36:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_37:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_38:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_39:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_40:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_41:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_42:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_43:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_44:
		if (i == ev)
   goto loop_label_34_45;
		in = p->events[i];
		t = p->type[in];
		s = p->status[i];

		// cDS >= cDY, ctrl, cW
		if (t == ACI || t == DMBSY || (t >= ST && t <= STLX))
			ASSUME(s == COMMIT);
	
 i++;
loop_label_34_45:
 /* Loop 34 END */;

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
 /* Loop 35 BEGIN */
 i = 0;
loop_label_35_0:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_1:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_2:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_3:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_4:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_5:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_6:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_7:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_8:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_9:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_10:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_11:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_12:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_13:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_14:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_15:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_16:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_17:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_18:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_19:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_20:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_21:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_22:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_23:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_24:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_25:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_26:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_27:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_28:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_29:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_30:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_31:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_32:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_33:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_34:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_35:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_36:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_37:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_38:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_39:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_40:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_41:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_42:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_43:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_44:
		if (i == ev)
   goto loop_label_35_45;
		s = p->status[i];
		if (p->reg_written[i] == r1) {
			v1 = p->reg_write_val[i];
			ir1 = (s >= INIT);
		}
		if (p->reg_written[i] == r2) {
			v2 = p->reg_write_val[i];
			ir2 = (s >= INIT);
		}
	
 i++;
loop_label_35_45:
 /* Loop 35 END */;
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
 /* Loop 36 BEGIN */
 i = 0;
loop_label_36_0:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_1:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_2:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_3:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_4:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_5:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_6:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_7:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_8:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_9:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_10:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_11:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_12:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_13:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_14:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_15:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_16:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_17:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_18:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_19:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_20:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_21:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_22:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_23:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_24:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_25:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_26:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_27:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_28:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_29:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_30:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_31:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_32:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_33:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_34:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_35:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_36:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_37:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_38:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_39:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_40:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_41:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_42:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_43:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_44:
		if (i == ev)
   goto loop_label_36_45;
		s = p->status[i];
		ASSUME(s == COMMIT);
	
 i++;
loop_label_36_45:
 /* Loop 36 END */;

	// mark as committed, and set done=1
	p->status[ev] = COMMIT;
	p->done = 1;
}

void *run_proc(void *pv)
{
	struct proc_local_info *p = (struct proc_local_info *)pv;
	int i, ev;
 /* Loop 37 BEGIN */
 i = 0;
loop_label_37_0:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_1:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_2:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_3:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_4:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_5:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_6:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_7:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_8:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_9:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_10:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_11:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_12:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_13:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_14:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_15:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_16:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_17:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_18:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_19:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_20:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_21:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_22:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_23:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_24:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_25:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_26:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_27:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_28:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_29:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_30:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_31:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_32:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_33:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_34:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_35:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_36:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_37:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_38:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_39:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_40:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_41:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_42:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_43:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_44:
		if (!p->allfetched && (get_decision() || p->cur_fill == 0)) {
			fetch_next_instr(p);
		} else {
			ev = get_rng(0,p->cur_fill-1);
			ASSUME(p->status[ev] != COMMIT);
			switch(ev) {
			case LD:
				(p->status[ev] == FETCH)?
					init_LD(p,ev) : commit_LD(p,ev);
    goto loop_label_37_45;
			case LDA:
				(p->status[ev] == FETCH)?
					init_LDA(p,ev) : commit_LDA(p,ev);
    goto loop_label_37_45;
			case LDX:
				(p->status[ev] == FETCH)?
					init_LDX(p,ev) : commit_LDX(p,ev);
    goto loop_label_37_45;
			case LDAX:
				(p->status[ev] == FETCH)?
					init_LDAX(p,ev) : commit_LDAX(p,ev);
    goto loop_label_37_45;
			case ST:
				(p->status[ev] == FETCH)?
					init_ST(p,ev) : commit_ST(p,ev);
    goto loop_label_37_45;
			case STL:
				(p->status[ev] == FETCH)?
					init_STL(p,ev) : commit_STL(p,ev);
    goto loop_label_37_45;
			case STX:
				commit_STX(p,ev);
    goto loop_label_37_45;
			case STLX:
				commit_STLX(p,ev);
    goto loop_label_37_45;
			case ASSIGN:
				(p->status[ev] == FETCH)?
					init_ASSIGN(p,ev) : commit_ASSIGN(p,ev);
    goto loop_label_37_45;
			case DMBSY:
				commit_DMBSY(p,ev);
    goto loop_label_37_45;
			case ISB:
				commit_ISB(p,ev);
    goto loop_label_37_45;
			case DMBLD:
				commit_DMBLD(p,ev);
    goto loop_label_37_45;
			case DMBST:
				commit_DMBST(p,ev);
    goto loop_label_37_45;
			case LABEL:
				// just mark as committed
				p->status[ev] = COMMIT;
    goto loop_label_37_45;
			case ACI:
				commit_ACI(p,ev);
    goto loop_label_37_45;
			case TERM:
				commit_TERM(p,ev);
    goto loop_label_37_45;
			}
		}

		if (p->done)
   goto loop_label_37_45;
	
 i++;
loop_label_37_45:
 /* Loop 37 END */;

	// we don't want runs to overflow NTIME time units
	ASSUME(p->done);

	// collect final register values
	// these will be used by the final check
 /* Loop 38 BEGIN */
 i = 0;
loop_label_38_0:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_1:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_2:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_3:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_4:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_5:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_6:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_7:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_8:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_9:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_10:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_11:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_12:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_13:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_14:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_15:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_16:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_17:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_18:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_19:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_20:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_21:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_22:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_23:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_24:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_25:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_26:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_27:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_28:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_29:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_30:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_31:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_32:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_33:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_34:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_35:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_36:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_37:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_38:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_39:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_40:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_41:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_42:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_43:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_44:
		if (i == p->cur_fill)
   goto loop_label_38_45;
		if (p->reg_written[i] != -1)
			p->registers[p->reg_written[i]] = p->reg_write_val[i];
	
 i++;
loop_label_38_45:
 /* Loop 38 END */;

	// finished!
	p->finished = 1;
}

int main(int argc, char **argv)
{
	init_mark_pre();
	init_all_procs_pre();
	init_procs();
	init_memory_and_reg_other();

	pthread_t tids[NPROC];
	int i;
 /* Loop 39 BEGIN */
  i = 0;
loop_label_39_0:
		pthread_create(&tids[i], NULL, run_proc, (void *)&procs[i]);
  i++;
loop_label_39_1:
		pthread_create(&tids[i], NULL, run_proc, (void *)&procs[i]);
  i++;
loop_label_39_2:
  /* Loop 39 END */;

 /* Loop 40 BEGIN */
  i = 0;
loop_label_40_0:
		pthread_join(tids[i], NULL);
  i++;
loop_label_40_1:
		pthread_join(tids[i], NULL);
  i++;
loop_label_40_2:
  /* Loop 40 END */;

	check_conditions();

	return 0;
}