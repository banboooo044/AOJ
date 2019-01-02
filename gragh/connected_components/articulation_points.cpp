#include <bits/stdc++.h>
#define REP(i,n) for (long i=0;i<(n);i++)
#define FOR(i,a,b) for (long i=(a);i<(b);i++)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define loINF (long)10000000000
#define shINF (short)10000
#define SORT(c) sort((c).begin(),(c).end())
#define DEBUG
using namespace std;
typedef vector<long> VI;
typedef vector<VI> VVI;

VI lowest;
VI dfs_order;
VI prever;
VVI edge;

void dfs_tree(long ver,long dfs_ord,long pre) {
	long nextver;
	prever[ver] = pre;
	dfs_order[ver] = dfs_ord ;
	lowest[ver] = dfs_ord ;

	REP(i,edge[ver].size()){
		long nextver_num = 1;
		long now_ver;
		nextver = dfs_order[edge[ver][i]];
		now_ver = ver;
		if (nextver < lowest[ver]) {
			while (nextver < lowest[now_ver]){
				lowest[now_ver] = nextver;
				now_ver = prever[now_ver];
			}
		}
		else {
			if (nextver == loINF) {
				dfs_tree(edge[ver][i],dfs_ord+nextver_num,ver);
				nextver_num++;
			}
		}
	}
}

int main(void){
	long V,E;
	short root_count = 0;
	VI ans;
	cin >> V >> E;
	lowest = VI(V+1,0);
	dfs_order = VI(V+1,loINF);
	prever = VI(V+1,loINF);
	edge = VVI(V+1,VI(0));

	REP(i,E){
		long ver1,ver2;
		cin >> ver1 >> ver2;
		edge[ver1].push_back(ver2);
		edge[ver2].push_back(ver1);
	}

	dfs_tree(1,1,loINF);
	REP(i,V){
		long  parent = prever[i];
		if (parent == loINF) continue;
		if (parent == 1) root_count++;
		else { if (dfs_order[parent] <= lowest[i]) ans.push_back(parent); }
	}

	#ifdef DEBUG
		dump1d_arr(lowest);
		dump1d_arr(dfs_order);
		dump1d_arr(prever);
	#endif
	SORT(ans);
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	REP(i,ans.size()) cout << ans[i] << endl;
	if (root_count >= 2) cout << 1 << endl;

	return 0;
}

