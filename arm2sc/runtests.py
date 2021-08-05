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
elif sys.argv[1] == "-o":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_all.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_all.txt')
elif sys.argv[1] == "-a":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_all_new.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_all_new.txt')
elif sys.argv[1] == "-b1":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_b1.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_b1.txt')
elif sys.argv[1] == "-b2":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_b2.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_b2.txt')
elif sys.argv[1] == "-b3":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_b3.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_b3.txt')
elif sys.argv[1] == "-b4":
	infile = os.path.join(os.getcwd(), 'expected_results/expected_b4.txt')
	outfile = os.path.join(os.getcwd(), 'arm2sc/output_b4.txt')

resultdict = {}
tests = []
expected_dict = {}

with open(infile) as f:
	for line in f.readlines():
		parts = line.split(':')
		tests.append(parts[0].strip())
		expected_dict[parts[0].strip()] = parts[1].strip()

fail = False

count = 1
for test in tests:
	if fail:
		quit()
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
	if resultdict[test] == expected_dict[test]:
		three = colored('PASS', 'green')
	else:
		three = colored('FAIL', 'red')
		fail = True
	print(f"{count} {test} : EXPECTED {one} GOT {two}.....{three}")
	count += 1

with open(outfile, 'w+') as f:
	for test, result in resultdict.items():
		f.write(f"{test} : {result}\n")