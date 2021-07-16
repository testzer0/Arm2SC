import os
import subprocess
import sys

lines = ["emptyline"]
if len(sys.argv) == 1:
	file = os.path.join(os.getcwd(),'arm2sc/translated.c')
	fname = "translated.c"
	delname = "del.txt"
elif len(sys.argv) == 2:
	file = os.path.join(os.getcwd(),'arm2sc/'+sys.argv[1])
	fname = sys.argv[1]
	delname = "del.txt"
else:
	file = os.path.join(os.getcwd(),'arm2sc/'+sys.argv[1])
	fname = sys.argv[1]
	delname = sys.argv[2]

with open(file) as f:
	for line in f.readlines():
		lines.append(line)

names = []
nunwind = 5

cmd1 = f"cbmc arm2sc/{fname} --show-loops"
output = subprocess.check_output(cmd1, shell=True).decode("utf-8").split('\n')
for i in range(len(output)):
	if output[i].startswith("Loop"):
		name = output[i][4:-1].strip()
		lineno = int(output[i+1].split()[3])
		line = lines[lineno].strip().split(' ')
		if len(line) == 0:
			continue
		if line[0] == "goto":
			names.append(name)

cmd2 = f"cbmc arm2sc/{fname}"
if len(names) != 0:
	cmd2 += " --unwindset "
	for name in names:
		cmd2 += f"{name}:{nunwind},"
	cmd2 = cmd2[:-1]

# cmd2 += f" --trace > {delname}"
os.system(cmd2)