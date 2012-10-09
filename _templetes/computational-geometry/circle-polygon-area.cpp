#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

const double PI  = acos(-1.0);
const double TAU = 2 * PI;
const double EPS = 1e-8;

int sig(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template<class T> T pow2(T x) {return x*x;}

struct Vector {
    double x, y;
    Vector() {}
    Vector(double x, double y): x(x), y(y) {}
    Vector operator -(const Vector &v) const {return Vector(x-v.x, y-v.y);}
    Vector operator +(const Vector &v) const {return Vector(x+v.x, y+v.y);}
    Vector operator *(double s) const {return Vector(x*s, y*s);}
    Vector operator /(double s) const {return Vector(x/s, y/s);}
    
    double operator *(const Vector &v) const {return x*v.x + y*v.y;}
    double operator ^(const Vector &v) const {return x*v.y - y*v.x;}
    
    double len2() {return x*x + y*y;}
    double len() {return sqrt(len2());}
    double ang() {return atan2(y, x);}
    Vector e() {return *this / len();}
};

typedef Vector Point;
typedef vector<Point> Polygon;


struct Segment {
    Point a, b;
    Segment() {}
    Segment(Point a, Point b): a(a), b(b) {}
};

typedef Segment Line;

struct Circle {Point o; double r;};


// dot & cross product
double   dot(Point o, Point a, Point b) {return (a-o)*(b-o);}
double cross(Point o, Point a, Point b) {return (a-o)^(b-o);}


// Nearest point in line
Point project(Point p, Line l) {
    Vector vl = l.b - l.a;
    return l.a + vl * ((p - l.a) * vl) / vl.len2();
}


// distance from point to line
double dis_p_li(Point p, Line l) {
    // dis(high) = area / bottom
    return fabs(cross(l.a, l.b, p)) / (l.a - l.b).len();
}
// distance from point to segment
double dis_p_seg(Point p, Segment s) {
    if (dot(s.a, s.b, p) > 0
        && dot(s.b, s.a, p) > 0) return dis_p_li(p, Line(s));
    else
        return min((p - s.a).len(), (p - s.b).len());
}


// The segment which line intersect with circle
// Ensure intersect(Circle c, Line l) is `true'
Segment cross_cir_li(Circle c, Line l) {
    Point p = project(c.o, l);
    Vector v = l.a - l.b;
    v = v.e() * sqrt(pow2(c.r) - (c.o - p).len2());
    return  Segment(p + v, p - v);
}


// signed area of intersection of circle(c.o, c.r) and
//  triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
double fix_acute(double th) {return th<-PI ? th+TAU : th>PI ? th-TAU : th;}
double area_cir_tri(Circle c, Segment s)
{
    double disoa = (c.o - s.a).len(), disob = (c.o - s.b).len();
    
    // sector
    if (sig(dis_p_seg(c.o, s) - c.r) >= 0)
        return fix_acute((s.b - c.o).ang() - (s.a - c.o).ang())
            * pow2(c.r) / 2.0;

    // triangle
    if (sig(disoa - c.r) <= 0 && sig(disob - c.r) <= 0)
        return cross(c.o, s.a, s.b) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    Segment rs = cross_cir_li(c, Line(s));
    return area_cir_tri(c, Segment(s.a, rs.a))
        + area_cir_tri(c, Segment(rs.a, rs.b))
        + area_cir_tri(c, Segment(rs.b, s.b));
}
// area of intersecion of circle(c.o, c.r) and simple polyson(p[])
//  (ccw or cw is ok)
double area_cir_polygon(Circle c, Polygon p)
{
    double res = .0;
    int n = p.size();
    for (int i = 0; i < n; ++ i)
        res += area_cir_tri(c, Segment(p[i], p[(i+1)%n]));
    return fabs(res);
}

int main(int argc, char *argv[])
{
    Circle c;
    c.o.x = c.o.y = .0;
    while (cin >> c.r) {
        int n;
        cin >> n;
        Polygon P(n);
        for (int i = 0; i < n; i++)
            cin >> P[i].x >> P[i].y;
        printf("%.2lf\n", area_cir_polygon(c, P));
    }
    return 0;
}
