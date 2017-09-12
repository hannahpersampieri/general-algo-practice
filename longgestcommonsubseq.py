# LCS Problem

def LengthOfLCS(a, b, matrix, i, j):
	if min(i, j) == 0:
		return 0
	if matrix[i][j] == -1:
		if a[i] == b[j]:
			matrix[i][j] = 1 + LengthOfLCS(a, b, matrix, i - 1, j - 1)
		else:
			matrix[i][j] = max(LengthOfLCS(a, b, matrix, i-1, j), LengthOfLCS(a, b, matrix))
	return matrix[i][j]

def LCS(a, b):
	matrix = [[-1 for x in range(len(a))] for y in range(len(b))]
	print matrix 
	LengthOfLCS(a, b, matrix, len(a)-1, len(b)-1)

print(LCS("ABCCDAB", "BDCABA"))