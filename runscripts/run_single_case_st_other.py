import os
import subprocess
import sys

testdir = os.path.join(os.getcwd(), 'other_cctests')
listdir = os.path.join(os.getcwd(), 'other_tests')

blacklist = set()

infile = os.path.join(os.getcwd(), 'blacklists/blacklist_others.txt')
with open(infile) as f:
	for x in f.readlines():
		blacklist.add(x.strip())

logfile = os.path.join(os.getcwd(), 'ignore/log.txt')		

resultdict = {}


def runtest(filename, untilTrue=False):
	sat = False
	cmd = "./model_st \"" + filename + "\" -other" 
	if untilTrue:
		numIter = 0
		while not sat:
			numIter += 1
			output = subprocess.check_output(cmd, shell=True).decode("utf-8")
			lastline = output.split('\n')[-2]
			if lastline == 'satisfied':
				sat = True
				with open(logfile, 'w+') as f:
					f.write(output)
				break
		print(numIter)
	else:
		for i in range(10000):
			output = subprocess.check_output(cmd, shell=True).decode("utf-8")
			lastline = output.split('\n')[-2]
			if lastline == 'satisfied':
				sat = True
				with open(logfile, 'w+') as f:
					f.write(output)
				break
	if sat:
		return "satisfiable"
	else:
		return "unsatisfiable"

if len(sys.argv) == 1:
	print(runtest("LB+rel+BEQ3"))
elif len(sys.argv) == 2 or sys.argv[2] != "-u":
	print(runtest(sys.argv[1]))
else:
	print(runtest(sys.argv[1], True))
