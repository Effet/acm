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
    // void   get()   {cin >> x >> y;}
    void get()     {scanf("%lf%lf", &x, &y);}
    void   print() {cout << "Point: (" << x << ", " << y << ")" << endl;}
};


struct Line {
    Point a, b;
    double t;
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
        Line H;
        H.get();
        H.b = H.a + (H.b - H.a) * BIG;
        
        Point P[3];
        for (int i = 0; i < 3; ++ i)
            P[i].get();
        
        double u;
        cin >> u;
        
        if (sign((P[2]-P[0])^(P[1]-P[0])) > 0)
            swap(P[0], P[1]);
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
                if (H.seg_seg(L[i]) && sign((H.a - L[i].a)^(L[i].b - L[i].a)) > 0)
                {
                    double _dis = L[i].dis(H.a);
                    if (!flag) {dis = _dis; flag = true; l = L[i];}
                    else if (dis > _dis) {dis = _dis; l = L[i];}
                }
            }
            
            if (flag)
            {
                // l.print();
                Point o = H._X_(l), v;
                Point v1 = H.b - H.a, v2 = l.b - l.a;
                double sin_1 = fabs(cos(v2.ang() - v1.ang()));
                double sin_2 = sin_1 / l.t;

                if (sign(v2*v1) > 0)
                    v = Point(-v2.y, v2.x).L(sqrt(1.0-sin_2*sin_2), sin_2);
                else
                    v = Point(-v2.y, v2.x).R(sqrt(1.0-sin_2*sin_2), sin_2);

                H = Line(o, o + v.e() * BIG);
                // H.print();
            }
        }

        Line hoz(Point(-BIG, .0), Point(BIG, .0));
        if (sign(H.a.y) >= 0 && sign(H.b.y - H.a.y) <= 0 && !H.is_H(hoz))
        {
            Point o = H._X_(hoz);
            // cout << o.x << endl;
            printf("%.3lf\n", o.x);
        }
        else
            // cout << "Error" << endl;
            printf("Error\n");
    }
    return 0;
}
