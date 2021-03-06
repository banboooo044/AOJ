/*ベルマンフォード法自作ライブラリ*/
/*標準:単一始点からの他の全頂点への最短距離 & 閉ループ判定 ,option1:単一始点&終点の最短距離。&辞書順経路復元,option2:経路復元(非辞書順)*/
#include <bits/stdc++.h>
#define REP(i,n) for (int i=0;i<(n);i++)
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define loINF (long)10000000000
#define shINF (short)10000
#define SORT(c) sort((c).begin(),(c).end())
//#define TRACE_ROUTE
//#define TRACE_ROUTE_DIC
using namespace std;
typedef vector<long> VL;
typedef vector<VL> VVL;
typedef vector<char> VC;

//global変数
VVL edge;	//隣接リスト
VL dis;

#if defined(TRACE_ROUTE) || defined(TRACE_ROUTE_DIC)
	VL pre;
#endif 

short bellman_ford (long start,long V){
	long update_flag = 1;
	long edge_start,edge_end,edge_dis;
	long roop_count = 0;

	while (update_flag) {
		if (++roop_count > V) return -1;
		update_flag = 0;
		REP(i,edge.size()) {	// 辺の始点
			edge_start = edge[i][0];
			edge_end = edge[i][1];
			edge_dis = edge[i][2];

			if (dis[edge_start] == loINF) continue; //まだ候補すらない頂点

			if (dis[edge_start] + edge_dis < dis[edge_end]){
				dis[edge_end] = dis[edge_start] + edge_dis;
				update_flag = 1;

				#if defined(TRACE_ROUTE) || defined(TRACE_ROUTE_DIC)
					pre[edge_end] = edge_start;
				#endif
			}

			#if defined(TRACE_ROUTE) || defined(TRACE_ROUTE_DIC)
			else {
				if (dis[edge_start] + edge_dis == dis[edge_end] && pre[edge_end] > edge_start){
					pre[edge_end] = edge_start;
					update_flag = 1;
				}
			}
			#endif
		}
	}

	return 0;
}

#ifdef TRACE_ROUTE
string trace_route (long start,long goal) {
	string tmp;
	string route("");
	long ver = goal;
	while (ver != start){
		tmp = ("-" + to_string(ver)) ;
		route = (tmp + route);
		ver = pre[ver];
	}
	route = (to_string(start) + route);
	return route;
}
#endif

#ifdef TRACE_ROUTE_DIC
string trace_route_dic(long start,long goal) {
	string route("");
	long ver = start;
	while (ver != goal){
		route += (to_string(ver) + "-");
		ver = pre[ver];
	}
	route += to_string(goal);
	return route;
}

short bellman_ford_dic(long start,long goal,long V){
	short flag = bellman_ford(goal,V);
	if (ans_val == -1) cout << "exist negative loop" << endl;
	
	if (ans_val == 0){
		// 最短距離の表示
		cout << dis[start] << endl;
		// 辞書順の経路復元
		cout << trace_route_dic(start,goal) << endl;
	}
	else cerr << "error" << endl;
}
#endif

/* テンプレの入力フォーマット
V E
v11 v12 dis
v21 v22 dis
.
.
start (goal)
*/

int main(void) {
	long V,E; 
	long ver1,ver2,weight;
	long start;

	//入力部分1
	cin >> V >> E >> start; //V:頂点数 , E:辺数
	//入力部分1　ここまで

	edge = VVL(E,VL(3,0)); //　辺の端点とコストの組を格納

	//入力部分2
	REP(i,E){ //辺の情報を入力
		cin >> ver1 >> ver2 >> weight;
		/*有向グラフ ver1 ==> ver2 */
		edge[i][0] = ver1;
		edge[i][1] = ver2;
		edge[i][2] = weight; 
	}
	//入力部分2ここまで

	dis = VL(V+1,loINF);
	dis[start] = 0; //スタート地点は距離0

	#if defined(TRACE_ROUTE) || defined(TRACE_ROUTE_DIC)
		pre = VL(V+1,loINF);
		pre[start] = start;
	#endif

	// 辞書順の経路復元を行う場合。
	#ifdef TRACE_ROUTE_DIC
		long goal
		cin >> goal;
		bellman_ford_dic(start,goal,V);
		exit(0);
	#endif

	// それ以外
	long ans_val = bellman_ford(start,V);
	if (ans_val == -1) cout << "NEGATIVE CYCLE" << endl;
	else {
		if (ans_val == 0){
			// 最短距離の表示 dis[i]にstartから頂点iまでの最短距離が格納されている。
			FOR(i,0,V) {
				if (dis[i] == loINF) cout << "INF" << endl;
				else cout << dis[i] << endl;
				// 経路復元
				#ifdef TRACE_ROUTE
					cout << trace_route(start,i) << endl;
				#endif
			}
		}
		else cerr << "error" << endl;
	}
 	return 0;
}