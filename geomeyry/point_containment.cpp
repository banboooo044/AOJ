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
typedef vector<LL> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<LL,LL> pr;
typedef vector<pr> VP;
struct Order {
  bool operator() (pr const& a,pr const& b) const {
    return a.first > b.first || ((a.first == b.first) && (a.second > b.second));
  }
};

typedef struct _PT {
  long double x, y;
  _PT() {}
  _PT(long double x,long double y) : x(x), y(y) {} 
  _PT operator + (_PT p){
     return _PT(x + p.x, y + p.y);
  }
  _PT operator - (_PT p){
     return _PT(x - p.x, y - p.y);
  }
  _PT operator * (long double d){
     return _PT(d*x, d*y);
  }
  bool operator <(const struct _PT &e) const{
     return (abs(x - e.x) < eps) ? ((y - e.y) < eps) : ((x - e.x) < eps);
  }
  bool operator >(const struct _PT &e) const{
     return (abs(x - e.x) < eps) ? ((y - e.y) > eps) : ((x - e.x) > eps);
  }

  // --オプジェクトは位置ベクトル--

  long double dist(_PT p){ //点pとの距離の2乗
     return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
  }

  // --オブジェクトは幾何ベクトル--
  
  long double dot(_PT v){ //ベクトルvとの内積
     return x * v.x + y * v.y;
  }
  
  long double det(_PT v){ // ベクトルvとの外積
     return x * v.y - v.x * y;
  }

  long double norm(void){ // ベクトルのノルム
    return sqrt(x*x + y*y);
  }

  long double twiceNorm(void){ // ノルムの2乗
    return x*x + y*y;
  }

  bool is_parallel(_PT v) { //ベクトルvと平行か(外積 = 0か)
    return (abs(x * v.y - v.x * y) < eps);
  }
}P;

static bool cmp_rad(const P &p1,const P &p2){
    return atan2(p1.y,p1.x) > atan2(p2.y,p2.x);
}

class Plane{
private:
  static bool cmp_x(const P &p1,const P &p2){
      if (p1.x != p2.x) return p1.x < p2.x;
      return p1.y < p2.y;
  }
public:
  P intersection(P p1,P p2,P q1,P q2) { // 直線p1-p2と直線q1-q2の交点
    return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
  }

  bool on_seq(P p1,P p2,P q) { // 線分p1-p2上に点qがあるか
    return (abs((p1 - q).det(p2 - q)) < eps) && ((p1 - q).dot(p2 - q) < (eps));
  }

  bool have_intersection(P p1,P p2,P q1,P q2) { // 線分p1-p2と線分q1-q2がが交点を持つか
    if (abs((p1-p2).det(q1-q2)) > eps) {
      P r = intersection(p1,p2,q1,q2);
      return (on_seq(p1,p2,r) && on_seq(q1,q2,r));
    }
    else return (on_seq(p1,p2,q1) || on_seq(p1,p2,q2) || on_seq(q1,q2,p1) || on_seq(q1,q2,p2));
  }

  bool inPolygon(P p,vector<P> &polygon) {
    P m = P(p.x+inf,p.y)
  }

  P projection(P v1,P v2) { // v1へのv2の正射影ベクトル
    return (v1)*((v1).dot(v2) / v1.twiceNorm());
  }

  vector<P> convexHull(vector<P> &point){
      LL n = point.size();
      vector<P> qs(n*2);
      sort(point.begin(),point.end(),cmp_x);
      long k = 0;

      REP(i,n){ //下側凸包の作成
        while(k > 1 && (qs[k-1] - qs[k-2]).det(point[i] - qs[k-1]) <= 0) k--;
        qs[k++] = point[i];
      }

      for(long i = n - 2, t = k; i >= 0; i--){ //上側凸包の作成
        while(k > t && (qs[k-1] - qs[k-2]).det(point[i] - qs[k-1]) <= 0) k--;
        qs[k++] = point[i];
      }
      qs.resize(k-1);
      return qs;
  }

  long double getArea(vector<P> &point){
      long double s = 0;
      LL n = point.size();
      REP(i,n-1) s += point[i].det(point[i+1]);
      s += point[n-1].det(point[0]);
      return abs(s) * 0.5;
  }

  long double getAngle(P v1,P v2){ //2ベクトルのなす角を出す。
    return acos(v1.dot(v2)/sqrt(v1.twiceNorm() * v2.twiceNorm()));
  }
};

int main(void) {
  Plane pl;
  int n,q,n2;
  P a;
  cin >> n;
  vector<P> point(n);
  REP(i,n) cin >> point[i].x >> point[i].y;
  cin >> q;
  REP(i,q) {
    cin >> a.x >> a.y;
    P tmp = P(10001.0,a.y+0.1);
    LL cnt = 0;
    bool flg = false;
    REP(i,n-1) {
      if (pl.on_seq(point[i],point[i+1],a)) flg = true;
      if (pl.have_intersection(tmp,a,point[i],point[i+1])) {
        cnt++;
        if ((point[i]-point[i+1]).is_parallel(tmp-a)) cnt--;
      }
    }

    if (pl.on_seq(point[0],point[n-1],a)) flg = true;
    if (pl.have_intersection(tmp,a,point[0],point[n-1])) {
      cnt++;
      if ((point[0]-point[n-1]).is_parallel(tmp-a)) cnt--;
    }
    
    if (flg) cout << 1 << endl;
    else if(cnt%2) cout << 2 << endl;
    else cout << 0 << endl;
  }


}
