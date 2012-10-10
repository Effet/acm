#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


const double EPS = 1e-8;
const double PI  = acos(-1.0);

double  pow2(double x)  {return x * x;}
int     sign(double x)  {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
// Fix angle in [-PI, PI]
double   fix(double th) {return sign(th + PI) < 0 ? th+2*PI : sign(th - PI) > 0 ? th-2*PI : th;}
double _acos(double th) {return sign(th + 1) <= 0 ?      PI : sign(th - 1) >= 0 ?       0 : acos(th);}
double _asin(double th) {return sign(th + 1) <= 0 ?   -PI/2 : sign(th - 1) >= 0 ?    PI/2 : asin(th);}


struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point  operator -() const {return Point(-x, -y);}
    Point  operator +(const Point  &p) const {return Point(x+p.x, y+p.y);}
    Point  operator -(const Point  &p) const {return Point(x-p.x, y-p.y);}
    Point  operator *(const double &s) const {return Point(x*s, y*s);}
    Point  operator /(const double &s) const {return Point(x/s, y/s);}
    
    double operator ^(const Point  &p) const {return x*p.y - y*p.x;}
    double operator *(const Point  &p) const {return x*p.x + y*p.y;}
    
    // rotate vector (Right/Left hand)
    Point  R(double th) {return Point(x*cos(th)-y*sin(th), x*sin(th)+y*cos(th));}
    Point  L(double th) {return R(2*PI - th);}
    
    double len2()  {return x*x + y*y;}
    double len()   {return sqrt(len2());}
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
    // TODO:
    Line chord(const Circle &c) const {
        Point v = c.o - o;
        double th = _acos((pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len()));
        return Line(v.L(th).e() * r + o, v.R(th).e() * r + o);
    }

    // 两圆相切交点
    // _d = 0 切线不交叉，须满足相交、外切或外离
    // _d = 1 切线交叉，须满足外离
    // 返回圆上逆时针
    // TODO:
    Line tangent_points(const Circle &c, const int &_d) const {
        Point  v = c.o - o;
        double th = _acos((_d&0x1 ? r+c.r : r-c.r) / v.len());
        return Line(v.R(th).e() * r + o, v.L(th).e() * r + o);
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
    void add(Point  st, Point  ed) {add(atan2(st.y, st.x), atan2(ed.y, ed.x));}
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

            // // A more fater version
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

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        int n;
        cin >> n;
        vector<Circle> C(n);
        for (int i = 0; i < n; ++ i)
            C[i].get();

        int ans = a_line_cut_circle(C);

        cout << "Case #" << cas << ": ";
        cout << ans << endl;
    }
    return 0;
}
