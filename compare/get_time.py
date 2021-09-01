import os

total_time = 0
num_tests = 0
with open("test.txt") as f:
	for line in f.readlines():
		line = line.strip()
		if not line:
			continue
		total_time += float(line.split()[-2])
		num_tests += 1

print(f"Total time taken: {total_time} seconds")
total_time /= num_tests
print(f"Averaged over {num_tests} tests, {total_time} seconds")
