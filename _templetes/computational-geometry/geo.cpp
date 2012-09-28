#include <cmath>
#include <cstdio>
#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const double INF = 1e99;


template <class T> int sign(T x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template <class T> T pow2(T x) {return x * x;}

typedef complex<double> Point;
typedef complex<double> Vector;
#define x real()
#define y imag()

double dot(Vector v1, Vector v2) {return v1.x*v2.x + v1.y*v2.y;}
double cross(Vector v1, Vector v2) {return v1.x*v2.y - v1.y*v2.x;}

// vector parallel/perpendicular
bool parallel(Vector v1, Vector v2) {return sign(cross(v1, v2)) == 0;}
bool perpendicular(Vector v1, Vector v2) {return sign(dot(v1, v2)) == 0;}

Vector e(Vector v) {return v/abs(v);}

void test()
{
    Vector v(10.0, 11.0), v1(20.103, 30);
    cout << v << endl;
    cout << arg(v) << endl;
    cout << dot(v, v1) << endl;

    cout << e(v) << endl;
    cout << norm(v) << endl;
    cout << norm(v1) << endl;
    cout << cos(v1) << endl;
}

// class Point {
// public:
//     T x, y;
//     // rotate vector (Right/Left hand)
//     Point<double> R(double co, double si) {return Point(x*co-y*si,  x*si+y*co);}
//     Point<double> L(double co, double si) {return Point(x*co+y*si, -x*si+y*co);}
//     Point<double> R(double th) {return R(cos(th), sin(th));}
//     Point<double> L(double th) {return L(cos(th), sin(th));}

//     double len2()  {return x*x + y*y;}
//     double len()   {return sqrt(len2());} // length of vector
//     double ang()   {return atan2(y, x);}  // angle of vector
//     Point  e()     {return Point(x/len(), y/len());}
//     void   get()   {cin >> x >> y;}
//     void   print() {cout << "Point: (" << x << ", " << y << ")" << endl;}
// };


// struct Line {
//     Point a, b;
//     Line(){} Line(Point _a, Point _b) : a(_a), b(_b) {}

//     bool operator <(const Line &l) const {return (b-a).ang() < (l.b-l.a).ang();}

//     // distance from point to line
//     double dis(Point p) {return fabs(((a-p)^(b-p))) / (b-a).len();}

//     // is point in a line/half line(a to b)/segment
//     bool   line_of(Point p) {return sign((b-a) ^ (p-a)) == 0;}
//     // not include border
//     bool   half_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) > 0;}
//     bool    seg_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) > 0 && sign((a-b)*(p-b)) > 0;}
//     // include border
//     bool half_b_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) >= 0;}
//     bool  seg_b_of(Point p) {return line_of(p) && sign((b-a)*(p-a)) >= 0 && sign((a-b)*(p-b)) >= 0;}

//     // return the relation of the line and two points
//     // -1: points in opposite side of line
//     //  1: points in same side of line
//     //  0: at least one point in line
//     int pos(Point p1, Point p2) {return sign((b-a)^(p1-a)) * sign((b-a)^(p2-a));}
    
//     // whether two line parallel/perpendicular
//     bool is_H(Line l) {return (b-a).is_H(l.b-l.a);}
//     bool is_L(Line l) {return (b-a).is_L(l.b-l.a);}

//     // segment/half line intersect to segment (not border or in line)
//     bool seg_seg(Line s) {return pos(s.a, s.b) < 0 && s.pos(a, b) < 0;}
//     // include intersect in border or in line
//     bool seg_seg_b(Line s) {
//         if (line_of(s.a) && line_of(s.b))
//             return seg_b_of(s.a) || seg_b_of(s.b) || s.seg_b_of(a) || s.seg_b_of(b);
//         return pos(s.a, s.b) <= 0 && s.pos(a, b) <= 0;
//     }

//     // return the intersection point of two line (ensure not rarallel)
//     Point _X_(Line l) {return a + (b-a) * (((a-l.b)^(l.a-l.b))/((a-b)^(l.a-l.b)));}
    
//     // 点在线上映射 (最近点) FIXME: 可能有错
//     Point p_line(Point p) {return _X_(Line(p, p+Point(b.x-a.x, a.y-b.y)));}

//     void get()   {a.get(); b.get();}
//     void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
// };


int main(int argc, char *argv[])
{
    test();
    return 0;
}
