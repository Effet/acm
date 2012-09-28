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

    // 向量平行/垂直
    bool      parallel(Point v) {return sign(*this^v) == 0;}
    bool perpendicular(Point v) {return sign(*this*v) == 0;}

    // rotate vector (Right/Left hand)
    Point  R(double _cos, double _sin) {return Point(x*_cos-y*_sin, x*_sin+y*_cos);}
    Point  L(double _cos, double _sin) {return Point(x*_cos+y*_sin, -x*_sin+y*_cos);}

    Point  R(double th) {return Point(x*cos(th)-y*sin(th), x*sin(th)+y*cos(th));}
    Point  L(double th) {return R(2*PI - th);}
    // Point  L(double th) {return Point(x*cos(th)+y*sin(th), -x*sin(th)+y*cos(th));}

    double len2()  {return x*x + y*y;}
    double len()   {return sqrt(len2());}
    double ang()   {return atan2(y, x);}
    Point  e()     {return Point(x/len(), y/len());}
    void   get()   {cin >> x >> y;}
    void   print() {cout << "Point: (" << x << ", " << y << ")" << endl;}
};


struct Line {
    Point a, b;
    double t;
    Line(){} Line(Point a, Point b) : a(a), b(b) {}

    bool operator <(const Line &l) const {return (b-a).ang() < (l.b-l.a).ang();}

    // 判点在直线/射线(a到b)/线段上
    bool p_in_line(Point p) {return sign((b-a) ^ (p-a)) == 0;}
    // 包括端点
    bool p_in_half_in(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) >= 0;}
    bool p_in_seg_in(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) >= 0 && sign((a-b)*(p-b)) >= 0;}
    // 不包括
    bool p_in_half(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) > 0;}
    bool p_in_seg(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) > 0 && sign((a-b)*(p-b)) > 0;}

    // 判两点在直线同侧/异侧 (点不在线上)
    bool     same_side(Point p1, Point p2) {return sign((b-a)^(p1-a)) * sign((b-a)^(p2-a)) > 0;}
    bool opposite_side(Point p1, Point p2) {return sign((b-a)^(p1-a)) * sign((b-a)^(p2-a)) < 0;}
    
    // 直线平行/垂直
    bool      parallel(Line l) {return (b-a).parallel(l.b-l.a);}
    bool perpendicular(Line l) {return (b-a).perpendicular(l.b-l.a);}

    // 线段/射线与线段相交 (不包括端点和部分重合)
    bool  seg_seg_intersect(Line s) {return opposite_side(s.a, s.b) && s.opposite_side(a, b);}
    // 包括端点和部分重合
    bool seg_seg_intersect_in(Line s) {
        if (p_in_line(s.a) && p_in_line(s.b))
            return p_in_seg_in(s.a) || p_in_seg_in(s.b) || s.p_in_seg_in(a) || s.p_in_seg_in(b);
        return !same_side(s.a, s.b) && !s.same_side(a, b);
    }

    // 两直线交点 (保证不平行)
    Point intersection(Line l) {return a + (b-a) * (((a-l.b)^(l.a-l.b))/((a-b)^(l.a-l.b)));}
    
    // 点在线上映射 (最近点) FIXME: 可能有错
    Point p_line(Point p) {return intersection(Line(p, p+Point(b.x-a.x, a.y-b.y)));}
    // 点到直线距离
    double p_dist(Point p) {return fabs((a-p)^(b-p)) / (b-a).len();}

    void get() {a.get(); b.get();}
    void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
};

const double BIG = 1000000000.0;

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        Line H; H.get(); H.b = H.a + (H.b - H.a) * BIG;
        Point P[3];
        for (int i = 0; i < 3; ++ i) P[i].get();
        double u; cin >> u;
        
        if (sign((P[2]-P[0])^(P[1]-P[0])) > 0) swap(P[0], P[1]);
        Line L[6];
        for (int i = 0; i < 3; ++ i)
        {
            L[i] = Line(P[i], P[(i+1)%3]); L[i].t = u;
            L[i+3] = Line(P[(i+1)%3], P[i]); L[i+3].t = 1.0/u;
        }

        for (int k = 0; k < 3; ++ k)
        {
            bool flag = false;
            double dis;
            Line l;
            for (int i = 0; i < 6; ++ i)
            {
                if (H.seg_seg_intersect(L[i]) && sign((H.a - L[i].a)^(L[i].b - L[i].a)) > 0)
                {
                    double _dis = L[i].p_dist(H.a);
                    if (!flag) {dis = _dis; flag = true; l = L[i];}
                    else if (dis > _dis) {dis = _dis; l = L[i];}
                }
            }
            
            if (flag)
            {
                // l.print();
                Point o = H.intersection(l), v;
                Point v1 = H.b - H.a, v2 = l.b - l.a;
                double sin_1 = fabs(cos(v2.ang() - v1.ang()));
                double sin_2 = sin_1 / l.t;

                if (sign(v2*v1) > 0)
                {
                    v = Point(-v2.y, v2.x).L(sqrt(1.0-sin_2*sin_2), sin_2);
                }
                else
                {
                    // Point  R(double th) {return Point(x*cos(th)-y*sin(th), x*sin(th)+y*cos(th));}
                    v = Point(-v2.y, v2.x).R(sqrt(1.0-sin_2*sin_2), sin_2);
                }

                // double dt = asin(sin_2) - asin(sin_1);

                // if (sign(v2*v1) > 0)
                // {
                //     v = v1.R(dt);
                //     cout << "R: " << dt << endl;
                // }
                // else
                // {
                //     v = v1.L(dt);
                //     cout << "L: " << dt << endl;
                // }

                H = Line(o, o + v.e() * BIG);
                // // H.print();
            }
        }

        // H.print();
        Line hoz(Point(-BIG, .0), Point(BIG, .0));
        if (sign(H.a.y) >= 0 && sign(H.b.y - H.a.y) <= 0 && !H.parallel(hoz))
        {
            Point o = H.intersection(hoz);
            // cout << o.x << endl;
            printf("%.3lf\n", o.x);
        }
        else
            // cout << "Error" << endl;
            printf("Error\n");
    }
    return 0;
}
