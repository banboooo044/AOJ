#include <bits/stdc++.h>
#define REP(i,n) for (long i=0;i<(n);i++)
#define FOR(i,a,b) for (long i=(a);i<(b);i++)
#define RREP(i,n) for(long i=n;i>=0;i--)
#define RFOR(i,a,b) for(long i=(a);i>(b);i--)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define llINF (long long) 9223372036854775807
#define loINF (long) 2147483647
#define shINF (short) 32767
#define SORT(c) sort((c).begin(),(c).end())

using namespace std;
typedef vector<long> VI;
typedef vector<VI> VVI;
// to:次の頂点,cap:辺の重み,rev:逆辺のindex
struct edge {long to,cap,rev;};
class Ford_fulkerson {
private:
	vector<vector<edge>> E;
	vector<bool> used;
	size_t V;
public:
	Ford_fulkerson() : V(0) { }

	Ford_fulkerson(size_t v) :
		E(v,vector<edge>(0)),used(v,false),V(v){ }

	size_t size() { return V;}

	void add_edge(long from,long to,long cap){
		E[from].push_back({to,cap,(long)E[to].size()});
		E[to].push_back({from,0,(long)E[from].size()-1});
	}

	long dfs(long node,long goal,long flow){
		if (node == goal) return flow;
		used[node] = true;
		REP(i,E[node].size()){
			edge* e = &E[node][i];
			if (!used[e->to] && e->cap != 0){
				long d = dfs(e->to,goal,min(flow,e->cap));
				if (d != 0) {
					e->cap -= d;
					E[e->to][e->rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	long max_flow(long start,long goal){
		long ans = 0;
		while (1){
			REP(i,used.size()) used[i] = false;
			long f = dfs(start,goal,2147483647);
			if (f == 0) return ans;
			ans += f;
		}
	}
};

int main(void){
	long X,Y,E;
	long x,y;
	cin >> X >> Y >> E;
	Ford_fulkerson ff(X+Y+2);

	long start = X+Y;
	long goal = start+1;

	REP(i,E){
		cin >> x >> y;
		ff.add_edge(x,y+X,1);
	}

	REP(i,X) ff.add_edge(start,i,1);
	FOR(i,X,X+Y) ff.add_edge(i,goal,1);

	cout << ff.max_flow(start,goal) << endl;

	return 0;
}
