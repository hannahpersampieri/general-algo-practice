# count the number of ways to get to a corner on an n x m gird
# if you can only travel down or right.
# follow up: with obstacles

def ways(n, m, table):
	if (n == 0):
		return 1
	elif m == 0:
		return 1
	else:
		table[m][n] = ways(n-1, m, table) + ways(n, m-1, table)
		return table[m][n]

def count_ways(n, m):
	ways_counter = [[0 for x in range(n)] for y in range(m)] 
	nways = ways(n-1, m-1, ways_counter)
	print nways

count_ways(6, 8)