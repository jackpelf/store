def kmp():
	while i<len(text):
		if text[i] == P[i]:
			i++
			j++
		else:
			if next[j] == -1:
				j = 0
				i += 1
			else:
				j = next[j]	#max pre and post len

def gnext():
	next[0] = -1
	k = -1
	j = 0
	while j<len(P):
		if k != -1 && P[k] != P[j]:	#not start ,find start,
			k = next[k]
		j += 1
		k += 1
		if P[k] == P[j]:		#eqal fuzhi qianmiande
			next[j] = next[k]
		else:
			next[j] = k
