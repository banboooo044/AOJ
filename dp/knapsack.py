if __name__ == "__main__":
	N,W = map(int,input().split(" "))
	dp = [[0] * (W+1) for _ in range(N+1)]

	w_lis = [0] * N
	v_lis = [0] * N

	for i in range(N):
		v,w = map(int,input().split(" "))
		w_lis[i] = w
		v_lis[i] = v



	for i in range(1,N+1):
		for w in range(0,W+1):
			if w >= w_lis[i-1]:
				dp[i][w] = max([dp[i-1][w - w_lis[i-1]] + v_lis[i-1],dp[i-1][w]])

			else:
				dp[i][w] = dp[i-1][w]


	print(dp[N][W])





