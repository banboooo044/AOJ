n = int(input())
def prime_factorize(n):
	import math
	m = math.sqrt(n)+1
	i = 2
	prime = {}
	while n != 1 and i < m:
		if n % i == 0:
			if i in prime:
				prime[i] += 1
			else:
				prime[i] = 1 
			n //= i
		else:
			i += 1
	if n != 1:
		prime[n] = 1
	return prime

dic = prime_factorize(n)
for key in dic.keys():
	n *= (1 - (1/key))

print(int(n))


