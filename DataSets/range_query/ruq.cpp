#include <bits/stdc++.h>
#define REP(i,n) for (long long i=0;i<(n);i++)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
using namespace std;
/*
struct Monoid {
    using T = _underlying_set_;
    static  T op(const T& a, const T& b) { return _a_op_b_; }
    static constexpr T identity() { return _identity_element_; }
};
*/
template <class Monoid,class MonoidAct>
class LazySegmentTree {
private:
    using T1 = typename Monoid::T;
    using T2 = typename MonoidAct::T;
    vector<T1> data;
    vector<T2> lazy;
    const size_t h, n;

    //オペレータ2 MonoidAct -> Monoid
    //static T1 op2(const T1& l,const T2& r) { return r != MonoidAct::id() ? r : l; }
    static T1 op2(const T1& l,const T2& r) { return r != MonoidAct::id() ? r : l; }

private:
    void eval(size_t node) {
        if (lazy[node] == MonoidAct::id()) return;
        if (node < n) {
            lazy[node * 2] = MonoidAct::op3(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = MonoidAct::op3(lazy[node * 2 + 1], lazy[node]);
        }
        data[node] = op2(data[node], lazy[node]);
        lazy[node] = MonoidAct::id();
    }
    void update(size_t node) {
        data[node] = Monoid::op1(op2(data[node * 2], lazy[node * 2])
                        ,op2(data[node * 2 + 1], lazy[node * 2 + 1]));
    }

public:
    LazySegmentTree(int n_)
        : h(ceil(log2(n_))), n(1 << h) {data.resize(n * 2, Monoid::id());lazy.resize(n * 2, MonoidAct::id());}
    LazySegmentTree(int n_, T1 v1)
        : h(ceil(log2(n_))), n(1 << h) {data.resize(n * 2, v1);lazy.resize(n * 2, MonoidAct::id());}
    LazySegmentTree(const vector<T1>& data_)
        : h(ceil(log2(data_.size()))), n(1 << h) {
            data.resize(n * 2,Monoid::id());
            lazy.resize(n * 2, MonoidAct::id());
            init(data_);   
    }
    void init() {
        for (int i = n - 1; i >= 1; i--) data[i] = Monoid::op1(data[i * 2], data[i * 2 + 1]);
    }
    void init(const vector<T1>& data_) {
        for (int i = 0; i < (int)data_.size(); i++) data[i + n] = data_[i];
        init();
    }

    T1 operator[](size_t i) { return find(i,i+1);}

    void update(size_t l, size_t r, T2 val) {
        l += n, r += n - 1;
        for (int i = h; i > 0; i--) eval(l >> i), eval(r >> i);
        size_t tl = l, tr = r;
        r++;
        while (l < r) {
            if (l & 1) lazy[l] = MonoidAct::op3(lazy[l], val), l++;
            if (r & 1) r--, lazy[r] = MonoidAct::op3(lazy[r], val);
            l >>= 1; r >>= 1;
        }
        while (tl >>= 1, tr >>= 1, tl) {
            if (lazy[tl] == MonoidAct::id()) update(tl);
            if (lazy[tr] == MonoidAct::id()) update(tr);
        }
    }
    T1 find(size_t l, size_t r) {
        l += n, r += n - 1;
        for (int i = h; i > 0; i--) eval(l >> i), eval(r >> i);
        r++;
        T1 res1 = Monoid::id(), res2 = Monoid::id();
        while (l < r) {
            if (l & 1) res1 = Monoid::op1(res1, op2(data[l], lazy[l])), l++;
            if (r & 1) r--, res2 = Monoid::op1(op2(data[r], lazy[r]), res2);
            l >>= 1; r >>= 1;
        }
        return Monoid::op1(res1, res2);
    }
};

// findモノイド
struct RMQ { // 区間の最小
    using T = int;
    static T op1(const T& a, const T& b) { return min(a, b); }
    static constexpr T id() {return numeric_limits<T>::max(); }
};

// updateモノイド
struct U { // 区間に代入更新
    using T = int;
    static T op3(const T& l,const T& r) { return r != id() ? r : l;}
    static constexpr T id() { return 0;}
};

int main(void) {
    int n,q,com,s,t,x;
    cin >> n >> q;
    vector<int> a(n,0);
    LazySegmentTree<RMQ,U> sg(a);
    REP(i,q) {
        cin >> com;
        if (!com) {
            cin >> s >> t >> x;
            sg.update(s,t+1,x);
        }
        else {
            cin >> s;
            cout << sg[s] << endl;
        }
    }
}
//00:13 sec    5408 KB     4706 bytes     