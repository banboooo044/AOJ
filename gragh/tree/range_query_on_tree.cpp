#include <bits/stdc++.h>
#define REP(i,n) for (long long i=0;i<(n);i++)
#define FOR(i,a,b) for (long long i=(a);i<(b);i++)
#define RREP(i,n) for(long long i=n;i>=0;i--)
#define RFOR(i,a,b) for(long long i=(a);i>(b);i--)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define dumpP(p) cerr << "( " << p.first << " , " << p.second << " )" << ends;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define SORT(c) sort((c).begin(),(c).end())
#define MIN(vec) *min_element(vec.begin(), vec.end());
#define MAX(vec) *max_element(vec.begin(), vec.end());
#define UNIQ(vec) vec.erase(unique(vec.begin(), vec.end()),vec.end());
#define IN(n,m)  (!(m.find(n) == m.end()))
#define ENUM(m) for (auto itr = m.begin(); itr != m.end(); ++itr)
#define dump_MAP(m) for(auto itr = m.begin(); itr != m.end(); ++itr) { cerr << itr->first << " --> "  << itr->second << endl; }
#define FINDL(vec,x) (lower_bound(vec.begin(),vec.end(),x) - vec.begin())
#define FINDU(vec,x) (upper_bound(vec.begin(),vec.end(),x) - vec.begin())
#define ROUND(N) setprecision(N)
#define ROUND_PRINT(N,val) cout << fixed;cout << setprecision(N) << val << endl
using namespace std;
constexpr long double pi = M_PI;
constexpr double eps = 1e-10;
constexpr long mod = 1000000007;
constexpr short shINF = 32767;
constexpr long loINF = 2147483647;
constexpr long long llINF = 9223372036854775807;
typedef long long LL;
typedef vector<long> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<LL,LL> pr;
typedef vector<pr> VP;
struct Order {
	bool operator() (pr const& a,pr const& b) const {
		return a.first > b.first || ((a.first == b.first) && (a.second > b.second));
	}
};

VVI E;
VI idx;
VI chil_idx;
long dfs(long node,long num) {
	idx[node] = num;
	if (E[node].size() == 0) return chil_idx[node] = num;
	else {
		long next = num;
		REP(i,E[node].size()) {
			next = dfs(E[node][i],next+1);
		}
		chil_idx[node] = next;
	}
}

template <class Monoid,class MonoidAct,typename N>
class LazySegmentTree {
private:
    using T1 = typename Monoid::T;
    using T2 = typename MonoidAct::T;
    vector<T1> data;
    vector<T2> lazy;
    vector<N> rank; 
    const size_t h, n;

    //オペレータ2 MonoidAct -> Monoid (値がどう変化するか)

    // RUQ -> RMQ
    static T1 op2(const T1& l,const T2& r,const N& num) {return r != MonoidAct::id() ? r : l; }
    // RAQ -> RMQ
    //static T1 op2(const T1& l,const T2& r,const N& num) {return l + r; }
    // RAQ -> RSQ 
    //static T1 op2(const T1& l,const T2& r,const N& num) {return l + (r*num); }
    // RUQ -> RSQ
    //static T1 op2(const T1& l,const T2& r,const N& num) {return r != MonoidAct::id() ? r*num : l; }



private:
    void eval(size_t node) {
        if (lazy[node] == MonoidAct::id()) return;
        if (node < n) {
            lazy[node * 2] = MonoidAct::op3(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = MonoidAct::op3(lazy[node * 2 + 1], lazy[node]);
        }
        data[node] = op2(data[node],lazy[node],rank[node]);
        lazy[node] = MonoidAct::id();
    }
    void update(size_t node) {
        data[node] = Monoid::op1(op2(data[node * 2],lazy[node * 2],rank[node*2])
                        ,op2(data[node * 2 + 1],lazy[node * 2 + 1],rank[node*2+1]));
    }

public:
    LazySegmentTree(size_t n_)
        : h(ceil(log2(n_))), n(1 << h) {data.resize(n * 2, Monoid::id());lazy.resize(n * 2, MonoidAct::id());rank.resize(n*2);init();}
    LazySegmentTree(size_t n_, T1 v1)
        : h(ceil(log2(n_))), n(1 << h) {data.resize(n * 2, v1);lazy.resize(n * 2, MonoidAct::id());rank.resize(n*2);init();}
    LazySegmentTree(const vector<T1>& data_)
        : h(ceil(log2(data_.size()))), n(1 << h) {
            data.resize(n * 2,Monoid::id());
            lazy.resize(n * 2, MonoidAct::id());
            rank.resize(n*2);
            init(data_);
    }
    void init() {
        for (N i = 0;i < n;i++) rank[i+n] = 1;
        for (N i = n - 1; i >= 1; i--) {
            data[i] = Monoid::op1(data[i * 2], data[i * 2 + 1]);
            rank[i] += (rank[i*2] + rank[i*2+1]);
        }
    }
    void init(const vector<T1>& data_) {
        for (N i = 0; i < (N)data_.size(); i++) {
            data[i + n] = data_[i];
        }
        init();
    }

    T1 operator[](size_t i) { return find(i,i+1);}

    void update(size_t l, size_t r, T2 val) {
        l += n, r += n - 1;
        for (N i = h; i > 0; i--) eval(l >> i), eval(r >> i);
        size_t tl = l, tr = r;
        r++;
        while (l < r) {
            if (l & 1) lazy[l] = MonoidAct::op3(lazy[l], val), l++;
            if (r & 1) r--, lazy[r] = MonoidAct::op3(lazy[r],val);
            l >>= 1; r >>= 1;
        }
        while (tl >>= 1, tr >>= 1, tl) {
            if (lazy[tl] == MonoidAct::id()) update(tl);
            if (lazy[tr] == MonoidAct::id()) update(tr);
        }
    }
    T1 find(size_t l, size_t r) {
        l += n, r += n - 1;
        for (N i = h; i > 0; i--) eval(l >> i), eval(r >> i);
        r++;
        T1 res1 = Monoid::id(), res2 = Monoid::id();
        while (l < r) {
            if (l & 1) res1 = Monoid::op1(res1, op2(data[l],lazy[l],rank[l])), l++;
            if (r & 1) r--, res2 = Monoid::op1(op2(data[r],lazy[r],rank[r]),res2);
            l >>= 1; r >>= 1;
        }
        return Monoid::op1(res1, res2);
    }
};


// findモノイド
struct RMQ { // 区間の最小
    using T = long;
    static T op1(const T& a, const T& b) { return min(a,b); }
    static constexpr T id() {return numeric_limits<T>::max();}
};
struct RSQ { // 区間の和
    using T = long;
    static T op1(const T& a, const T& b) { return (a+b); }
    static constexpr T id() {return 0; }
};

// updateモノイド
struct RUQ { // 区間に代入更新
    using T = long;
    static T op3(const T& l,const T& r) { return r != id() ? r : l;}
    static constexpr T id() { return numeric_limits<T>::max(); }
};

struct RAQ { // 区間に加算
    using T = long;
    static T op3(const T& l,const T& r) { return l+r;}
    static constexpr T id() { return 0;}
};

int main(void) {
	long n,k,x,q,com,v,w;
	cin >> n;
	idx = VI(n);
	chil_idx = VI(n);
	E = VVI(n);
	REP(i,n) {
		cin >> k;
		REP(j,k) {
			cin >> x;
			E[i].push_back(x);
		}
	}
	dfs(0,0);
	LazySegmentTree<RMQ,RAQ,long> sg(n,0);
	cin >> q;
	REP(i,q) {
		cin >> com;
		if (!com) {
			cin >> v >> w;
			sg.update(idx[v],chil_idx[v]+1,w);
		}
		else {
			cin >> v;
			cout << sg[idx[v]] << endl;
		}
	}
}

