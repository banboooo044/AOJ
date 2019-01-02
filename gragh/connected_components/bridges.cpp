// lolinkの自作ライブラリ
/* option1:グラフが非連結の場合,option2:bridgeの検出,option3:関節点の検出*/
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
//#define NOT_ALL_CONNECTED 	//option1
#define BRIDGE   				//option2
//#define ARTICULATION_POINT    //option3
//#define DEBUG

using namespace std;
const long V_START = 0;
typedef vector<long> VL;
typedef vector<VL> VVL;
typedef pair<long,long> pr;
typedef vector<pr> VP;

bool pairCompare(const pr& firstElof, const pr& secondElof)
{
    return (firstElof.first < secondElof.first || ((firstElof.first == secondElof.first) && (firstElof.second < secondElof.second)));
}

VVL edge;	//隣接リスト
VL ord;		//dfs順序
VL low;		//lowlink
VL pre;		//(dfsツリーにおける)親の頂点

void dfs(long now_ver,long parent,long order){
	long child_num = 1;
	char flag = 0;
	pre[now_ver] = parent;
	low[now_ver] = ord[now_ver] = order;

	REP(i,edge[now_ver].size()){
		long to = edge[now_ver][i];
		if (to == parent) continue;
		if (ord[to] == -1) { // 子ノードへの辺
			dfs(to,now_ver,order + child_num);
			child_num++;
			low[now_ver] = min(low[now_ver],low[to]);
		}
		low[now_ver]=min(low[now_ver],ord[to]);
	}
}

int main(void){
	long V,E;
	cin >> V >> E;
	edge = VVL(V+1,VL(0));
	ord = VL(V+1,-1);
	low = VL(V+1,loINF);
	pre = VL(V+1,-1);

	REP(i,E){
		long u,v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u); 
	}

	#ifdef NOT_ALL_CONNECTED // グラフが非連結の場合
		FOR(i,V_START,V+V_START) 
			if(ord[i] == -1)
				dfs(i,-1,1);
	#endif

	#ifndef NOT_ALL_CONNECTED // グラフが連結の場合
		dfs(1,-1,1);
	#endif

	#ifdef BRIDGE
		VP bridge;
		long bridge_count = 0;

		FOR(i,V_START,V+V_START){
			if (ord[i] == low[i]) {
				if (pre[i] == (-1)) continue;
				bridge.push_back(make_pair(min(i,pre[i]),max(i,pre[i])));
				bridge_count++;
			}
		}

		sort(bridge.begin(),bridge.end(),pairCompare);	// a - b が辞書順で表示

		// bridge_count : 橋の本数 , bridge(pair配列):橋の頂点 first-second
		cout << "橋の数:" << bridge_count << endl;
		REP(i,bridge.size()) cout << bridge[i].first << "-" << bridge[i].second << endl;
	#endif

	#ifdef ARTICULATION_POINT
		VL point;
		long point_count = 0;
		char root_count = 0;
		FOR(i,V_START,V+V_START){
			if (pre[i] == -1) continue;
			if (pre[i] == 1) root_count++;
			else {
				if (ord[pre[i]] <= low[i]) {
					point.push_back(pre[i]);
					point_count++;
				}
			}
		}
		if(root_count >= 2) {
			point.push_back(1);
			point_count++;
		}

		SORT(point);
		point.erase(unique(point.begin(),point.end()),point.end());

		// point_count:関節点の個数 , point:関節点
		cout << "関節点の個数:" << point_count << endl;
		REP(i,point.size()) cout << point[i] << endl;
		
	#endif

	#ifdef DEBUG
		dump1d_arr(ord);
		dump1d_arr(low);
		dump1d_arr(pre);
	#endif

	return 0;
}

