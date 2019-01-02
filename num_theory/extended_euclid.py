def extended_euclid(a,b):
	cc = gg = 1
	ee = ff = 0
	while b:
		div,mod = divmod(a,b)
		hh = cc - div * ee
		ii = ff - div * gg
		a,b = b,mod
		cc,ee = ee,hh
		ff,gg = gg,ii

	return (cc,ff)
n,m = map(int,input().split(" "))
print(*extended_euclid(n,m))

