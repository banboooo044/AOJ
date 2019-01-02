#include <bits/stdc++.h>
#define REP(i,n) for (long long i=0;i<(n);i++)
#define FOR(i,a,b) for (long long i=(a);i<(b);i++)
#define RREP(i,n) for(long long i=n;i>=0;i--)
#define RFOR(i,a,b) for(long long i=(a);i>(b);i--)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl
#define dump(x)  cerr << #x << " => " << (x) << endl
#define dumpP(p) cerr << "( " << p.first << " , " << p.second << " )" << ends
#define SORT(c) sort((c).begin(),(c).end())
#define MIN(vec) *min_element(vec.begin(), vec.end())
#define MAX(vec) *max_element(vec.begin(), vec.end())
#define UNIQ(vec) vec.erase(unique(vec.begin(), vec.end()),vec.end()) //ソートの必要あり
#define IN(n,m)  (!(m.find(n) == m.end()))
#define ENUM(m) for (auto itr = m.begin(); itr != m.end(); ++itr)
#define dump_MAP(m) for(auto itr = m.begin(); itr != m.end(); ++itr) { cerr << itr->first << " --> "  << itr->second << endl; }
#define FINDL(vec,x) (lower_bound(vec.begin(),vec.end(),x) - vec.begin())
#define FINDU(vec,x) (upper_bound(vec.begin(),vec.end(),x) - vec.begin())
#define ROUND(N) setprecision(N)
#define ROUND_PRINT(N,val) cout << fixed;cout << setprecision(N) << val << endl
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define INARR(h,w,x,y) (0 <= y && y < h && 0 <= x && x < w)
#define EQ(a,b) (abs(a - b) < 1e-10)
using namespace std;
constexpr int dx[4] = {0,1,0,-1};
constexpr int dy[4] = {1,0,-1,0};
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
typedef vector<bool> VB;
typedef vector<pr> VP;
struct Order {
	bool operator() (pr const& a,pr const& b) const {
		return a.first > b.first || ((a.first == b.first) && (a.second > b.second));
	}
};

bool eq(double a,double b){ return a>b?a-b<eps:b-a<eps; }
class Point { //位置ベクトルと作用ベクトルを同一視
public:
	double x;
	double y;
	Point(double X=0.0,double Y=0.0):x(X),y(Y){}
	Point(const Point &m):x(m.x),y(m.y) {}
	Point operator+(const Point &p){return Point(x+p.x,y+p.y);}
	Point operator-(const Point &p){return Point(x-p.x,y-p.y);}
	Point operator*(const double k){return Point(x*k,y*k);}
	Point operator/(const double k){return Point(x/k,y/k);}
	Point operator=(const Point &p){x=p.x;y=p.y;return *this;}
	Point rev() {return Point(-x,-y);}
	bool operator<(const Point &p){return x!=p.x?x<p.x:y<p.y;}
	bool operator>(const Point &p){return x!=p.x?x>p.x:y>p.y;}
	bool operator==(const Point &p){return eq(x,p.x)&&eq(y,p.y);}
	double norm(){ return x*x+y*y; }
	double abs() { return sqrt(norm());}
	double dist(const Point &a) { return (Point(x,y)-a).abs(); }
	double dot(const Point &a) { return x*a.x + y*a.y; }
	//外積 -> 2vec向き付き角度判定,平行四辺形面積
	double det(const Point &a) { return x*a.y - y*a.x; }
	bool is_parallel(const Point &a) { return eq((x*a.y - y*a.x),0); }
	// a -> this の正射影
	Point proj(const Point &a) { return Point(x,y)*(dot(a)/norm()); }
	//2ベクトルのなす角 (正 : 時計回り, 負 : 反時計)
	double ang(const Point &v) {
		double g1 = atan2(v.y,v.x);
		double g2 = atan2(y,x);
		if (g1 < 0) g1 += (2 * M_PI);
		if (g2 < 0) g2 += (2 * M_PI);
		return (g2 - g1);
	}
	//2ベクトルのなす角(正値)を出す。
	double absAng(Point &v){ 
    	return acos(dot(v)/sqrt(norm() * v.norm()));
  	}

};

class Segment {
public:
	Point p1;
	Point p2;
	Segment(double x1,double y1,double x2,double y2) : p1(x1,y1),p2(x2,y2) {}
	Segment(const Point &a,const Point &b) : p1(a),p2(b) {}
	double len (const Segment &l) { return (p2 - p1).norm(); }
	inline Point toVec() { return (p2 - p1); }
};

// 線分Xと線分Yの交点
Point intersection(Segment X,Segment Y) {
	return X.p1 + (X.p2 - X.p1) * (Y.p2 - Y.p1).det((Y.p1 - X.p1)) / (Y.p2 - Y.p1).det(X.p2 - X.p1);
}

// 線分X上に点qがあるか
bool on_seq(Segment X,Point q) {
	return (eq((X.p1 - q).det(X.p2 - q),0) && (X.p1 - q).dot(X.p2 - q) < eps);
}

// 線分Xと線分Yが交点を持つか
bool have_intersection(Segment X,Segment Y) {
	if (!(X.toVec()).is_parallel(Y.toVec())) {
		Point r = intersection(X,Y);
		return (on_seq(X,r) && on_seq(Y,r));
    }
    else return (on_seq(X,Y.p1) || on_seq(X,Y.p2) || on_seq(Y,X.p1) || on_seq(Y,X.p2));
}

// 二つの線分の位置関係
int ccw(Point a,Point b,Point c) { // aが支点
	complex<double> v1(b.x-a.x,b.y-a.y),v2(c.x-a.x,c.y-a.y);
	complex<double> v = (v2*conj(v1));
	if(v.imag()>eps)return 1;        //反時計回り
	if(v.imag()<-eps)return -1;      //時計回り
	if(v.real()<-eps)return 2;       //真逆
	if(abs(v1)+eps<abs(v2))return -2;//同じ側超えてる
	return 0;                        //同じ側近い側
}
// 線分Xと点qの距離
double distance1 (Segment X,Point q) { 
	if (eq((X.p1 - X.p2).dot(q - X.p2),0)) return X.p2.dist(q);
	if (eq((X.p2 - X.p1).dot(q - X.p1),0)) return X.p1.dist(q);
	else return (X.p1 + (X.p2-X.p1).proj(q-X.p1)).dist(q);
}

//線分Xと線分Yの距離
double distance2 (Segment X,Segment Y) { 
	if (have_intersection(X,Y)) return 0.0;
	else return min({distance1(X,Y.p1),distance1(X,Y.p2),distance1(Y,X.p1),distance1(Y,X.p2)});
}

//点列をx座標で昇順ソート
inline void sort_x(vector<Point> &p) { 
	struct comp { bool operator() (const Point &a,const Point &b) {return (a.x!=b.x?a.x<b.x:a.y<b.y);} };
	sort(p.begin(),p.end(),comp());
}

//点列をy座標で昇順ソート
inline void sort_y(vector<Point> &p) { 
	struct comp { bool operator() (const Point &a,const Point &b) {return (a.y!=b.y?a.y<b.y:a.x<b.x);} };
	sort(p.begin(),p.end(),comp());
}

//多角形の面積 (point列は順番になっていること)
double getArea(vector<Point> &point){
	double s = 0;
	int n = point.size();
	for (int i = 0;i < n;i++ ) s += point[i%n].det(point[(i+1)%n]);
	return abs(s) * 0.5;
}

//0: outside, 1: on line, 2: inside (Winding Number)
int contains(const vector<Point> &point, Point p) {
    int flg = -1;
    Point _a, _b = point.back();
    for (int i = 0; i < int(point.size()); i++) {
        _a = _b; _b = point[i];
        Point a = _a, b = _b;
        if (ccw(a, b, p) == 0) return 1;
        if (a.y > b.y) swap(a, b);
        if (!(a.y <= p.y && p.y < b.y)) continue;
        // (a-p).det(b-p) > eps) : 線の内側
        if (eq(a.y,p.y) ? (a.x > p.x):((a-p).det(b-p) > eps)) flg *= -1;
    }
    return flg + 1;
}

//凸包(グラハムスキャン)
vector<Point> convexHull(vector<Point> &point){
	int n = point.size(),k = 0;
	vector<Point> qs(n*2);
	sort_x(point);
	for(int i = 0;i < n;i++){ //下側凸包の作成
		while(k > 1 && (qs[k-1] - qs[k-2]).det(point[i] - qs[k-1]) < (-eps)) k--;
		// 平行な点を削除 -> while(k > 1 && (qs[k-1] - qs[k-2]).det(point[i] - qs[k-1]) < (eps)) k--;
		qs[k++] = point[i];
	}
	for(int i = n - 2, t = k; i >= 0; i--){ //上側凸包の作成
		while(k > t && (qs[k-1] - qs[k-2]).det(point[i] - qs[k-1]) <= (-eps)) k--;
		// 平行な点を削除 -> while(k > t && (qs[k-1] - qs[k-2]).det(point[i] - qs[k-1]) <= (eps)) k--;
		qs[k++] = point[i];
	}
	qs.resize(k-1);
	return qs;
}

//最遠頂点対間距離 (pはConvex)
double diameter(vector<Point> &p) {
    int n = int(p.size());
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[x]) x = i;
        if (p[y] < p[i]) y = i;
    }
    double ans = 0;
    int sx = x, sy = y;
    while (sx != y || sy != x) {
        ans = max(ans, (p[x]).dist(p[y]));
        int nx = ((x+1) % n),ny = ((y+1)%n);
        if ((p[nx] - p[x]).det(p[ny] - p[y]) < 0.0) x = nx;
        else y = ny;
    }
    return ans;
}

int main(void) {
	long n;
	double x,y;
	cin >> n;
	vector<Point> p(n);
	REP(i,n) {
		cin >> x >> y;
		p[i] = Point(x,y);
	}
	vector<Point> m = convexHull(p);
	double v = diameter(m);
	ROUND_PRINT(10,v);
}



