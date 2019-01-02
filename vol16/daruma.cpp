#include <bits/stdc++.h>
#define REP(i,n) for (int i=0;i<(n);i++)
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define dump1d_arr(array,i) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array,i,j) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define loINF (long)10000000000
#define shINF (short)10000
#define SORT(c) sort((c).begin(),(c).end())
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

int main (void){
	char flag;
	short N;
	cin >> N;

	VI W(N,0);
	REP(i,N) cin >> W[i];

	VVI dp(N, VI(N,0));
	VVI removable(N,VI(N,0));

	REP(i,N-1){
		if (abs(W[i]-W[i+1])<= 1){
			removable[i][i+1] = 1;
			dp[i][i+1] = 2;
		}

	}

	FOR(w,2,N){ //幅
		REP(l,N-w){ //left_index
			short r = l + w; //right_index
			FOR(k,l+1,r){
				dp[l][r] = max({dp[l][r],dp[l][k] + dp[k+1][r]});
			}

			if (!(w % 2)) continue;

			if ((abs(W[l] - W[r]) > 1)) continue;
			if (removable[l+1][r-1]){
				removable[l][r] = 1;
				dp[l][r] = w + 1;
				continue;
			}

			flag = 0;
			for(int k = l;k < r;k+=2){
				if (abs(W[k]-W[k+1])>1){
					flag = 1;
					break;
				}
			}
			if (!(flag)) {
				removable[l][r] = 1;
				dp[l][r] = w + 1;
			}
		}
	}
	#ifdef DEBUG
		REP(i,N) REP(j,N) dump2d_arr(dp,i,j);
	#endif


	cout << dp[0][N-1] << endl;
	return 0;
}