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
     return x == e.x? (y < e.y) : x < e.x;
  }
  bool operator >(const struct _PT &e) const{
     return abs(x - e.x) < eps ? ((y - e.y) > eps) : ((x - e.x)>eps);
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

int main(void) {
  double px,py,qx,qy,rx,ry;
  cin >> px >> py >> qx >> qy;
  double base = atan2((qy-py),(qx-px));
  int n;
  cin >> n;
  REP(i,n) {
    cin >> rx >> ry;
    double rad = atan2((ry-py),(rx-px));
    if (abs(rad-base) < eps || (px == rx)&&(py == ry)) { //重なってる場合 
      if (P(rx-px,ry-py).twiceNorm() > P(qx-px,qy-py).twiceNorm()) cout << "ONLINE_FRONT" << endl; 
      else cout << "ON_SEGMENT" << endl;
    }
    else if (abs(abs(rad - base)-pi) < eps) cout << "ONLINE_BACK" << endl; // 真裏
    else if ((rad > base && (rad - base) < pi) || (rad < base && (base - rad) > pi)) cout << "COUNTER_CLOCKWISE" << endl;
    else cout << "CLOCKWISE" << endl;
  }
}