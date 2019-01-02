def gcd (a,b):
	if a < b:
		a,b = b,a
	return a if b == 0 else gcd(b,a%b)

n = int(input())
a = list(map(int,input().split(" ")))
ans = 1

for i in range(n):
	ans *= (a[i]//gcd(ans,a[i]))

print(ans)