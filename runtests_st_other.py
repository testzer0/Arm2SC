import os
import subprocess
import sys

if len(sys.argv) > 1:
	testdir = os.path.join(os.getcwd(), sys.argv[1])
	donefile = os.path.join(os.getcwd(),sys.argv[2])
	alltestfile = os.path.join(os.getcwd(), sys.argv[3])
	blacklistfile = os.path.join(os.getcwd(), sys.argv[4])
	dirname = sys.argv[1]
else:
	testdir = os.path.join(os.getcwd(), 'other_cctests')
	donefile = os.path.join(os.getcwd(),'results_others.txt')
	alltestfile = os.path.join(os.getcwd(),'expected_others.txt')
	blacklistfile = os.path.join(os.getcwd(), 'blacklist_others.txt')
	dirname = 'other_cctests'



blacklist = set()
tests = {}
finished = {}

with open(blacklistfile) as f:
	for x in f.readlines():
		blacklist.add(x.strip())
	f.close()

with open(alltestfile) as f:
	for x in f.readlines():
		parts = x.split(':')
		part0 = parts[0].strip()
		part1 = parts[1].strip()
		tests[part0] = part1
	f.close()

with open(donefile) as f:
	for x in f.readlines():
		parts = x.split(':')
		part0 = parts[0].strip()
		part1 = parts[1].strip()
		finished[part0] = part1
	f.close()


def runtest(filename, expectedSat):
	sat = False
	cmd = "./model_st " + filename + " -n " + dirname 
	if expectedSat:
		while not sat:
			output = subprocess.check_output(cmd, shell=True).decode("utf-8")
			if output.strip() == 'satisfied':
				sat = True
				break
	else:
		for i in range(10000):
			output = subprocess.check_output(cmd, shell=True).decode("utf-8")
			if output.strip() == 'satisfied':
				sat = True
				break
	if sat:
		return "satisfiable"
	else:
		return "unsatisfiable"

for file, result in tests.items():
	if file in blacklist:
		continue
	if file in finished:
		continue
	fname = file[:-7]
	print(file + " : ", end='', flush=True)
	ret = runtest(fname, result == 'satisfiable')
	print(ret)
	finished[file] = ret


file = open(donefile, 'w+')
for key,value in resultdict.items():
	file.write(key + ".litmus : " + value + "\n")
file.close()
