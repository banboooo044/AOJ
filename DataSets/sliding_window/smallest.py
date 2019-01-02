N,S = map(int,input().split(" "))
a = list(map(int,input().split(" ")))

ans = float('inf')
l = 0
r = 0
sumv = 0
while True:
	while r < N and sumv < S:
		sumv += a[r]
		r += 1

	if sumv < S:
		break

	ans = min(ans,r-l)
	sumv -= a[l]
	l += 1

if ans == float('inf'):
	ans = 0
print(ans)

