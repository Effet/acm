#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);

double  pow2(double x)  {return x * x;}
int     sign(double x)  {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
// Fix angle in [0, 2*PI]
double fix_p(double th) {return th < 0 ? th + 2*PI : th;}
// Fix angle in [-PI, PI]
double   fix(double th) {return th < -PI ? th+2*PI : th > PI ? th-2*PI : th;}
double _acos(double th) {return th <= -1 ?      PI : th >= 1 ?       0 : acos(th);}
double _asin(double th) {return th <= -1 ?   -PI/2 : th >= 1 ?    PI/2 : asin(th);}


struct Point {
    double x, y;
    int id; // Used in Circle Convex Hull
    Point(){} Point(double x, double y) : x(x), y(y) {}

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
    Line(){} Line(Point a, Point b) : a(a), b(b) {}

    void get() {a.get(); b.get();}
    void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
};

struct Circle {
    Point  o;
    double r;

    // Area of ``circular segment'' (弓形面积)
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
    // FIXME: _acos() may wrong
    Line chord(const Circle &c) const {
        Point v = c.o - o;
        double th = _acos((pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len()));
        return Line(v.L(th).e() * r + o, v.R(th).e() * r + o);
    }

    // 两圆相切交点
    // _d = 0 切线不交叉，须满足相交、外切或外离
    // _d = 1 切线交叉，须满足外离
    // 返回圆上逆时针
    // FIXME: _acos() may wrong
    Line tangent_points(const Circle &c, const int &_d) const {
        Point  v = c.o - o;
        double th = _acos((_d&0x1 ? r+c.r : r-c.r) / v.len());
        return Line(v.L(th).e() * r + o, v.R(th).e() * r + o);
    }

    // 两圆切线单位向量
    // _d = 0 切线不交叉，须满足相交、外切或外离
    // _d = 1 切线交叉，须满足外离
    // 返回起点逆时针
    // FIXME: _asin() may wrong
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

    // Used in Circle Union
    Point p; Range(double th, int t, Point p) : th(th), t(t), p(p) {}

    bool operator <(const Range &s) const {return sign(th - s.th) < 0 || (sign(th - s.th) == 0 && t > s.t);}
};


// 圆环区间(Simple)
struct Ranges {
    int nc;
    vector<Range> R;
    Ranges() {clear();}
    void clear() {nc = 0; R.clear();}

    void add(double th, int     t) {R.push_back(Range(th, t));}
    void add(double st, double ed) {if (sign(st - ed) > 0) ++ nc; add(st, 1); add(ed, -1);}
    void add(Point  st, Point  ed) {add(fix(st.ang()), fix(ed.ang()));}
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


// 平面一直线最多能与几个圆相交 （建立在最优直线可为一圆切线推论下）
int a_line_cut_circle(vector<Circle> &C)
{
    int n = C.size();
    int ans = 0;
    Ranges R;
    for (int i = 0; i < n; ++ i)
    {
        int cnt = 0;
        R.clear();
        for (int j = 0; j < n; ++ j)
        {
            if (j == i) continue;

            int pd = C[i].pos(C[j]);
            if (pd == -2 || pd == -1) { // 包含
                if (sign(C[i].r - C[j].r) <= 0) ++ cnt;
                continue;
            }

            // // A more fater version, only use angles
            // Point  v = C[j].o - C[i].o;
            // double d = v.len();
            // double th_ji = atan2( v.y,  v.x);
            // double th_ij = atan2(-v.y, -v.x);
            // double vt1 = asin((C[i].r + C[j].r) / d);
            // double vt2 = asin((C[i].r - C[j].r) / d);

            // if (pd == 0 || pd == 1) // 相交
            //     R.add(th_ij + vt2, th_ji - vt2);
            // else // 相离
            // {
            //     R.add(th_ji - vt1, th_ji - vt2);
            //     R.add(th_ij + vt2, th_ij + vt1);
            // }
            // // End of it

            Line v1 = C[i].tangent_vector(C[j], 0);
            Line v2 = C[i].tangent_vector(C[j], 1);
            if (pd == 0 || pd == 1) // 相交
                R.add(v1.a, -v1.b);
            else // 相离
            {
                R.add(v1.a, v2.a);
                R.add(-v2.b, -v1.b);
            }
        }

        R.run();
        cnt += R.get_max();
        ans = max(ans, cnt);
    }

    return ans + 1;
}


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
            li.a.id = i; P.push_back(li.a);
            li.b.id = i; P.push_back(li.b);
            lj.a.id = j; P.push_back(lj.a);
            lj.b.id = j; P.push_back(lj.b);
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


// 圆并返回交了k次的面积
vector<double> union_circle(vector<Circle> &C)
{
    int n = C.size();
    vector<double> area(n + 1, 0);

    for (int i = 0; i < n; ++ i)
    {
        Point mpi = Point(- C[i].r, 0.0) + C[i].o;
        vector<Range> R(2);
        R[0] = Range(-PI,  1, mpi);
        R[1] = Range( PI, -1, mpi);
        int nc = 0;
        for (int j = 0; j < n; ++ j)
        {
            if (j == i) continue;

            int pd = C[i].pos(C[j]);
            if (pd == 1 || pd == 2) continue; // 外切或外离
            if (pd == -2 || pd == -1) { // 内含或内切
                if(sign(C[j].r - C[i].r) > 0) {
                    R.push_back(Range(-PI,  1, mpi));
                    R.push_back(Range( PI, -1, mpi));
                }
                continue;
            }
            Line l = C[i].chord(C[j]);
            double jR = (l.a - C[i].o).ang(), jL = (l.b - C[i].o).ang();
            if (sign(jR - jL) > 0) ++ nc;
            R.push_back(Range(jR,  1, l.a));
            R.push_back(Range(jL, -1, l.b));
        }
        sort(R.begin(), R.end());

        double pj = - PI;
        Point  pp = mpi;
        for(int j = 0; j < R.size(); ++ j)
        {
            double ts = C[i].segment_area(R[j].th - pj) + (pp ^ R[j].p) * 0.5;

            area[nc] += ts;
            if(nc > 1)
                area[nc - 1] -= ts;
            
            nc += R[j].t;
            pj  = R[j].th;
            pp  = R[j].p;
        }
    }
    return area;
}


// 一由一起点发射的射线最多交多少线段
int a_line_cut_lines(Point &st, vector<Line> &L)
{
    Ranges R;
    for (int j = L.size() - 1; j >= 0; -- j)
    {
        Line l = L[j];
        l.a = (l.a - st).e(); l.b = (l.b - st).e();
        int rd = sign(l.a ^ l.b);
        if (rd == 0 && sign(l.a * l.b) <= 0)
        { // 点在线上
            ++ R.nc;
            continue;
        }
        
        if (rd < 0) // 保持逆时针
            swap(l.a, l.b);

        R.add(l);
    }
    R.run();

    return R.get_max();
}

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<Line> L(n);
        for (int i = 0; i < n; ++ i)
            L[i].get();
        
        Point st;
        st.get();

        int ans = a_line_cut_lines(st, L);

        cout << ans << endl;
    }
    return 0;
}
