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
using namespace std;
typedef vector<long> VI;
typedef vector<VI> VVI;
const short V_START = 1;

class Union_Find {
private:
	vector<unsigned> par;    // par[x] : x の親ノード
    vector<unsigned> rank;   // rank[x] : 木の高さ
    size_t sz;             // 集合の個数
public:
	
    // コンストラクタ : 空
    Union_Find() : sz(0) { }

    // コンストラクタ : 1 要素の集合 n 個
    Union_Find(size_t n) :
        par(n, -1), rank(n, 0), sz(n) {
        for (size_t i = 0; i < n; i++) par[i] = i;
    }

    size_t size() { return sz; }

    // 集合の追加 : 1 個
    void add_node() {
        par.push_back(par.size());
        rank.push_back(0);
        sz++;
    }
    // 集合の追加 : n 個
    void add_node(size_t n) {
        for (size_t i = 0; i < n; i++) add_node();
    }

    // x が属する集合の代表元を返す
    size_t find(size_t x) {
        if (par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }

    // x が属する集合と y が属する集合をマージする
    void unite(size_t x, size_t y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (rank[x] < rank[y])
            par[x] = y;
        else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
        sz--;
    }

    // x と y が同じ集合に属しているか？
    bool same(size_t x, size_t y) {
        return find(x) == find(y);
    }

    void dump_par(void){
    	dump1d_arr(par);
    }

    void dump_rank(void){
    	dump1d_arr(rank);
    }
};

// global変数
VVI edge;
VVI edge_reverse;

VI visited;
VI stop;

Union_Find uf;

void dfs_forward(long node){
	visited[node] = 1;
	REP(i,edge[node].size()){
		long to = edge[node][i];
		if (visited[to] == 0){
			dfs_forward(to);
		}
	}
	stop.push_back(node);
}

void dfs_reverse(long node){
	visited[node] = 0;
	REP(i,edge_reverse[node].size()){
		long to = edge_reverse[node][i];
		if (visited[to] == 1) {
			dfs_reverse(to);
			uf.unite(node,to);
		}
	}
}

int main(void){
	long V,E;
	cin >> V >> E;

	// global変数の初期化
	edge = VVI(V+1,VI(0));
	edge_reverse = VVI(V+1,VI(0));
	visited = VI(V+1,0);
	uf.add_node(V);

	//辺情報の入力
	REP(i,E) {
		long s,t;
		cin >> s >> t;
		edge[s].push_back(t);
		edge_reverse[t].push_back(s); 
	}

	FOR(i,V_START,V+V_START){
		if (visited[i] == 0) dfs_forward(i);
	}

	long max_iter = stop.size()-1;
	for(long i = max_iter;i >= 0;i--){
		if (visited[stop[i]] == 1) dfs_reverse(stop[i]);
	}

	cout << uf.size() << endl;

	return 0;	
}