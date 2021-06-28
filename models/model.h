#ifndef MODEL_H_
#define MODEL_H_

// #define DEBUG
// #define BIAS

#include <vector>
#include <deque>
#include <stdlib.h>
#include <mutex>
#include <fstream>
#include "defines.h"

using namespace std;			// Maybe we shouldnt?

struct event{
	// Event metadata

	uint32_t 	event_num;		// Helps determine po-order; is unique per-process to the event
								// Every process assigns event_no's in increasing order
	ins_t 		ins_type;		// Instruction type; stored here for quick access
	struct instruction *instr;	// Pointer to the instruction of which the event is an instance
	proc_t 		proc;			// ID of process to which the event belongs
	status_t 	status;			// 0 = fetch, 1 = init, 2 = commit

	uint32_t 	result;			// event result (that was written or read/ truth value for aci)
	uint32_t 	exc_success;	// success indicator (0/1) for store exclusive instructions
	uint32_t 	addr_final; 	// Address' evaluated value (if none, then 0xFFFFFFFF)
								// Used to check for po-loc constraints

	// Event relations
	vector<struct event *> addr_dep; // events on which this one is addr-dependent
	vector<struct event *> data_dep; // events on which this one is data-dependent
	struct event *ctrl_dep; 	// event on which this one is ctrl-dependent - do we need more than one?
	struct event *rf;			// event (if any) from which this one read its value

	// Event index in the events vector of its process
	int 		index;
};

struct op_parse_tree_node {
	// Node for building parse tree of an operand
	parse_node_type	type;		// Type of node
	op_type 	 	op;			// Operation type (if is an op)
	uint32_t 		value;		// RegID if register and literal value if of that type
	struct op_parse_tree_node *left, *right; // Children, if of type op
};

struct instruction {			// An instruction in the instruction tree with at most 2 children
	// Instruction metadata
	uint32_t 	instr_id;		// ID of the instruction
	proc_t 		parent_proc;	// ID of parent process
	ins_t 		ins_type;		// Type of instruction
	struct instruction *parent;	// Parent of the instruction in the instruction tree of parent_proc (NULL if root)
	struct instruction *childl; // The left child if has two children; the only child if has one child; else NULL
	struct instruction *childr; // The right child if has two children; else NULL
	// uint32_t 	ins_dfs_in;		// dfs 'in' time in tree - is this required?
	// uint32_t 	ins_dfs_out; 	// dfs 'out' time: the two together define po-order - is this required?

	// NOTE: If the instrucion is an ACI statement childl is for the "TRUE" branch

	// Operands of the instruction (if they exist)
	struct op_parse_tree_node 	*operand1;	// Register ID or address of op1
	struct op_parse_tree_node	*operand2;	// Register ID or address of op2
	uint32_t 	reg_for_exc_st;				// For store exclusive type of instructions, the register
	op_type 	optype;						// Operation type for ACI?

	// The following are helpful since they will be used often
	// even though they can be reconstructed from the operands
	vector<uint32_t> regs_data;				// The registers read by this instruction for data
	vector<uint32_t> regs_addr;				// The registers read by this instruction for addr
	uint32_t reg_written; 					// The register written by this instruction
};

struct random_execution_args{
	uint32_t *regs_to_fill;
	const char *testname;
	double fetch_prob;
	int which_process;
};

class process{
public:
	// No need for lock because only one thread mutates a process's structures.
	// Process metadata
	proc_t		proc_id;		// ID of the process
	uint32_t  	next_event_num; // Next event number to be assigned
	bool 		finished; 		// Whether all instructions of this process have committed
	uint32_t 	regs[NREGS]; 	// Registers: these are local to processes
	bool 		have_taken_wrong_branch; 	// Whether we have mispredicted an ACI instruction.

	// The instruction tree of the process
	struct instruction *ins_tree_root; 		// Root of the instruction tree
	struct instruction *max_i[2]; 			// The set of instructions which can be fetched next

	// Event related stuff
	vector<struct event *> active_events; 	// The set of currently active events (NOT sorted by po)
	struct event *closest_write[MEMSIZE];	// The latest write for each address location
	struct event *closest_reg_write[NREGS]; // The latest instruction that writes to that register,
											// updated when instructions are FETCHed.
	struct event *closest_aci_event; 		// The latest aci event
	struct event *last_fetched_event;		// Last fetched event

	// functions
	process(proc_t pid);				// constructor
	int add_event(struct event *e); 	// Adds event to set of active events and returns index 
	int remove_event(struct event *e); 	// Removes event from global set of active events,
						 				// returns 0 on success, and a negative number on failure.

	// helper predicates
	// mostly not used directly
	bool all_dmb_lds(struct event *e);
	bool all_dmb_sts(struct event *e);
	bool all_dmb_sys(struct event *e);
	bool all_writes(struct event *e);
	bool all_reads(struct event *e);
	bool all_syncs(struct event *e);
	bool all_srels(struct event *e);
	bool all_lacq_init(struct event *e);
	bool all_lacqs(struct event *e);
	bool all_mem(struct event *e);
	bool all_barriers(struct event *e);
	bool init_cnd(struct event *e);
	bool isb_cnd(struct event *e);
	bool com_cnd(struct event *e);
	bool valid_cnd(struct event *e);

	// the following predicates are better optimized
	// than the ones above
	bool nonacq_read_init_cnd(struct event *e);
	bool acq_read_init_cnd(struct event *e);
	bool st_init_cnd(struct event *e);
	bool stl_init_cnd(struct event *e);
	bool read_com_cnd(struct event *e);
	bool non_exc_write_com_cnd(struct event *e);
	bool stx_com_cnd(struct event *e);
	bool stlx_com_cnd(struct event *e);
	bool isb_com_cnd(struct event *e);
	bool dmb_ld_com_cnd(struct event *e);
	bool dmb_st_com_cnd(struct event *e);
	bool dmb_sy_com_cnd(struct event *e);
	bool aci_com_cnd(struct event *e);
	bool assign_init_cnd(struct event *e);
	bool assign_com_cnd(struct event *e);

	// instructions to perform transitions
	struct event *fetch_next_instr(struct instruction *next_ins);
	struct event *fetch_next_instr_nondet();
	void try_resolving_addresses();
	inline struct event *get_closest_write(struct event *e);
	uint32_t init_nonacq_read(struct event *e); 
	uint32_t init_acq_read(struct event *e);	
	uint32_t com_read(struct event *e);
	uint32_t init_st(struct event *e);
	uint32_t init_stl(struct event *e);
	uint32_t com_non_exc_write(struct event *e);
	uint32_t com_stx(struct event *e);
	uint32_t com_stlx(struct event *e);
	uint32_t com_isb(struct event *e);
	uint32_t com_dmb_ld(struct event *e);
	uint32_t com_dmb_st(struct event *e);
	uint32_t com_dmb_sy(struct event *e);
	uint32_t com_aci(struct event *e);
	uint32_t com_term(struct event *e);
	uint32_t init_assign(struct event *e);
	uint32_t com_assign(struct event *e);
	
	uint32_t take_next_possible_transition(struct event *e);

	// Random execution
	void random_execution(struct random_execution_args *args);

	// Read in the instructions
	void read_in_code(const char *filename);
};

struct event *global_memory[MEMSIZE];	// Global memory - *actual* size = MEMSIZE * sizeof(reg_t)
proc_t mark[MEMSIZE];					// mark for load/store exclusive instructions
std::mutex global_mutex;				// mutex which MUST be held for accessing global_memory or mark
uint32_t nproc; 						// number of processors
vector<struct process> processes;		// the processes

vector<uint32_t> get_register_deps(struct op_parse_tree_node *n);
void fill_read_write_regs(struct instruction *ins);
inline bool try_to_resolve_address(struct event *e, struct process *proc);
uint32_t evaluate_exp(struct op_parse_tree_node *n, uint32_t regvals[NREGS]);
inline event *read_global_memory(uint32_t index, uint32_t proc_id);
inline bool write_global_memory(uint32_t index, event *e);
inline bool update_mark(uint32_t index, event *e);
void init_global_memory(const char *filename);
bool check_final_conditions(const char *filename, uint32_t **process_regs);

inline void *malloc_to_calloc(size_t size)
{
   return calloc(1, size);
}


void cleanup();

#endif