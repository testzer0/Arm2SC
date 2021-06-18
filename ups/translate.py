import os
import sys
from enum import Enum

#############################################
# 			     translate.py 			    #
# ========================================= #
# Translates an input AArch64 multi-thread- #
# ed program to an equivalent SC program by #
# making use of context bounding. 			#
#############################################

if len(sys.argv) == 1:
	infile = os.path.join(os.getcwd(), 'tests/2+2W.litmus')
	outfile = os.path.join(os.getcwd(), 'ups/translated.c')
elif len(sys.argv) == 3:
	infile = os.path.join(os.getcwd(), 'tests/'+sys.argv[1])
	outfile = os.path.join(os.getcwd(), 'ups/'+sys.argv[2])
else:
	infile = os.path.join(os.getcwd(), sys.argv[1]+'/'+sys.argv[2])
	outfile = os.path.join(os.getcwd(), 'ups/'+sys.argv[3])

preamblefile = os.path.join(os.getcwd(), 'ups/preamble.c')

class InstrType(Enum):
	LD = 1
	LDA = 2
	LDX = 3
	LDAX = 4
	ST = 5
	STL = 6
	STX = 7
	STLX = 8
	ASSIGN = 9
	DMBSY = 10
	ISB = 11
	DMBLD = 12
	DMBST = 13
	LABEL = 14
	ACI = 15

class Expression:
	# A simple class for an expression
	# Holds the types and values of two operands, and the operation in the string form
	# Type 0 = register, type 1 = integer, and type -1 = does not exist
	def __init__(self, type1, val1, type2=-1, val2=-1, op=-1):
		self.type1 = type1
		self.type2 = type2
		self.val1 = val1
		self.val2 = val2
		self.op = op

	def get_regs(self):
		# returns the list of used registers
		regs = []
		if (self.type1 == 0):
			regs.append(self.val1)
		if (self.type2 == 0):
			regs.append(self.val2)
		return regs

	def get_exp(self, p):
		# returns the expression in string form, given the process
		if (self.type2 == -1):
			# only one argument
			if (self.type1 == 0):
				ret = f"REGP({p},{self.val1})"
			else:
				ret = str(self.val1)
		else:
			ret = "("
			if (self.type1 == 0):
				ret += f"REGP({p},{self.val1})"
			else:
				ret += str(self.val1)
			ret += " " + str(self.op) + " "
			if (self.type2 == 0):
				ret += f"REGP({p},{self.val2})"
			else:
				ret += str(self.val2)
			ret += ")"
		return ret

nregs = 16
addrsize = 64
nproc = 0
ncontext = 10 # later read in as argument

code = []
incode = []
procwise_label_to_index_map = []
procwise_indices = []
init_addr_with_zeros = True							# whether to initialize addr with zeroes
init_reg = []
init_addr_diff = {}
final_conds = []									# final conditions

def add_indented_code(line, indentlevel=0):
	### Add code with the given level of indentation ###
	# One indent is assumed to be 4 spaces
	code.append((" "*4*indentlevel)+line)

def add_preamble(indentlevel=0):
	### Preamble code ### 
	code.append(f"#define NPROC {nproc}")
	with open(preamblefile) as f:
		for line in f:
			code.append(line.rstrip())

def add_init_memory_and_reg_other(indentlevel=0):
	add_indented_code("void init_memory_and_reg_other() {", indentlevel)
	if not init_addr_with_zeros:
		add_indented_code("init_memory_random();", indentlevel+1);
	for addr, value in init_addr_diff.items():
		add_indented_code(f"memory[{addr}] = {value};", indentlevel+1);
	add_indented_code("", indentlevel+1)
	for istmt in init_reg:
		add_indented_code(istmt, indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)


def add_ST(p, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = ST;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_STL(p, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = STL;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_STX(p, rdoubleprime, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = STX;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rdoubleprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o3[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t3[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_STLX(p, rdoubleprime, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = STLX;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rdoubleprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o3[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t3[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_assign(p, r, exp, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = ASSIGN;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {exp.val1};", indentlevel)
	if (exp.type1 == 0):	#REG
		add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	else:
		add_indented_code(f"procs[{p}].t2[{i}] = NUM;", indentlevel)
	add_indented_code(f"procs[{p}].o3[{i}] = {exp.val2};", indentlevel)
	if (exp.type2 == -1):	#EMPTY
		add_indented_code(f"procs[{p}].t3[{i}] = EMPTY;", indentlevel)
	elif (exp.type2 == 0):	#REG
		add_indented_code(f"procs[{p}].t3[{i}] = REG;", indentlevel)
	else:
		add_indented_code(f"procs[{p}].t3[{i}] = REG;", indentlevel)

	if exp.op == '+':
		add_indented_code(f"procs[{p}].operation[{i}] = PLUS;", indentlevel)
	elif exp.op == '-':
		add_indented_code(f"procs[{p}].operation[{i}] = MINUS;", indentlevel)
	elif exp.op == '*':
		add_indented_code(f"procs[{p}].operation[{i}] = MULT;", indentlevel)
	elif exp.op == '^':
		add_indented_code(f"procs[{p}].operation[{i}] = EOR;", indentlevel)
	elif exp.op == '==':
		add_indented_code(f"procs[{p}].operation[{i}] = EQ;", indentlevel)
	elif exp.op == '!=':
		add_indented_code(f"procs[{p}].operation[{i}] = NEQ;", indentlevel)
	elif exp.op == '>=':
		add_indented_code(f"procs[{p}].operation[{i}] = GEQ;", indentlevel)
	elif exp.op == '<=':
		add_indented_code(f"procs[{p}].operation[{i}] = LEQ;", indentlevel)
	else:
		# assume op is '=='
		add_indented_code(f"procs[{p}].operation[{i}] = EQ;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_LD(p, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = LD;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_LDA(p, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = LDA;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_LDX(p, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = LDX;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_LDAX(p, rprime, r, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = LDAX;", indentlevel)
	add_indented_code(f"procs[{p}].o1[{i}] = {rprime};", indentlevel)
	add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].o2[{i}] = {r};", indentlevel)
	add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_dmb_sy(p, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = DMBSY;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_isb(p, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = ISB;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_dmb_ld(p, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = DMBLD;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);


def add_dmb_st(p, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = DMBST;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel);
	add_indented_code("", indentlevel);

def add_term(p, indentlevel=0):
	i = procwise_indices[p];
	procwise_indices[p] += 1;

	add_indented_code(f"procs[{p}].type[{i}] = TERM;", indentlevel)
	add_indented_code(f"procs[{p}].next1[{i}] = -1;", indentlevel);
	add_indented_code("", indentlevel);

def add_check_conditions(indentlevel=0):
	add_indented_code("void check_conditions() {", indentlevel)
	add_indented_code("for (int i = 0; i < NPROC; i++)", indentlevel+1)
	add_indented_code("ASSUME(procs[i].finished);", indentlevel+2)
	add_indented_code("if (", indentlevel+1)
	for cnd in final_conds:
		add_indented_code(cnd + " &&", indentlevel+2)
	add_indented_code("1)", indentlevel+1)
	add_indented_code("ASSERT(0);", indentlevel+2)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)

def write_translated_code():
	### Write the code to the output file ###
	with open(outfile,'w+') as file:
		file.write('\n'.join(str(line) for line in code))

class Instruction:
	def __init__(self, p, i_type, op1=None, op2=None, op3=None):
		self.p = p
		self.i_type = i_type
		self.op1 = op1
		self.op2 = op2
		self.op3 = op3

def parse_from_litmus(ifile):
	global nproc, incode, procwise_label_to_index_map
	var_set = set()										# global variable list
	process_local_regs = []								# process local register list
	mem_mapping = {}									# variables to values
	process_local_mapping = []							# registers to variable (addresses)	
	
	process_reg_nums = []								# number of per-proc registers
	process_reg_to_num_map = []							# assign numbers to registers		
	var_to_addr_map = {}								# global variable to address mapping	

	init_conds = [] 									# global var initial values

	process_private_regs = []

	with open(ifile) as f:
		content = [x.strip() for x in f.readlines()]
	cur_index = 0
	
	# find the '{'
	while content[cur_index] != "{":
		cur_index += 1
	cur_index += 1

	while content[cur_index] != "}":
		thisline = [part.strip() for part in content[cur_index].split(';')[:-1]]
		# print(thisline)

		for part in thisline:
			if ':' in part:								# register initial values
				subparts1 = part.split(':')
				index = int(subparts1[0])				# which process
				subparts2 = subparts1[1].split('=')		
				while nproc <= index:
					process_local_regs.append(set())
					process_local_mapping.append({})
					process_reg_to_num_map.append({})
					incode.append([])
					procwise_indices.append(0)
					procwise_label_to_index_map.append({})
					process_reg_nums.append(2)			# register 0,1 are "private" registers for CMP stmts
					process_private_regs.append(-1)
					nproc += 1

				process_local_regs[index].add(subparts2[0][1:])
				var_set.add(subparts2[1])
				process_local_mapping[index][subparts2[0][1:]] = subparts2[1]
			else:										# variable initial values
				subparts = part.split('=')
				var_set.add(subparts[0])
				mem_mapping[subparts[0]] = int(subparts[1])

		cur_index += 1

	cur_index += 2 										# skip over the '}' and PO|P1|... lines

	vind = 0
	for var in var_set:
		var_to_addr_map[var] = vind
		vind += 1

	# assign local registers numbers - this may miss some
	# registers that we will find first referred to in the code.
	# But for them, we'll simply allocate higher counts on-the-fly
	for proc in range(nproc):
		for reg in process_local_regs[proc]:
			process_reg_to_num_map[proc][reg] = process_reg_nums[proc]
			process_reg_nums[proc] += 1
		
		# Add register assignments to output code
		for reg, var in process_local_mapping[proc].items():
			istmt = f"procs[{proc}].registers[{reg}] = {var_to_addr_map[var]};"
			init_reg.append(istmt)

	while not content[cur_index].startswith("exists"):
		parts = [part.strip() for part in content[cur_index][:-1].split('|')]
		for proc in range(nproc):
			# need to remove spaces
			part = parts[proc].split(' ')
			operation = part[0]
			if operation in ['ISB','NOP','']:
				operands = ['']
			elif ':' in operation:
				# label
				procwise_label_to_index_map[operation[:-1]] = len(incode[proc])
				stmt = Instruction(proc, InstrType.LABEL.value, operation[:-1])
				incode[proc].append(stmt)
				operation = ''				# so that the file isn't blacklisted
			else:
				operands =  part[1].split(',')
				if len(operands) == 2 and not operands[1]:
					operands[1] = part[2]

			# these litmus tests have very simple addresses - simple locations

			if operation in ['LDR','LDAR','LDAXR','LDXR']:
				operands[0] = operands[0][1:]
				if len(operands) > 2:
					# has the offset and stuff
					operands[1] = operands[1][2:]
					if ']' in operands[2]:
						operands[2] = operands[2][1:-1]
					else:
						operands[2] = operands[2][1:]
					# Now add an assign statement to the private register
					# followed by a load
					for operand in operands:
						if operand not in process_local_regs[proc]:
							process_local_regs[proc].add(operand)
							process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
							process_reg_nums[proc] += 1
					if process_private_regs[proc] == -1:
						process_private_regs[proc] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					exp = Expression(0, process_reg_to_num_map[proc][operands[1]]	\
						, 0, process_reg_to_num_map[proc][operands[2]],'+')
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, process_private_regs[proc], exp)
					stmt2 = Instruction(proc, InstrType[operation[:-1]].value, 	\
						process_reg_to_num_map[proc][operands[0]],	\
						process_private_regs[proc])
					incode[proc].append(stmt1)
					incode[proc].append(stmt2)
				else:
					operands[1] = operands[1][2:-1]
					for operand in operands:
						if operand not in process_local_regs[proc]:
							process_local_regs[proc].add(operand)
							process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
							process_reg_nums[proc] += 1
					stmt = Instruction(proc, InstrType[operation[:-1]].value, 	\
						process_reg_to_num_map[proc][operands[0]],	\
						process_reg_to_num_map[proc][operands[1]])
					incode[proc].append(stmt)
			elif operation in ['STR', 'STLR']:
				operands[0] = operands[0][1:]
				if len(operands) > 2:
					# has the offset and stuff
					operands[1] = operands[1][2:]
					if ']' in operands[2]:
						operands[2] = operands[2][1:-1]
					else:
						operands[2] = operands[2][1:]
					# Now add an assign statement to the private register
					# followed by a load
					for operand in operands:
						if operand not in process_local_regs[proc]:
							process_local_regs[proc].add(operand)
							process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
							process_reg_nums[proc] += 1
					if process_private_regs[proc] == -1:
						process_private_regs[proc] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					exp = Expression(0, process_reg_to_num_map[proc][operands[1]]	\
						, 0, process_reg_to_num_map[proc][operands[2]],'+')
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, process_private_regs[proc], exp)
					stmt2 = Instruction(proc, InstrType[operation[:-1]].value, 	\
						process_private_regs[proc], process_reg_to_num_map[proc][operands[0]])
					incode[proc].append(stmt1)
					incode[proc].append(stmt2)
				else:
					operands[1] = operands[1][2:-1]
					for operand in operands:
						if operand not in process_local_regs[proc]:
							process_local_regs[proc].add(operand)
							process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
							process_reg_nums[proc] += 1
					stmt = Instruction(proc, InstrType[operation[:-1]].value,	\
						process_reg_to_num_map[proc][operands[1]], process_reg_to_num_map[proc][operands[0]])
					incode[proc].append(stmt)
			elif operation in ['STXR', 'STLXR']:
				operands[0] = operands[0][1:]
				operands[1] = operands[1][1:]
				operands[2] = operands[2][2:-1]
				for operand in operands:
					if operand not in process_local_regs[proc]:
						process_local_regs[proc].add(operand)
						process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
				stmt = Instruction(proc, InstrType[operation[:-1]].value,	\
					process_reg_to_num_map[proc][operands[0]], process_reg_to_num_map[proc][operands[2]],	\
					process_reg_to_num_map[proc][operands[1]])
				incode[proc].append(stmt)
			elif operation == "DMB":
				stmt = Instruction(proc, InstrType[operation+operands[0]].value)
				incode[proc].append(stmt)
			elif operation == "ISB":
				stmt = Instruction(proc, InstrType.ISB.value)
				incode[proc].append(stmt)
			elif operation == "MOV":
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1

				if operands[1][0] == '#': 
					exp = Expression(1, int(operands[1][1:]))
					stmt = Instruction(proc, InstrType.ASSIGN.value,	\
						process_reg_to_num_map[proc][operands[0]], exp)
				else:
					operands[1] = operands[1][1:]
					if operands[1] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[1])
						process_reg_to_num_map[proc][operands[1]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					exp = Expression(0, process_reg_to_num_map[proc][operands[1]])
					stmt = Instruction(proc, InstrType.ASSIGN.value,	\
						process_reg_to_num_map[proc][operands[0]], exp)
				incode[proc].append(stmt)
			elif operation == "CMP":
				if operands[0][0] == '#':
					exp = Expression(1, int(operands[0][1:]))
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, 0, exp)
				else:
					operands[0] = operands[0][1:]
					if operands[0] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[0])
						process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					exp = Expression(0, process_reg_to_num_map[proc][operands[0]])
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, 0, exp)
				if operands[1][0] == '#':
					exp = Expression(1, int(operands[1][1:]))
					stmt2 = Instruction(proc, InstrType.ASSIGN.value, 1, exp)
				else:
					operands[1] = operands[1][1:]
					if operands[1] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[1])
						process_reg_to_num_map[proc][operands[1]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					exp = Expression(0, process_reg_to_num_map[proc][operands[1]])
					stmt2 = Instruction(proc, InstrType.ASSIGN.value, 1, exp)
				incode[proc].append(stmt1)
				incode[proc].append(stmt2)
			elif operation == "B.EQ":
				stmt = Instruction(proc, InstrType.ACI.value, "BEQ", operands[0])
				incode[proc].append(stmt)
			elif operation == "EOR":
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = operands[1][1:]
				else:
					type1 = 0
					operands[1] = operands[1][1:]
					if operands[1] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[1])
						process_reg_to_num_map[proc][operands[1]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = operands[2][1:]
				else:
					type2 = 0
					if operands[2] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[2])
						process_reg_to_num_map[proc][operands[2]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					operands[2] = operands[2][1:]
				exp = Expression(type1, process_reg_to_num_map[proc][operands[1]], type2,	\
					process_reg_to_num_map[proc][operands[2]], '^')
				stmt = Instruction(proc, InstrType.ASSIGN.value,	\
					process_reg_to_num_map[proc][operands[0]], exp)
				incode[proc].append(stmt)
			elif operation == "CBZ":
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1
				stmt = Instruction(proc, InstrType.ACI.value, "CBZ",	\
					process_reg_to_num_map[proc][operands[0]], operands[1])
				incode[proc].append(stmt)
			elif operation == "CBNZ":
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1
				stmt = Instruction(proc, InstrType.ACI.value, "CBNZ",	\
					process_reg_to_num_map[proc][operands[0]], operands[1])
				incode[proc].append(stmt)
		cur_index += 1

	for var, value in mem_mapping.items():
		init_addr_diff[var_to_addr_map[var]] = value

	# extract the conditions
	# for now we support ONLY and symbols (/\): if you want OR symbols,
	# you're out of luck
	if content[cur_index] == "exists":
		cur_index += 1
		conditions = content[cur_index][1:-1].split('/')
	else:
		line = content[cur_index][6:].strip()
		conditions = line[1:-1].split('/')
	for condition in conditions:
		if condition[0] == '\\':
			# lingering '\' from the /\
			condition = condition[1:]
		condition = condition.strip()
		if ':' in condition:
			# local constraint on a register
			# Format: LOCAL <PROCID> <REGNO> <EXPECTED_VALUE>
			parts = condition.split(':')
			proc = int(parts[0])
			subparts = parts[1].split('=')
			subparts[0] = subparts[0][1:]

			if subparts[0] not in process_local_regs[proc]:
				process_local_regs[proc].add(subparts[0])
				process_reg_to_num_map[proc][subparts[0]] = process_reg_nums[proc]
				process_reg_nums[proc] += 1

			istmt = f"(REGP({proc},{process_reg_to_num_map[proc][subparts[0]]}) == {int(subparts[1])})"
			final_conds.append(istmt)
		else:
			# global constraint on a variable
			# Format: GLOBAL <ADDRESS> <EXPECTED_VALUE>
			parts = condition.split('=')

			if parts[0] not in var_set:
				var_set.add(parts[0])
				var_to_addr_map = vind
				vind += 1

			istmt = f"(MU({var_to_addr_map[parts[0]]},NCONTEXT-1) == {int(parts[1])})"
			final_conds.append(istmt)

def add_aci_instruction(instr, indentlevel=0):
	p = instr.p
	if (instr.op1 == "BEQ"):
		i = procwise_indices[p];
		procwise_indices[p] += 1;

		dest = procwise_label_to_index_map[p][instr.op2]

		add_indented_code(f"procs[{p}].type[{i}] = ACI;", indentlevel)
		add_indented_code(f"procs[{p}].o1[{i}] = 0;", indentlevel)
		add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
		add_indented_code(f"procs[{p}].o2[{i}] = 0;", indentlevel)
		add_indented_code(f"procs[{p}].t2[{i}] = REG;", indentlevel)
		add_indented_code(f"procs[{p}].operation[{i}] = EQ;", indentlevel)
		add_indented_code(f"procs[{p}].next1[{i}] = {dest};", indentlevel)
		add_indented_code(f"procs[{p}].next2[{i}] = {i+1};", indentlevel);
		add_indented_code("", indentlevel);
	elif (instr.op1 == "CBZ"):
		i = procwise_indices[p];
		procwise_indices[p] += 1;

		dest = procwise_label_to_index_map[p][instr.op3]

		add_indented_code(f"procs[{p}].type[{i}] = ACI;", indentlevel)
		add_indented_code(f"procs[{p}].o1[{i}] = {instr.op2};", indentlevel)
		add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
		add_indented_code(f"procs[{p}].o2[{i}] = 0;", indentlevel)
		add_indented_code(f"procs[{p}].t2[{i}] = NUM;", indentlevel)
		add_indented_code(f"procs[{p}].operation[{i}] = EQ;", indentlevel)
		add_indented_code(f"procs[{p}].next1[{i}] = {dest};", indentlevel)
		add_indented_code(f"procs[{p}].next2[{i}] = {i+1};", indentlevel);
		add_indented_code("", indentlevel);
	elif (instr.op1 == "CBNZ"):
		i = procwise_indices[p];
		procwise_indices[p] += 1;

		dest = procwise_label_to_index_map[p][instr.op3]

		add_indented_code(f"procs[{p}].type[{i}] = ACI;", indentlevel)
		add_indented_code(f"procs[{p}].o1[{i}] = {instr.op2};", indentlevel)
		add_indented_code(f"procs[{p}].t1[{i}] = REG;", indentlevel)
		add_indented_code(f"procs[{p}].o2[{i}] = 0;", indentlevel)
		add_indented_code(f"procs[{p}].t2[{i}] = NUM;", indentlevel)
		add_indented_code(f"procs[{p}].operation[{i}] = NEQ;", indentlevel)
		add_indented_code(f"procs[{p}].next1[{i}] = {dest};", indentlevel)
		add_indented_code(f"procs[{p}].next2[{i}] = {i+1};", indentlevel);
		add_indented_code("", indentlevel);

def add_instruction(instr, indentlevel=0):
	# labels and goto's not handled yet
	if instr.i_type == InstrType.ACI.value:
		add_aci_instruction(instr, indentlevel)
	elif instr.i_type == InstrType.LABEL.value:
		# simply add a dummy instruction marked as LABEL
		i = procwise_indices[p];
		procwise_indices[p] += 1;
		add_indented_code(f"procs[{p}].type[{i}] = LABEL;", indentlevel)
		add_indented_code(f"procs[{p}].next1[{i}] = {i+1};", indentlevel)
		add_indented_code("", indentlevel)
	elif instr.i_type == InstrType.LD.value:
		add_LD(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.LDA.value:
		add_LDA(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.LDX.value:
		add_LDX(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.LDAX.value:
		add_LDAX(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.ST.value:
		add_ST(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.STL.value:
		add_STL(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.STX.value:
		add_STX(instr.p, instr.op1, instr.op2, instr.op3, indentlevel)
	elif instr.i_type == InstrType.STLX.value:
		add_STLX(instr.p, instr.op1, instr.op2, instr.op3, indentlevel)
	elif instr.i_type == InstrType.ASSIGN.value:
		add_assign(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.DMBSY.value:
		add_dmb_sy(instr.p, indentlevel)
	elif instr.i_type == InstrType.ISB.value:
		add_isb(instr.p, indentlevel)
	elif instr.i_type == InstrType.DMBLD.value:
		add_dmb_ld(instr.p, indentlevel)
	elif instr.i_type == InstrType.DMBST.value:
		add_dmb_st(instr.p, indentlevel)

def translate_code(indentlevel=0):
	add_preamble()
	add_indented_code("void init_procs() {", indentlevel)
	for p in range(nproc):
		# start cnt for this process at some non-deterministic context
		add_indented_code(f"// Process {p} BEGIN", indentlevel+1)
		for instr in incode[p]:
			add_instruction(instr, indentlevel+1)
		add_term(p,indentlevel+1)
		add_indented_code(f"// Process {p} END", indentlevel+1)
		add_indented_code("", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)
	add_init_memory_and_reg_other()

parse_from_litmus(infile)
translate_code()
write_translated_code()
