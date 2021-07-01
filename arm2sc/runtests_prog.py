import os
import subprocess
import sys

tests = ["burns", "dekker", "dijkstra", "nolocking", "optimistic3", "peterson",  \
		 "STXlock", "wronglock1", "wrongpc1"]

resultdict = {}
outfile = os.path.join(os.getcwd(),'arm2sc/output_prog.txt')

for test in tests:
	cmd = f"python3 arm2sc/translate_prog.py {test} translated.c && python3 arm2sc/call_cbmc.py 2>/dev/null"
	try:
		output = subprocess.check_output(cmd, shell=True).decode("utf-8")
	except Exception as e:
		output = e.output.decode("utf-8")
	try:
		word = output.split('\n')[-1].split()[-1][:-3]
	except Exception as e:
		word = "SUCCEEDED"
	if word == "FAILED":
		resultdict[test] = "satisfiable"
	else:
		resultdict[test] = "unsatisfiable"
	print(f"{test} : GOT {resultdict[test]}")

with open(outfile, 'w+') as f:
	for test, result in resultdict.items():
		f.write(f"{test} : {result}\n")