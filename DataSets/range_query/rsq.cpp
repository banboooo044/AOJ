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
/*
struct Monoid {
    using T = _underlying_set_;
    static  T op(const T& a, const T& b) { return _a_op_b_; }
    static constexpr T identity() { return _identity_element_; }
};
*/

// 下から更新
// 1-index
template <class Monoid>
class SegTree {
   private:
    using T = typename Monoid::T;
    const size_t n;
    vector<T> t;

    void prop_to(size_t i) { t[i] = Monoid::op(t[2*i+1],t[2*i+2]); }

   public:
    SegTree(size_t n, const T& v = Monoid::identity())
        : n(n), t(2*n-1, v) {}

    template <class InputIt>
    SegTree(InputIt first, InputIt last)
        : n(distance(first, last)), t(2*n-1, Monoid::identity()) { 
        copy(first, last, begin(t) + n);
        for (long long i = (n-2); i >= 0; --i) prop_to(i);
    }

    void set(size_t i, const T& v) {
        t[i += (n-1)] += v;
        while (i && ((--i) >>= 1)) prop_to(i);
        if(n >= 2) prop_to(0);
    }

    void update(size_t l,size_t r, int v) {
        for (l += (n-1), r += (n-1); l < r; l >>= 1, r >>= 1) {
            if (l & 1) t[l] += v;
            if (r & 1) t[--r] += v;
        }
    }

    T get(size_t i) { return t[i + (n-1)]; }

    T getminval(size_t l, size_t r) {
        T accl = Monoid::identity(), accr = Monoid::identity();
        for (l += (n-1), r += (n-1); l < r; l >>= 1, (--r) >>= 1) {
            if(!(l & 1)) accl = Monoid::op(accl, t[l]);
            if(!(r & 1)) accr = Monoid::op(t[r-1], accr);
        }
        return Monoid::op(accl, accr);
    }
};
/*
struct RMQ {
    using T = int;
    static T op(const T& a, const T& b) { return min(a, b); }
    static constexpr T identity() {return numeric_limits<T>::max(); }
};
*/

struct RSQ { //区間の合計
    using T = int;
    static T op(const T&a,const T& b) {return a+b;}
    static constexpr T identity() {return 0;}
};

typedef long long LL;
int main(void) {
    int n,q,com,x,y;
    cin >> n >> q;
    vector<int> a(n,0);
    SegTree<RSQ> sg(a.begin(),a.end());
    REP(i,q) {
        cin >> com >> x >> y;
        if (com) cout << sg.getminval(x,y+1) << endl;
        else sg.set(x,y);
    }
}
//00:10 sec    3892 KB     3281 bytes