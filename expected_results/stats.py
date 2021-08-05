import os
import sys
from enum import Enum

indir = os.path.join(os.getcwd(), '../herd-install/experiments/alltests/')

allow = []
disallow = []

why = dict()
counts = dict()

def check(ifile):
	with open(ifile) as f:
		content = [x.strip() for x in f.readlines()]
	cur_index = 0
	nproc = 0
	name = ifile.split('/')[-1]
	reason = ''

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
				reason = 'intel syntax'
				why[name] = reason
				if not reason in counts:
					counts[reason] = 0
				counts[reason] += 1
				return False
			if ':' in part:	
				subparts1 = part.split(':')
				try:
					index = int(subparts1[0])
				except:
					reason = 'parse error in startconds'
					why[name] = reason
					if not reason in counts:
						counts[reason] = 0
					counts[reason] += 1
					return False
				nproc = max(nproc,index)
		cur_index += 1

	nproc += 1
	if nproc == 1:
		reason = 'only 1 process'
		why[name] = reason
		if not reason in counts:
			counts[reason] = 0
		counts[reason] += 1
		return False

	cur_index += 1
	while content[cur_index].strip() == "":
		content.pop(cur_index)
	cur_index += 1 										# skip over the '}' and PO|P1|... lines
	while not content[cur_index].startswith("exists"):
		if content[cur_index] == '':
			cur_index += 1
			continue
		if content[cur_index].startswith("~exists"):
			content[cur_index] = content[cur_index][1:]
			changed = True
			continue
		elif content[cur_index].startswith("locations"):
			reason = 'Check cnds parse error'
			why[name] = reason
			if not reason in counts:
				counts[reason] = 0
			counts[reason] += 1
			return False
		parts = [part.strip() for part in content[cur_index][:-1].split('|')]
		for proc in range(nproc):
			# need to remove spaces
			if parts[proc] == '':
				continue
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
					reason = 'cannot split on comma: '+operation
					why[name] = reason
					if not reason in counts:
						counts[reason] = 0
					counts[reason] += 1
					return False
				if len(operands) == 2 and not operands[1]:
					operands[1] = part[2]
			# these litmus tests have very simple addresses - simple locations
			if operation in ['LDR','LDAR','LDAXR','LDXR','STR','STLR','STXR', 'STLXR', \
				'DMB','ISB','MOV','CMP','B.EQ','B.GE','B.GT','B.NE', 'B', 'EOR', \
				'CBZ','CBNZ', 'ADD', 'SUB', 'MUL','']:
				pass
			else:
				reason = 'op not supported: '+parts[proc]
				x = 'op not supported: '+operation
				why[name] = reason
				if not x in counts:
					counts[x] = 0
				counts[x] += 1
				return False
		cur_index += 1

	while cur_index < len(content):
		if ("\\/" in content[cur_index]) or ("not" in content[cur_index]):
			reason = 'conditions have OR/not'
			if not reason in counts:
				counts[reason] = 0
			counts[reason] += 1
			return False
		cur_index += 1
	return True

for filename in os.listdir(indir):
	if filename == '@all':
		continue
	file = os.path.join(indir,filename)
	check(file)

for key,value in counts.items():
	print("%s => %d" % (key, value))

print("")
print("==========================")
print("")
for key, value in why.items():
	print("%s : %s" % (key, value))