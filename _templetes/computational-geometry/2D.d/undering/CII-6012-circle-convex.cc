#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;


const double EPS = 1e-8;
const double PI  = acos(-1.0);

double  pow2(double x)  {return x * x;}
int     sign(double x)  {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
// Fix angle in [0, 2*PI]
double fix_p(double th) {return sign(th) < 0 ? th + 2*PI : th;}
// Fix angle in [-PI, PI]
double   fix(double th) {return sign(th + PI) < 0 ? th+2*PI : sign(th - PI) > 0 ? th-2*PI : th;}
double _acos(double th) {return sign(th + 1) <= 0 ?      PI : sign(th - 1) >= 0 ?       0 : acos(th);}
double _asin(double th) {return sign(th + 1) <= 0 ?   -PI/2 : sign(th - 1) >= 0 ?    PI/2 : asin(th);}


struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // Used in Circle Convex Hull
    int id; Point(Point p, int _id) {x = p.x, y = p.y; id = _id;}

    Point  operator -() const {return Point(-x, -y);}
    Point  operator +(const Point  &p) const {return Point(x+p.x, y+p.y);}
    Point  operator -(const Point  &p) const {return Point(x-p.x, y-p.y);}
    Point  operator *(const double &s) const {return Point(x*s, y*s);}
    Point  operator /(const double &s) const {return Point(x/s, y/s);}
    
    double operator ^(const Point  &p) const {return x*p.y - y*p.x;}
    double operator *(const Point  &p) const {return x*p.x + y*p.y;}

    bool   operator <(const Point  &p) const {return sign(x - p.x) < 0 || (sign(x - p.x) == 0 && sign(y - p.y) < 0);}

    
    // rotate vector (Right/Left hand)
    Point  R(double th) {return Point(x*cos(th)-y*sin(th), x*sin(th)+y*cos(th));}
    Point  L(double th) {return R(2*PI - th);}
    
    double len2()  {return x*x + y*y;}
    double len()   {return sqrt(len2());}
    double ang()   {return atan2(y, x);}
    Point  e()     {return Point(x/len(), y/len());}
    void   get()   {cin >> x >> y;}
    void   print() {cout << "Point: (" << x << ", " << y << ")" << endl;}
};

struct Line {
    Point a, b;
    Line(Point a, Point b) : a(a), b(b) {}

    void get() {a.get(); b.get();}
    void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
};

struct Circle {
    Point  o;
    double r;

    // Area of ``circular segment'' (弓形)
    double segment_area(const double &th) {return 0.5 * pow2(r) * (th - sin(th));}
    double dis(const Circle &c) const {return (o - c.o).len();}

    // -2: 内含 (d < R - r) // -1: 内切 (d = R - r)
    //  0: 相交 (R - r < d < R + r)
    //  1: 外切 (d = R + r) //  2: 外离 (d > R + r)
    int pos(const Circle &c) const {
		double d = dis(c);
        int pd1 = sign(d - fabs(r - c.r)), pd2 = sign(d - (r + c.r));
        return pd1<0? -2 : pd1==0? -1 : pd2==0? 1 : pd2>0? 2 : 0;
	}

    // 两圆相交弦，满足两圆相交
    // 返回此圆上逆时针
    // TODO:test
    Line chord(const Circle &c) const {
        Point v = c.o - o;
        double th = _acos((pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len()));
        return Line(v.L(th).e() * r + o, v.R(th).e() * r + o);
    }

    // 两圆相切交点
    // _d = 0 切线不交叉，须满足相交、外切或外离
    // _d = 1 切线交叉，须满足外离
    // 返回圆上逆时针
    // TODO:test
    Line tangent_points(const Circle &c, const int &_d) const {
        Point  v = c.o - o;
        double th = _acos((_d&0x1 ? r+c.r : r-c.r) / v.len());
        return Line(v.L(th).e() * r + o, v.R(th).e() * r + o);
    }

    // 两圆切线单位向量
    // _d = 0 切线不交叉，须满足相交、外切或外离
    // _d = 1 切线交叉，须满足外离
    // 返回起点逆时针
    Line tangent_vector(const Circle &c, const int &_d) const {
        Point v = c.o - o;
        double th = _asin((_d&0x1 ? r+c.r : r-c.r) / v.len());
        return Line(v.R(th).e(), v.L(th).e());
    }

    void get()   {o.get(); cin >> r;}
    void print() {cout << "Circle:" << endl; cout << " `--"; o.print(); cout << " `--R: " << r << endl;}
};


// -PI <= th <= PI
struct Range {
    double th;
    int    t;
    Range(double th = 0, int t = 0) : th(th), t(t) {}
    bool operator <(const Range &s) const {return sign(th - s.th) < 0 || (sign(th - s.th) == 0 && t > s.t);}
};


// 圆环区间
struct Ranges {
    int nc;
    vector<Range> R;
    Ranges() {clear();}
    void clear() {nc = 0; R.clear();}
    
    void add(double th, int     t) {R.push_back(Range(th, t));}
    void add(double st, double ed) {st = fix(st); ed = fix(ed); if (sign(st - ed) > 0) ++ nc; add(st, 1); add(ed, -1);}
    void add(Point  st, Point  ed) {add(st.ang(), ed.ang());}
    void add(Line l) {add(l.a, l.b);}
    
    void run() {sort(R.begin(), R.end());}
    
    int get_max() {
        int r = nc;
        double pj = - PI;
        for(int j = 0; j < R.size(); ++ j) {
            nc += R[j].t; pj  = R[j].th;
            r = max(r, nc);
        }
        return r;
    }
};


// 凸包模板
vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; i++) {
        while (k >= 2 && sign((H[k-1]-H[k-2])^(P[i]-H[k-2])) <= 0) -- k;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && sign((H[k-1]-H[k-2])^(P[i]-H[k-2])) <= 0) -- k;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}


// 多圆凸包（周长）
double circle_convex_hull(vector<Circle> &C)
{
    int n = C.size();
    if (n == 1) return 2 * PI * C[0].r;

    vector<Point> P;
    for (int i = 0; i < n; ++ i)
        for (int j = i + 1; j < n; ++ j)
        {
            Line li = C[i].tangent_points(C[j], 0);
            Line lj = C[j].tangent_points(C[i], 0);
            P.push_back(Point(li.a, i));
            P.push_back(Point(li.b, i));
            P.push_back(Point(lj.a, j));
            P.push_back(Point(lj.b, j));
        }

    vector<Point> CH = convex_hull(P);

    double ans = 0;
    int m = CH.size() - 1;
    for (int i = 0; i < m; ++ i)
    {
        if (CH[i].id != CH[i+1].id)
            ans += (CH[i] - CH[i+1]).len();
        else
        {
            Circle c = C[CH[i].id];
            ans += c.r * fix_p((CH[i+1] - c.o).ang() - (CH[i] - c.o).ang());
        }
    }
    
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<Circle> C(n);
        for (int i = 0; i < n; ++ i)
            C[i].get();

        double ans = circle_convex_hull(C);
        printf("%.5lf\n", ans);
    }
    return 0;
}
