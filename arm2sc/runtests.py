import os
import subprocess
import sys
from termcolor import colored

if len(sys.argv) == 1:
	infile = os.path.join(os.getcwd(), 'expected_results/expected.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output.txt')
elif sys.argv[1] == "-k":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_others.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_other.txt')
else:
	infile = os.path.join(os.getcwd(), 'expected_results/expected_all.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_all.txt')

resultdict = {}
tests = []
expected_dict = {}

with open(infile) as f:
	for line in f.readlines():
		parts = line.split(':')
		tests.append(parts[0].strip())
		expected_dict[parts[0].strip()] = parts[1].strip()

for test in tests:
	if len(sys.argv) > 1:
		if sys.argv[1] == "-k":
			cmd = f"python3 arm2sc/translate.py other_tests {test} translated.c &&  \
				cbmc arm2sc/translated.c 2>/dev/null"
		else:
			cmd = f"python3 arm2sc/translate.py alltests {test} translated.c &&  \
				cbmc arm2sc/translated.c 2>/dev/null"
	else:
		cmd = f"python3 arm2sc/translate.py {test} translated.c && cbmc arm2sc/translated.c 2>/dev/null"
	try:
		output = subprocess.check_output(cmd, shell=True).decode("utf-8")
	except Exception as e:
		output = str(e.output)
	try:
		word = output.split('\n')[-1].split()[-1][:-3]
	except Exception as e:
		word = "SUCCEEDED"
	if word == "FAILED":
		resultdict[test] = "satisfiable"
		two = colored('satisfiable', 'green')
	else:
		resultdict[test] = "unsatisfiable"
		two = colored('unsatisfiable', 'red')
	if expected_dict[test] == "satisfiable":
		one = colored('satisfiable', 'green')
	else:
		one = colored('unsatisfiable', 'red')
	print(f"{test} : EXPECTED {one} GOT {two}")

with open(outfile, 'w+') as f:
	for test, result in resultdict.items():
		f.write(f"{test} : {result}\n")