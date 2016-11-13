# Check anagram
# Check if two words are an anagram
def check_anagram(word1, word2):
	h1 = build_hash(word1)
	h2 = build_hash(word2)
	if h1 == h2:
		return True
	else:
		return False

def build_hash(word):
	result = {}
	for letter in word:
		if letter not in result:
			result[letter] = 1
		else:
			result[letter] += 1
	return result


