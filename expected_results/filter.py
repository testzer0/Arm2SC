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

indir = os.path.join(os.getcwd(), '../herd-install/experiments/alltests/')
allowfile = os.path.join(os.getcwd(), 'expected_results/allow.txt')
disallowfile = os.path.join(os.getcwd(), 'expected_results/disallow.txt')

allow = []
disallow = []

def check(ifile):
	with open(ifile) as f:
		content = [x.strip() for x in f.readlines()]
	cur_index = 0
	nproc = 0
	name = ifile.split('/')[-1]
	print(name)

	# amend
	changed = False
	i = 0
	while i < len(content):
		if content[i].startswith("{") and content[i] != "{":
			content.insert(i+1,content[i][1:])
			content[i] = "{"
			changed = True
		elif content[i].endswith("}") and content[i] != "}":
			content.insert(i+1,"}")
			content[i] = content[i][:-1]
			changed = True
		i += 1

	while content[cur_index] != "{":
		cur_index += 1

	while content[cur_index] != "}":
		thisline = [part.strip() for part in content[cur_index].split(';')[:-1]]
		for part in thisline:
			if '%' in part:
				return False
			if ':' in part:	
				subparts1 = part.split(':')
				try:
					index = int(subparts1[0])
				except:
					return False
				nproc = max(nproc,index)
		cur_index += 1

	cur_index += 1
	while content[cur_index].strip() == "":
		content.pop(cur_index)
	cur_index += 1 										# skip over the '}' and PO|P1|... lines
	while not content[cur_index].startswith("exists"):
		if content[cur_index].startswith("~exists"):
			content[cur_index] = content[cur_index][1:]
			changed = True
			continue
		elif content[cur_index].startswith("locations"):
			return False
		parts = [part.strip() for part in content[cur_index][:-1].split('|')]
		for proc in range(nproc):
			# need to remove spaces
			part = parts[proc].split(' ')
			operation = part[0]
			if operation in ['ISB','NOP','']:
				operands = ['']
			elif ':' in operation:
				# label
				operation = ''				# so that the file isn't blacklisted
			else:
				try:
					operands =  part[1].split(',')
				except:
					return False
				if len(operands) == 2 and not operands[1]:
					operands[1] = part[2]
			# these litmus tests have very simple addresses - simple locations
			if operation in ['LDR','LDAR','LDAXR','LDXR','STR','STLR','STXR', 'STLXR', \
				'DMB','ISB','MOV','CMP','B.EQ','B.GE','B.GT','B.NE','B.LT','B.LE','EOR', \
				'CBZ','CBNZ']:
				pass
			else:
				return False
		cur_index += 1

	while cur_index < len(content):
		if ("\\/" in content[cur_index]) or ("not" in content[cur_index]):
			return False
		cur_index += 1
	if changed:
		with open(ifile,'w+') as f:
			for line in content:
				f.write(f"{line}\n")
		print(f"Modified {name}\n")
	return True

for filename in os.listdir(indir):
	file = os.path.join(indir,filename)
	if filename != "@all" and check(file):
		allow.append(filename)
	else:
		disallow.append(filename)

with open(allowfile, 'w+') as f:
	for test in allow:
		f.write(f"{test}\n")

with open(disallowfile, 'w+') as f:
	for test in disallow:
		f.write(f"{test}\n")