#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const double INF = 1e99;

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

    bool   operator <(const Point  &p) const {return x < p.x || x == p.x && y < p.y;}

    // vector parallel/perpendicular
    bool is_H(Point v) {return sign(*this^v) == 0;}
    bool is_L(Point v) {return sign(*this*v) == 0;}

    // rotate vector (Right/Left hand)
    Point  R(double co, double si) {return Point(x*co-y*si,  x*si+y*co);}
    Point  L(double co, double si) {return Point(x*co+y*si, -x*si+y*co);}
    Point  R(double th) {return R(cos(th), sin(th));}
    Point  L(double th) {return L(cos(th), sin(th));}

    double len2()  {return x*x + y*y;}
    double len()   {return sqrt(len2());} // length of vector
    double ang()   {return atan2(y, x);}  // angle of vector
    Point  e()     {return Point(x/len(), y/len());}
    void   get()   {cin >> x >> y;}
    void   print() {cout << "Point: (" << x << ", " << y << ")" << endl;}
};


struct Line {
    Point a, b;
    Line(){} Line(Point a, Point b) : a(a), b(b) {}

    bool operator <(const Line &l) const {return (b-a).ang() < (l.b-l.a).ang();}

    // distance from point to line
    double dis(Point p) {return fabs(((a-p)^(b-p))) / (b-a).len();}

    // is point in a line/half line(a to b)/segment
    bool   line_of(Point p) {return sign((b-a) ^ (p-a)) == 0;}
    // not include border
    bool   half_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) > 0;}
    bool    seg_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) > 0 && sign((a-b)*(p-b)) > 0;}
    // include border
    bool half_b_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) >= 0;}
    bool  seg_b_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) >= 0 && sign((a-b)*(p-b)) >= 0;}

    // return the relation of the line and two points
    // -1: points in opposite side of line
    //  1: points in same side of line
    //  0: at least one point in line
    int pos(Point p1, Point p2) {return sign((b-a)^(p1-a)) * sign((b-a)^(p2-a));}
    
    // whether two line parallel/perpendicular
    bool is_H(Line l) {return (b-a).is_H(l.b-l.a);}
    bool is_L(Line l) {return (b-a).is_L(l.b-l.a);}

    // segment/half line intersect to segment (not border or in line)
    bool seg_seg(Line s) {return pos(s.a, s.b) < 0 && s.pos(a, b) < 0;}
    // include intersect in border or in line
    bool seg_seg_b(Line s) {
        if (line_of(s.a) && line_of(s.b))
            return seg_b_of(s.a) || seg_b_of(s.b) || s.seg_b_of(a) || s.seg_b_of(b);
        return pos(s.a, s.b) <= 0 && s.pos(a, b) <= 0;
    }

    // return the intersection point of two line (ensure not rarallel)
    Point _X_(Line l) {return a + (b-a) * (((a-l.b)^(l.a-l.b))/((a-b)^(l.a-l.b)));}
    
    // 点在线上映射 (最近点) FIXME: 可能有错
    Point p_line(Point p) {return _X_(Line(p, p+Point(b.x-a.x, a.y-b.y)));}

    void get()   {a.get(); b.get();}
    void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
};


struct Circle {
    Point  o;
    double r;

    // Area of ``circular segment'' (弓形面积)
    double segment_area(double th) {return 0.5 * pow2(r) * (th - sin(th));}
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
    Line chord(const Circle &c) const {
        Point v = c.o - o;
        double th = _acos((pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len()));
        return Line(v.L(th).e() * r + o, v.R(th).e() * r + o);
    }

    // 两圆相切交点
    // _d = 0 切线不交叉，须满足相交、外切或外离
    // _d = 1 切线交叉，须满足外离
    // 返回圆上逆时针
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


// 三角形重心
Point barycenter(Point a, Point b, Point c) {return Line((a+b)/2, c)._X_(Line((a+c)/2, b));}

struct Polygon {
    vector<Point> P;
    Polygon(){} Polygon(vector<Point> _P) {P = _P;}
    
    void get() {int n; cin >> n; P.resize(n); for (int i = 0; i < n; ++ i) P[i].get();}

    // 多边形面积，逆/顺时针
    double polygon_area() {
        double r = .0; int n = P.size(); P.push_back(P[0]);
        for (int i = 0; i < n; ++ i) r += (P[i] ^ P[i+1]);
        P.pop_back(); return fabs(r) / 2;
    }

    // 多边形重心，逆/顺时针
    Point barycenter() {
        Point c(.0, .0); double r = .0, t; // t is sum of area * 2
        int n = P.size(); P.push_back(P[0]);
        for (int i = 0; i < n; ++ i) {c = c + (P[i] + P[i+1]) * (t = P[i] ^ P[i+1]); r += t;}
        P.pop_back(); return c / (3 * r);
    }

    // 返回逆时针（去共线点）
    vector<Point> convex_hull() {
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

        H.resize(k-1);
        return H;
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

    vector<Point> CH = Polygon(P).convex_hull();

    double ans = 0;
    int m = CH.size(); CH.push_back(CH[0]);
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
// http://hi.baidu.com/aekdycoin/item/b8ff6adc73c0e71dd78ed0d6
// http://www.zhongsisi.com/solving-simple-polygons/
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


// 由一起点发射的射线最多交多少线段
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
