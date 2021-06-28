import os
import sys


##########################################
#           litmus_read.py 			     #
#									     #
# Reads in litmus tests from the 'tests' #
# folder and convert it to per-process   #
# code that can be read by processes in  #
# model.cc/.h. 							 #
##########################################

# op_name = {'LDR':'LD', 'STR':'ST', 'LDXR':'LDX', 'STXR':'STX',				\
#  		    'LDAR': 'LDA', 'STLR':'STL', 'LDAXR':'LDAX', 'STLXR':'STLX'}
# the name simply removes the last letter, 'R'

blacklist = set()

maxregs = 0

if len(sys.argv) > 1:
	testdir = os.path.join(os.getcwd(), sys.argv[1])
	outdir = os.path.join(os.getcwd(), sys.argv[2])
	bfile = open(os.path.join(os.getcwd(), sys.argv[3]), 'w+')
else:
	testdir = os.path.join(os.getcwd(), 'other_tests')
	outdir = os.path.join(os.getcwd(), 'other_cctests')
	bfile = open(os.path.join(os.getcwd(),"blacklist_others.txt"), 'w+')

def do_convert(filename):
	infile = os.path.join(testdir, filename)
	num_processes = 0

	var_set = set()										# global variable list
	process_local_regs = []								# process local register list
	mem_mapping = {}									# variables to values
	process_local_mapping = []							# registers to variable (addresses)	
	
	process_reg_nums = []								# number of per-proc registers
	process_reg_to_num_map = []							# assign numbers to registers		
	var_to_addr_map = {}								# global variable to address mapping	
	process_translated_code = []						# holds the translated code for each process

	final_conds = []									# final conditions
	init_conds = [] 									# global var initial values

	with open(infile) as f:
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
				
				while num_processes <= index:
					process_local_regs.append(set())
					process_local_mapping.append({})
					process_reg_to_num_map.append({})
					process_translated_code.append([])
					process_reg_nums.append(2)			# register 0,1 are "private" registers for CMP stmts
					num_processes += 1

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
	for proc in range(num_processes):
		for reg in process_local_regs[proc]:
			process_reg_to_num_map[proc][reg] = process_reg_nums[proc]
			process_reg_nums[proc] += 1
		
		# Add register assignments to output code
		# Format: REGASSIGN <regno> <value>  [easy to parse]
		for reg, var in process_local_mapping[proc].items():
			stmt = "REGASSIGN " + str(process_reg_to_num_map[proc][reg]) + " " + str(var_to_addr_map[var])
			process_translated_code[proc].append(stmt)

		# Add statement to indicate end of REGASSIGNS
		process_translated_code[proc].append("REGDONE")

	while not content[cur_index].startswith("exists"):
		parts = [part.strip() for part in content[cur_index][:-1].split('|')]
		for proc in range(num_processes):
			# need to remove spaces
			part = parts[proc].split(' ')
			operation = part[0]
			if operation in ['ISB','NOP','']:
				operands = ['']
			elif ':' in operation:
				# label
				# tell the model that the next instruction should be labelled
				# with this label
				stmt = "LABEL " + operation[:-1]
				process_translated_code[proc].append(stmt)
				operation = ''				# so that the file isn't blacklisted
			else:
				operands =  part[1].split(',')
				if len(operands) == 2 and not operands[1]:
					operands[1] = part[2]

			# these litmus tests have very simple addresses - simple locations

			# also, aci statements are not handled yet
			# might need to introduce a flags register for that

			if operation in ['LDR','LDAR','LDAXR','LDXR']:
				# Format: <LD..> REG <REGNO1> REG <REGNO2>
				# Stands for LD.. REG1, [REG2]
				operands[0] = operands[0][1:]
				operands[1] = operands[1][2:-1]
				for operand in operands:
					if operand not in process_local_regs[proc]:
						process_local_regs[proc].add(operand)
						process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
				stmt = operation[:-1] + " REG " + str(process_reg_to_num_map[proc][operands[0]]) + " REG " +	\
					   str(process_reg_to_num_map[proc][operands[1]])
				process_translated_code[proc].append(stmt)
			elif operation in ['STR', 'STLR']:
				# Format <ST..> REG <REGNO2> REG <REGNO1>
				# Stands for ST.. REG1, [REG2]
				# Reason for flip is that our model.cc expects the regs in the other
				# order for stores.
				operands[0] = operands[0][1:]
				operands[1] = operands[1][2:-1]
				for operand in operands:
					if operand not in process_local_regs[proc]:
						process_local_regs[proc].add(operand)
						process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
				stmt = operation[:-1] + " REG " + str(process_reg_to_num_map[proc][operands[1]]) + " REG " +	\
					   str(process_reg_to_num_map[proc][operands[0]])
				process_translated_code[proc].append(stmt)
			elif operation in ['STXR', 'STLXR']:
				# Format <ST..> REG <REGNO1> REG <REGNO3> REG <REGNO2>
				# Stands for ST.. REG1, REG2, [REG3]
				# Again, our model expects 2,3 in the other order
				operands[0] = operands[0][1:]
				operands[1] = operands[1][1:]
				operands[2] = operands[2][2:-1]
				for operand in operands:
					if operand not in process_local_regs[proc]:
						process_local_regs[proc].add(operand)
						process_reg_to_num_map[proc][operand] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
				stmt = operation[:-1] + " REG " + str(process_reg_to_num_map[proc][operands[0]]) + " REG " +	\
					   str(process_reg_to_num_map[proc][operands[2]]) + " REG " +   \
					   str(process_reg_to_num_map[proc][operands[1]])
				process_translated_code[proc].append(stmt)
			elif operation == "DMB":
				# Format: DMB<TYPE>, e.g. DMBSY
				# Simply concatenate the first operand with the op
				stmt = operation + operands[0]
				process_translated_code[proc].append(stmt)
			elif operation == "ISB":
				stmt = operation
				process_translated_code[proc].append(stmt)
			elif operation == "MOV":
				# If the second operand doesn't begin with a hash,
				# it is a register.
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1

				if operands[1][0] == '#': 
					stmt = "ASSIGN REG " + str(process_reg_to_num_map[proc][operands[0]]) + " NUM " + operands[1][1:]
				else:
					operands[1] = operands[1][1:]
					if operands[1] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[1])
						process_reg_to_num_map[proc][operands[1]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1

					stmt = "ASSIGN REG " + str(process_reg_to_num_map[proc][operands[0]]) + \
						" REG " + str(process_reg_to_num_map[proc][operands[1]])

				process_translated_code[proc].append(stmt)
			elif operation == "CMP":
				# convert the cmp into assigns to registers 0 and 1
				# Syntax: CMP <REG/NUM> <VALUE> <REG/NUM> <value>
				stmt1 = "ASSIGN REG 0 "
				if operands[0][0] == '#':
					stmt1 += "NUM " + operands[0][1:]
				else:
					operands[0] = operands[0][1:]
					if operands[0] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[0])
						process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					stmt1 += "REG " + str(process_reg_to_num_map[proc][operands[0]])
				stmt2 = "ASSIGN REG 1 "
				if operands[1][0] == '#':
					stmt2 += "NUM " + operands[1][1:]
				else:
					operands[1] = operands[1][1:]
					if operands[1] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[1])
						process_reg_to_num_map[proc][operands[1]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					stmt2 += "REG " + str(process_reg_to_num_map[proc][operands[1]])
				process_translated_code[proc].append(stmt1)
				process_translated_code[proc].append(stmt2)
			elif operation == "B.EQ":
				# Syntax: BEQ <LABEL>
				stmt = "BEQ " + operands[0]
				process_translated_code[proc].append(stmt)
			elif operation == "EOR":
				# Syntax BEQ REG <REGNO1> <REG/VAL> <REGNO2/VAL2> <REG/VAL> <REGNO3/VAL3>
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1
				stmt = "EOR REG " + str(process_reg_to_num_map[proc][operands[0]])
				if operands[1][0] == '#':
					stmt += " NUM "
					operands[1] = operands[1][1:]
					stmt += operands[1]
				else:
					stmt += " REG "
					operands[1] = operands[1][1:]
					if operands[1] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[1])
						process_reg_to_num_map[proc][operands[1]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					stmt += str(process_reg_to_num_map[proc][operands[1]])
				if operands[2][0] == '#':
					stmt += " NUM "
					operands[2] = operands[2][1:]
					stmt += operands[2]
				else:
					stmt += " REG "
					if operands[2] not in process_local_regs[proc]:
						process_local_regs[proc].add(operands[2])
						process_reg_to_num_map[proc][operands[2]] = process_reg_nums[proc]
						process_reg_nums[proc] += 1
					operands[2] = operands[2][1:]
					stmt += str(process_reg_to_num_map[proc][operands[2]])
				process_translated_code[proc].append(stmt)
			elif operation == "CBZ":
				# Syntax: CBZ REG <REGNO1> <LABEL>
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1
				stmt = "CBZ REG " + str(process_reg_to_num_map[proc][operands[0]]) + " " + operands[1]
				process_translated_code[proc].append(stmt)
			elif operation == "CBNZ":
				# Syntax: CBNZ REG <REGNO1> <LABEL>
				operands[0] = operands[0][1:]
				if operands[0] not in process_local_regs[proc]:
					process_local_regs[proc].add(operands[0])
					process_reg_to_num_map[proc][operands[0]] = process_reg_nums[proc]
					process_reg_nums[proc] += 1
				stmt = "CBNZ REG " + str(process_reg_to_num_map[proc][operands[0]]) + " " + operands[1]
				process_translated_code[proc].append(stmt)
			elif operation != '':
				print(filename, operation)
				blacklist.add(filename)
		cur_index += 1

	# add the terminating statement to all processes
	for proc in range(num_processes):
		process_translated_code[proc].append("TERM")

	# add the initialization code to its list
	init_conds.append(str(num_processes))				# first line is number of processes
	for var, value in mem_mapping.items():
		# Format: NUM <ADDR> VALUE <VALUE>
		stmt = "NUM " + str(var_to_addr_map[var]) + " VALUE " + str(value)
		init_conds.append(stmt)
	init_conds.append("DONE")

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

			stmt = "LOCAL " + parts[0] + " " + str(process_reg_to_num_map[proc][subparts[0]]) + " " + subparts[1]
			final_conds.append(stmt)
		else:
			# global constraint on a variable
			# Format: GLOBAL <ADDRESS> <EXPECTED_VALUE>
			parts = condition.split('=')

			if parts[0] not in var_set:
				var_set.add(parts[0])
				var_to_addr_map = vind
				vind += 1

			stmt = "GLOBAL " + str(var_to_addr_map[parts[0]]) + " " + parts[1]
			final_conds.append(stmt)
	final_conds.append("DONE")

	# we know that the filename ends with ".litmus", which is 7 characters
	testname = filename[:-7]

	# write the initial variable conditions
	name = testname + "_init.model"
	path = os.path.join(outdir, name)
	file = open(path, 'w+')
	file.write('\n'.join(str(line) for line in init_conds))

	# write the translation and conditions to a file
	for proc in range(num_processes):
		name = testname + "_" + str(proc) + "_code.model"
		path = os.path.join(outdir, name)
		file = open(path, 'w+')
		file.write('\n'.join(str(line) for line in process_translated_code[proc]))

	# write conditions
	name = testname + "_conditions.model"
	path = os.path.join(outdir, name)
	file = open(path, 'w+')
	file.write('\n'.join(str(line) for line in final_conds))

	# update maxregs
	global maxregs
	for proc in range(num_processes):
		maxregs = max(maxregs, process_reg_nums[proc])

for file in os.listdir(testdir):
	if os.path.isfile(os.path.join(testdir,file)) and file.endswith('.litmus'):
		print(file)
		do_convert(file)

bfile.write('\n'.join(str(name) for name in blacklist))
print(maxregs)
