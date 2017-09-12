# a child can hop up one, two, three steps at a time.
# given n steps, count the number of ways a child can go up the steps.

def count_steps(steps):
	ways_counter = []
	for i in range(steps+1):
		ways_counter.append(-1)
	ways = count_num_ways(ways_counter, steps)
	return ways


def count_num_ways(ways_counter, steps):
	if steps < 0:
		return 0
	elif steps == 0:
		return 1
	elif ways_counter[steps] != -1:
		return ways_counter[steps]
	else:
		ways_counter[steps] = count_num_ways(ways_counter, steps-1) + count_num_ways(ways_counter, steps-2) + count_num_ways(ways_counter, steps-3)
		return ways_counter[steps]

print(count_steps(0))
print(count_steps(3))