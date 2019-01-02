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

class RURM {
public:
    using t1 = int;
    using t2 = int;

    static t1 id1() {
        return INT_MAX;
    }
    static t2 id2() {
        return -1;
    }
    static t1 op1(const t1& l, const t1& r) {
        return min(l, r);
    }
    static t1 op2(const t1& l, const t2& r) {
        return r != id2() ? r : l;
    }
    static t2 op3(const t2& l, const t2& r) {
        return r != id2() ? r : l;
    }
};

template <typename M>
class LazySegmentTree {
    using T1 = typename M::t1;
    using T2 = typename M::t2;

private:
    const int n;
    vector<T1> data;
    vector<T2> lazy;

private:
    int size(int n) {
        int res = 1;
        while (res < n) res <<= 1;
        return res;
    }
    void push(int node) {
        if (lazy[node] == M::id2()) return;
        if (node < n) {
            lazy[node * 2] = M::op3(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = M::op3(lazy[node * 2 + 1], lazy[node]);
        }
        data[node] = M::op2(data[node], lazy[node]);
        lazy[node] = M::id2();
    }
    T1 sub(int l, int r, int node, int lb, int ub) {
        if (ub <= l || r <= lb) return M::id1();
        if (l <= lb && ub <= r) return M::op2(data[node], lazy[node]);
        push(node);
        int c = (lb + ub) / 2;
        return M::op1(sub(l, r, node * 2, lb, c), sub(l, r, node * 2 + 1, c, ub));
    }
    void suc(int l, int r, int node, int lb, int ub, T2 val) {
        if (ub <= l || r <= lb) return;
        if (l <= lb && ub <= r) {
            lazy[node] = M::op3(lazy[node], val);
            return;
        }
        push(node);
        int c = (lb + ub) / 2;
        suc(l, r, node * 2, lb, c, val);
        suc(l, r, node * 2 + 1, c, ub, val);
        data[node] = M::op1(M::op2(data[node * 2], lazy[node * 2])
                        , M::op2(data[node * 2 + 1], lazy[node * 2 + 1]));
    }

public:
    LazySegmentTree(int n_)
        : n(size(n_)), data(n * 2, M::id1()), lazy(n * 2, M::id2()) {}
    LazySegmentTree(int n_, T1 v1)
        : n(size(n_)), data(n * 2, v1), lazy(n * 2, M::id2()) {}
    LazySegmentTree(const vector<T1>& data_)
        : n(size(data_.size())) {data.resize(n * 2, M::id1());lazy.resize(n * 2, M::id2());
        init(data_);
    }
    void init() {
        for (int i = n - 1; i >= 1; i--) data[i] = M::op1(data[i * 2], data[i * 2 + 1]);
    }
    void init(const vector<T1>& data_) {
        for (int i = 0; i < (int)data_.size(); i++) data[i + n] = data_[i];
        init();
    }
    T1 find(int l, int r) {
        return sub(l, r, 1, 0, n);
    }
    void update(int l, int r, T2 val) {
        suc(l, r, 1, 0, n, val);
    }
};

int main(void) {
    int n,q,com,s,t,x;
    cin >> n >> q;
    vector<int> a(n,numeric_limits<int>::max());
    LazySegmentTree<RURM> sg(a);
    REP(i,q) {
        cin >> com;
        if (!com) {
            cin >> s >> t >> x;
            sg.update(s,t+1,x);
        }
        else {
            cin >> s >> t;
            cout << sg.find(s,t+1) << endl;
        }
    }
}

//00:14 sec    5216 KB     4421 bytes   