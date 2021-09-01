import os
import subprocess
import sys
from timeit import default_timer as timer
from termcolor import colored

testdir = os.getcwd()

if sys.argv[1] == "-a":
	infile = os.path.join(testdir, '../expected_results/expected_all.txt')
	outfile = os.path.join(os.getcwd(), 'out/output_all.txt')
elif sys.argv[1] == "-b1":
	infile = os.path.join(testdir, '../expected_results/expected_b1.txt')
	outfile = os.path.join(os.getcwd(), 'out/output_b1.txt')
elif sys.argv[1] == "-b2":
	infile = os.path.join(testdir, '../expected_results/expected_b2.txt')
	outfile = os.path.join(os.getcwd(), 'out/output_b2.txt')
elif sys.argv[1] == "-b3":
	infile = os.path.join(testdir, '../expected_results/expected_b3.txt')
	outfile = os.path.join(os.getcwd(), 'out/output_b3.txt')
elif sys.argv[1] == "-b4":
	infile = os.path.join(testdir, '../expected_results/expected_b4.txt')
	outfile = os.path.join(os.getcwd(), 'out/output_b4.txt')

resultdict = {}
tests = []
expected_dict = {}


with open(infile) as f:
	for line in f.readlines():
		parts = line.split(':')
		tests.append(parts[0].strip())
		expected_dict[parts[0].strip()] = parts[1].strip()

fail = False

total_time = 0
num_tests = len(tests)

count = 45
tests = tests[44:]
for test in tests:
	# if fail:
	#	quit()
	name = test + ".toml"
	cmd = f"target/release/isla-axiomatic -A aarch64.ir -C configs/aarch64.toml -m \
		web/client/dist/aarch64.cat -t alltests/{name}"
	then = timer()
	try:
		output = subprocess.check_output(cmd, shell=True).decode("utf-8")
	except Exception as e:
		output = str(e.output)
	now = timer()
	t = now - then
	try:
		word = output.split(" ")[1]
	except Exception as e:
		word = "disallowed"
	if word == "allowed":
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
	print(f"{count} {test} : EXPECTED {one} GOT {two}.....{three} in {t} seconds")
	total_time += t
	count += 1

print("")
print(f"Total time taken: {total_time} seconds")
total_time /= num_tests
print(f"Averaged over {num_tests} tests, {total_time} seconds")

with open(outfile, 'w+') as f:
	for test, result in resultdict.items():
		f.write(f"{test} : {result}\n")
