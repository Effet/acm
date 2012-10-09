#include <vector>
#include <complex>
#include <iostream>
#include <cstdio>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const double TAU = 2.0 * PI;
const double INF = 1e99;

double pow2(double x) {return x * x;}
int sig(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}


class Vector {
public:
    double x, y;
    Vector() {}
    Vector(double x, double y) : x(x), y(y) {}
    
    Vector operator -() const {return Vector(-x, -y);}
    Vector operator +(const Vector &v) const {return Vector(x+v.x, y+v.y);}
    Vector operator -(const Vector &v) const {return Vector(x-v.x, y-v.y);}
    Vector operator *(const double &s) const {return Vector(x * s, y * s);}
    Vector operator /(const double &s) const {return Vector(x / s, y / s);}

    // rotate vector (Right/Left hand)
    Vector  R(double co, double si) {return Vector(x*co-y*si,  x*si+y*co);}
    Vector  L(double co, double si) {return Vector(x*co+y*si, -x*si+y*co);}
    Vector  R(double th) {return R(cos(th), sin(th));}
    Vector  L(double th) {return L(cos(th), sin(th));}

    double len2() {return x * x + y * y;}
    double len()  {return sqrt(len2());}
    double ang()  {return atan2(y, x);}  // angle of vector
    Vector e()    {return *this / len();}
};

typedef Vector Point;
typedef vector<Point> Polygon;


class Segment {
public:
    Point a, b;
    Segment() {}
    Segment(const Segment &s) {a = s.a; b = s.b;}
    Segment(Point a, Point b) : a(a), b(b) {}
};


class Line : public Segment {
public:
    double A, B, C;
    Line() {}
    Line(Segment s) : Segment(s) {init_1();}
    Line(Point a, Point b) : Segment(a, b) {init_1();}
    Line(double A, double B, double C) {init_2();}

    void init_1() {}
    void init_2() {}
};

class Circle {
public:
    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r) : o(o), r(r) {}
};

// cin >> obj
istream& operator >>(istream &is, Vector  &p) {is >> p.x >> p.y; return is;}
istream& operator >>(istream &is, Segment &s) {is >> s.a >> s.b; return is;}
istream& operator >>(istream &is, Circle  &c) {is >> c.o >> c.r; return is;}
// cout << obj
ostream& operator <<(ostream &os, Vector  &p) {os << "(" << p.x << ","  << p.y << ")"; return os;}
ostream& operator <<(ostream &os, Segment &s) {os << "[" << s.a << ", " << s.b << "]"; return os;}
ostream& operator <<(ostream &os, Circle  &c) {os << "{" << c.o << ", " << c.r << "}"; return os;}


double dis(Point, Point);
double dis(Point, Line);
double dis(Point, Segment);
double dis(Line, Line);
double dis(Segment, Segment);

bool intersect(Point, Line);
bool intersect(Point, Segment, bool);
bool intersect(Segment, Line, bool);
bool intersect(Segment, Segment, bool);
bool intersect(Circle, Line, bool);
bool intersect(Circle, Segment, bool);

Point   intersection(Line, Line);
Segment intersection(Circle, Line);
double  intersection(Circle, Segment);
double  intersection(Circle, Polygon);

// dot & cross product
double   dot(Vector v1, Vector v2) {return v1.x * v2.x + v1.y * v2.y;}
double cross(Vector v1, Vector v2) {return v1.x * v2.y - v1.y * v2.x;}
double   dot(Point o, Point a, Point b) {return dot(a-o, b-o);}
double cross(Point o, Point a, Point b) {return cross(a-o, b-o);}


// relationships
bool parallel(Line l1, Line l2) {return sig(cross(l1.a-l1.b, l2.a-l2.b)) == 0;}
bool perpendicular(Line l1, Line l2) {return sig(dot(l1.a-l1.b, l2.a-l2.b)) == 0;}
// int pos(Point p1, Point p2, Line l)


// {{{ vector translation

// // If Vector is complex number.
// Vector rotate(Vector v, double co, double si) {return v * Vector(co, si);}
// Vector rotate(Vector v, double th) {return v * polar(1.0, th);}
// Point rotate(Point o, Point a, double co, double si) {return o + rotate(a-o, co, si);}
// Point rotate(Point o, Point a, double th) {return o + rotate(a-o, th);}

// Nearest point in line
Point project(Point p, Line l) {
    Vector vl = l.b - l.a;
    return l.a + vl * dot(p - l.a, vl) / vl.len2();
}
Point project_2(Point p, Line l) {
    Vector vl = l.a - l.b;
    vl = Vector(vl.y, - vl.x);  // perpendicular vector
    return intersection(Line(p, p + vl), l);
}

// Mirorr point of line
Point reflect(Point p, Line l) {
    Vector vp = p - l.a, vl = l.b - l.a;
    return p + (vl * dot(vp, vl) / vl.len2() - vp) * 2.0;
}

// }}}


// {{{ Distance

double dis(Point a, Point b) {return (a - b).len();}
double dis(Point p, Line l) {return fabs(cross(l.a, l.b, p)) / dis(l.a, l.b);}
double dis(Point p, Segment s) {
    if (dot(s.a, s.b, p) > .0
        && dot(s.b, s.a, p) > .0) return dis(p, Line(s));
    else
        return min(dis(p, s.a), dis(p, s.b));
}
double dis(Line l1, Line l2) {return !parallel(l1, l2) ? .0 : dis(l1.a, l2);}
double dis(Segment s1, Segment s2) {
    if (intersect(s1, s2, true)) return .0;
    return min(
        min(dis(s1.a, s2), // dis(Point, Segment)
            dis(s1.b, s2)),
        min(dis(s2.a, s1),
            dis(s2.b, s1))
        );
}

// }}}

// {{{ Intersect

// is intersect (x < -1 means x <= 0)
bool intersect(Point p, Line l) {return sig(cross(p, l.a, l.b)) == 0;}
bool intersect(Point p, Segment s, bool border = false) {
    return sig(cross(p, s.a, s.b)) == 0 // inline
        && sig(dot(s.a, s.b, p)) > (border?-1:0) // right of p1
        && sig(dot(s.b, s.a, p)) > (border?-1:0); // left of p2
}
bool intersect(Segment s, Line l, bool border = false) {
    return sig(cross(l.a, l.b, s.a)
                * cross(l.a, l.b, s.b)) > (border?-1:0);
}
bool intersect(Segment s1, Segment s2, bool border = false) {
    if (border && parallel(s1, s2)) // inline
        return intersect(s1.a, s2, true)
            || intersect(s1.b, s2, true) // intersect(Point, Segment)
            || intersect(s2.a, s1, true)
            || intersect(s2.b, s1, true);
    
    return intersect(s1, Line(s2), border) &&
        intersect(s2, Line(s1), border); // intersect(Segment, Line)
}
bool intersect(Circle c, Line l, bool border = false) {
    return sig(dis(c.o, l) - c.r) < (border?-1:0);
}
bool intersect(Circle c, Segment s, bool border = true) {
    int d1 = sig(dis(c.o, s.a) - c.r), d2 = sig(dis(c.o, s.b) - c.r);
    if (d1 <= 0 && d2 <= 0)
        return border && (d1 == 0 || d2 == 0);
    return sig(dis(c.o, s) - c.r) < (border?-1:0);
}

// }}}

// {{{ Intersection

// intersection point
Point intersection(Line l1, Line l2) { // ensure not rarallel
    return l1.a +
        (l1.b-l1.a) * (cross(l1.a-l2.b, l2.a-l2.b) /
                       cross(l1.a-l1.b, l2.a-l2.b));
}
// The segment which line intersect with circle
// Ensure intersect(Circle c, Line l) is `true'
Segment intersection(Circle c, Line l) {
    Point p = project(c.o, l);
    Vector v = l.a - l.b;
    v = v.e() * sqrt(pow2(c.r) - pow2(dis(c.o, p)));
    return  Segment(p + v, p - v);
}
// signed area of intersection of circle(c.o, c.r) and
//  triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
double fix_acute(double th) {return th<-PI ? th+TAU : th>PI ? th-TAU : th;}
double intersection(Circle c, Segment s)
{
    double disoa = dis(c.o, s.a), disob = dis(c.o, s.b);
    
    // sector
    if (sig(dis(c.o, s) - c.r) >= 0)
        return fix_acute((s.b - c.o).ang() - (s.a - c.o).ang())
            * pow2(c.r) / 2.0;

    // triangle
    if (sig(disoa - c.r) <= 0 && sig(disob - c.r) <= 0)
        return cross(c.o, s.a, s.b) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    Segment rs = intersection(c, Line(s));
    return intersection(c, Segment(s.a, rs.a))
        + intersection(c, Segment(rs.a, rs.b))
        + intersection(c, Segment(rs.b, s.b));
}
// area of intersecion of circle(c.o, c.r) and simple polyson(p[])
//  (ccw or cw is ok)
double intersection(Circle c, Polygon p)
{
    double res = .0;
    int n = p.size();
    for (int i = 0; i < n; ++ i)
        res += intersection(c, Segment(p[i], p[(i+1)%n]));
    return fabs(res);
}

// }}}



int main(int argc, char *argv[])
{
    Circle c;
    double v0, th, t, g, R;
    while (cin >> c.o >> v0 >> th >> t >> g >> R) {
        th = th / 360 * TAU;
        if (!sig(c.o.x) && !sig(c.o.y)
            && !sig(v0) && !sig(th) && !sig(t) && !sig(g) && !sig(R))
            break;
        
        c.o = c.o + Vector(v0*cos(th)*t, v0*sin(th)*t - g*t*t/2.0);
        c.r = R;
        int n;
        cin >> n;
        Polygon p(n);
        for (int i = 0; i < n; ++ i)
            cin >> p[i];
        double ans = intersection(c, p);
        printf("%.2lf\n", ans);
    }
    return 0;
}
