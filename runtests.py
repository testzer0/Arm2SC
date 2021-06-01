import os
import subprocess

testdir = os.path.join(os.getcwd(), 'cctests')
listdir = os.path.join(os.getcwd(), 'tests')

blacklist = set()

infile = os.path.join(os.getcwd(), 'blacklist.txt')
with open(infile) as f:
	for x in f.readlines():
		blacklist.add(x.strip())

resultdict = {}


def runtest(filename):
	sat = False
	cmd = "./model \"" + filename + "\"" 
	for i in range(10000):
		output = subprocess.check_output(cmd, shell=True).strip()
		if output == b'satisfied':
			sat = True
			break
	if sat:
		resultdict[filename] = "satisfiable"
	else:
		resultdict[filename] = "unsatisfiable"


for file in os.listdir(listdir):
	if os.path.isfile(os.path.join(listdir,file)) and file.endswith('.litmus'):
		fname = file[:-7]
		if file not in blacklist:
			runtest(fname)

file = open(os.path.join(os.getcwd(),"results.txt"), 'w+')
for key,value in resultdict.items():
	file.write(key + ".litmus : " + value + "\n")
