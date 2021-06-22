import os
import sys

infile = os.path.join(os.getcwd(),'preamble.c')
outfile = os.path.join(os.getcwd(),'preamble3.c')

inlines = []
outlines = []

loopcounter = 0
nregs = 16
addrsize = 64
nins = 20
ntime = 45

in_loop = False
brace_count = 0
loopcount = 0
nproc = 2

loop_contents = []
has_continue = False
has_break = False
loop_just_finished = False
skip_0 = False

with open(infile) as f:
	for line in f:
		inlines.append(line.rstrip())

for line in inlines:
	lline = line.lstrip()
	numspace = len(line) - len(lline)
	words = lline.split(' ')
	skip_0 = False
	if not len(words):
		if in_loop:
			loop_contents.append(line)
		else:
			outlines.append(line)
		continue
	if words[0] == "for":
		skip_0 = True
		in_loop = True
		has_continue = False
		has_break = False
		brace_count = 0
		loop_contents = []
		outlines.append(" "*numspace + f"/* Loop {loopcounter} BEGIN */")
		if words[6] == "ADDRSIZE;":
			loopcount = addrsize
		elif words[6] == "NREGS;":
			loopcount = nregs
		elif words[6] == "NINS;":
			loopcount = nins
		elif words[6] == "NTIME;":
			loopcount = ntime
		elif words[6] == "NPROC;":
			loopcount = nproc
		loopcounter += 1
	elif words[0] == "continue;":
		has_continue = True
	elif words[0] == "break":
		has_break = True

	if in_loop:
		for word in words:
			for character in word:
				if character == '}':
					brace_count -= 1
				elif character == '{':
					brace_count += 1
		if brace_count == 0 and not skip_0:
			in_loop = False
			loop_just_finished = True
			if len(line) != 0 and line[-1] == '}':
				line = line[:-1]
		if not skip_0:
			loop_contents.append(line)
	else:
		outlines.append(line)

	if loop_just_finished:
		loop_contents = ["loop_label:"]+loop_contents
		loop_contents.append(" "*numspace + "i++;")
		curind = 0
		expand = loop_contents*loopcount
		expand.append("loop_label:")
		for l in range(len(expand)):
			curline = expand[l]
			lcurline = curline.lstrip()
			if lcurline == "loop_label:":
				curline = f"loop_label_{loopcounter-1}_{curind}:"
				curind += 1
				expand[l] = curline
			elif lcurline == "continue;":
				wspace = len(curline)-len(lcurline)
				curline = " "*wspace + f"goto loop_label_{loopcounter-1}_{curind};"
				expand[l] = curline
			elif lcurline == "break;":
				wspace = len(curline)-len(lcurline)
				curline = " "*wspace + f"goto loop_label_{loopcounter-1}_{loopcount};"
				expand[l] = curline
		expand.append(" "*numspace + f"/* Loop {loopcounter-1} END */;")
		expand.insert(0," "*numspace + "i = 0;")
		outlines += expand
		loop_just_finished = False

with open(outfile,'w+') as file:
	file.write('\n'.join(str(line) for line in outlines))
