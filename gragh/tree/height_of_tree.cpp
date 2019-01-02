#include <bits/stdc++.h>
#define REP(i,n) for (long i=0;i<(n);i++)
#define FOR(i,a,b) for (long i=(a);i<(b);i++)
#define RREP(i,n) for(long i=n;i>=0;i--)
#define RFOR(i,a,b) for(long i=(a);i>(b);i--)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define dumpP(p) cerr << "( " << p.first << " , " << p.second << " )" << endl;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define SORT(c) sort((c).begin(),(c).end())
#define MIN(vec) *min_element(vec.begin(), vec.end());
#define MAX(vec) *max_element(vec.begin(), vec.end());
#define UNIQ(vec) vec.erase(unique(vec.begin(), vec.end()),vec.end());
#define IN(n,m)  (!(m.find(n) == m.end()))
#define TO_INT(vec,s) REP(i,s.length()){vec.push_back(s[i] - ‘0’);}
#define ENUM_v(vec) for (auto e : vec)
#define dump_MAP(m) for(auto itr = m.begin(); itr != m.end(); ++itr) { cerr << itr->first << " --> "  << itr->second << endl; }
#define FINDL(vec,x) (lower_bound(vec.begin(),vec.end(),x) - vec.begin())
#define FINDU(vec,x) (upper_bound(vec.begin(),vec.end(),x) - vec.begin())
#define ROUND(N) setprecision(N)
using namespace std;
constexpr long mod = 1000000007;
constexpr short shINF = 32767;
constexpr long loINF = 2147483647;
constexpr long long llINF = 9223372036854775807;
typedef long long LL;
typedef vector<long> VI;
typedef vector<VI> VVI;

template <typename T,typename D>
class Tree {
private:
	typedef struct {T node;D dist;T prev;} P;
	typedef pair<T,D> pr;
	typedef vector<pr> VP;
	vector<VP> E;
	T V;
	class LCA {
		public:
			T root;
			T log_2 = log2(V) + 1;
			vector<vector<T>> parent;
			vector<T> depth;
			LCA () : root(0){}
			LCA (T v) : root(v),parent(log_2,vector<T>(V)),depth(V){init();}

			void init(void) {
				stack<P> st;
				st.push(P(root,0,-1));
				while (!st.empty()) {
					T nd = st.top();st.pop();
					parent[0][nd.node] = nd.prev;
					depth[nd.node] = nd.dist;
					REP(i,E[nd.node].size()) {
						if (E[nd.node] != nd.prev){
							st.push(P(E[nd.node][i].first,nd.dist+E[nd.node][i].second,nd.node));
						}
					}
				}
				REP(k,log_2-1) {
            		REP(v,V) {
                		if (parent[k][v] < 0)
                    		parent[k + 1][v] = -1;
                		else parent[k + 1][v] = parent[k][parent[k][v]];
            		}
        		}
			}

			T query(T n1,T n2) {
				if (depth[n1] > depth[n2]) std::swap(n1, n2);
        		for (int k = 0; k < log_2; k++) {
            		if ((depth[n2] - depth[n1]) >> k & 1) {
                		n2 = parent[k][n2];
            		}
        		}
        		if (n1 == n2) return n1;
        		for (int k = log_2 - 1; k >= 0; k--) {
            		if (parent[k][n1] != parent[k][n2]) {
                		n1 = parent[k][n1];
                		n2 = parent[k][n2];
            		}
        		}
        		return parent[0][n1];
			}
	};
	LCA lc();
public:
	Tree() : V(0){}
	Tree(T v) : V(v),E(v) {}

	void addEdgeDirected(T start,T goal,D weight){
		E[start].push_back(pr(goal,weight));
	}

	void addEdgeUndirected(T start,T goal,D weight){
		E[start].push_back(pr(goal,weight));
		E[goal].push_back(pr(start,weight));
	}

	pair<T,D> farthest(T node){ // nodeからの最遠点(頂点,距離)
		vector<T> Dis;
		calcDist(node,Dis);
		T ret = (-1),dist = (-1);
		REP(i,V) {
			if (dist < Dis[i]) {
				ret = i;
            	dist = Dis[i];
			}
		}
		return (pair<T,D>(ret,dist));
	}

	void calcDist(T v, vector<D>& Dis) {
    	Dis.clear(); Dis.resize(V,loINF);
    	Dis[v] = 0;
    	queue<T> Q;
    	Q.push(v);
    	while (!Q.empty()) {
        	T c = Q.front(); Q.pop();
        	REP(i,E[c].size()) {
            	if (Dis[E[c][i].first] > Dis[c] + E[c][i].second) {
                	Dis[E[c][i].first] = Dis[c] + E[c][i].second;
                	Q.push(E[c][i].first);
            	}
            }
        }
    }

	vector<T> getHeight(void) { //全部のnodeの最遠距離。
		vector<T> Dis(V);
		T x = farthest(0).first;
   		T y = farthest(x).first;
    	vector<T> DX; calcDist(x, DX);
    	vector<T> DY; calcDist(y, DY);
    	REP(i,V) Dis[i] = max(DX[i],DY[i]);
    	return Dis;
	}

	pair<T,D> getDiameter(void){
		stack<P> st;
		pair<T,D> farV(V-1,0);
		st.push(P {V-1,0,-1});
		while (!st.empty()) {
			P e = st.top();
			st.pop();
			if (farV.second < e.dist) farV = pair<T,D> (e.node,e.dist);
			for ( auto &p : E[e.node]) {
				if (p.first != e.prev) st.push(P {p.first,e.dist+p.second,e.node});
			}
		}
		pair<T,D> farV2(farV.first,0);
		st.push(P {farV.first,0,-1});
		while (!st.empty()) {
			P e = st.top();
			st.pop();
			if (farV2.second < e.dist) farV2 = pair<T,D> (e.node,e.dist);
			for ( auto &p : E[e.node]) {
				if (p.first != e.prev) st.push(P {p.first,e.dist+p.second,e.node});
			}
		}
		return farV2;
	}

	void lca_init(void) { lc = LCA(V);}
	T lca(T n1,T n2) { return lc.query(n1,n2);}
};

int main(void) {
	long N,s,t,w;
	cin >> N;
	Tree<long,long> tr(N);
	REP(i,N-1){
		cin >> s >> t >> w;
		tr.addEdgeUndirected(s,t,w);
	}
	vector<long> p = tr.getHeight();
	REP(i,N) cout << p[i] << endl;
}