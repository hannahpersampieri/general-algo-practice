# Longest continguous sum
# given an array, find the largest running sum
def longest_sum(array):
	curr_max = 0
	new_max = 0
	for i in range(0, len(array)):
		new_max += array[i]
		if (new_max < 0):
			new_max = 0
		if curr_max < new_max:
			curr_max = new_max
	return curr_max
	
