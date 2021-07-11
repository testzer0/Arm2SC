import os
import subprocess
import sys
from timeit import default_timer as timer

tests = ["burns_safe1", "burns_unsafe1", "burns_unsafe2", "burns_unsafe3", "burns_unsafe4",  \
		 "burns_unsafe5", "dekker_safe1", "dekker_unsafe1", "dekker_unsafe2", "dekker_unsafe3",  \
		 "dijkstra_safe1", "dijkstra_unsafe1", "dijkstra_unsafe2", "dijkstra_unsafe3",  \
		 "fibbench_safe1", "fibbench_unsafe1", "nolocking_unsafe1", "optimistic3_safe1",  \
		 "peterson_safe1", "peterson_unsafe1", "peterson_unsafe2", "pgsql_safe1", "pgsql_unsafe1",  \
		 "pgsql_bound_safe1", "pagesql_bound_unsafe1", "singleton_safe1", "sigma_unsafe1",  \
		 "STXlock_safe1", "STXlock_unsafe1", "STXlock_unsafe2", "STXlock_unsafe3",  \
		 "szymanski_safe1", "szymanski_unsafe1", "wronglock1_unsafe1", "wrongpc1_unsafe1",  \
		 "queue_safe1", "queue_unsafe1", "apr2"]

resultdict = {}
timedict = {}
outfile = os.path.join(os.getcwd(),'arm2sc/output_prog.txt')

for test in tests:
	cmd = f"python3 arm2sc/translate_prog.py {test} translated.c && python3 arm2sc/call_cbmc.py 2>/dev/null"
	then = timer()
	try:
		output = subprocess.check_output(cmd, shell=True)
	except Exception as e:
		output = e.output
	now = timer()
	timedict[test] = now-then
	output = output.decode("utf-8")
	try:
		parts = output.split('\n')
		i = -1
		while parts[i].strip() == '':
			i -= 1
		word = parts[i].split()[-1]
	except Exception as e:
		word = "SUCCEEDED"
	if word == "FAILED":
		resultdict[test] = "unsafe/satisfiable"
	else:
		resultdict[test] = "safe/unsatisfiable"
	st = f"{test} : GOT {resultdict[test]}"
	st = st.ljust(50,'.') + f"in {timedict[test]} seconds"
	print(st)

with open(outfile, 'w+') as f:
	for test, result in resultdict.items():
		stmt = f"{test} : GOT {resultdict[test]}"
		stmt = stmt.ljust(50,'.') + f"in {timedict[test]} seconds"
		f.write(stmt)