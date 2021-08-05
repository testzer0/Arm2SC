import os

def parse_file_without_comments_or_empty_lines(filename, prefix=None):
	if prefix:
		filename = os.path.join(prefix,filename)
	lines = []
	with open(filename) as f:
		for line in f.readlines():
			line = line.strip()
			if line.startswith("//") or not line:
				continue 
			lines.append(line)
	return lines

dirs = os.listdir(os.path.join(os.getcwd(), "bench_translated"))
for directory in dirs:
	files = os.listdir(os.path.join(os.getcwd(), f"bench_translated/{directory}"))
	for file in files:
		if not file.endswith(".aarch64"):
			continue
		fname = os.path.join(os.getcwd(), f"bench_translated/{directory}/{file}")
		contents = parse_file_without_comments_or_empty_lines(fname)
		for i in range(len(contents)):
			if contents[i].endswith(";"):
				contents[i] = "    " + contents[i][:-1].strip()
			else:
				contents[i] = "    " + contents[i]
		with open(fname, 'w+') as file:
			file.write('\n'.join(str(line) for line in contents))