# rod cutting

def rod_cut(prices, cut):
	if cut == 0:
		return 0
	else:
		for i in range(0, cut):
			cuts[cut] = max(prices[cut] + rod_cut(cut-i))


def rod_cutting(rod_length, prices):
	cuts = []
	for i in range(rod_length):
		cuts.append(-1)

	optimal_cost = rod_cut(prices, rod_length-1)
