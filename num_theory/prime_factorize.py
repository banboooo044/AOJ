import math

s = "{0}:"
s2 = " {0}"
def prime_factorize(n):
	m = math.sqrt(n)+1
	i = 2
	prime = []
	while n != 1 and i < m:
		if n % i == 0:
			prime.append(i)
			n //= i
		else:
			i += 1
	if n != 1:
		prime.append(n)
	return prime
n = int(input())
lst = prime_factorize(n)
print(s.format(n),end="")
for i in range(len(lst)):
	print(s2.format(lst[i]),end="")
print()
