#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);

int sign(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template <class T> T pow2(T x) {return x * x;}

class Point {
public:
    double x, y;
    Point() {}
    Point(double x, double y) : x(x) , y(y) {}

    Point operator - () const {return Point(-x, -y);}
    Point operator +(const Point &p) const {return Point(x + p.x, y + p.y);}
    Point operator -(const Point &p) const {return Point(x - p.x, y - p.y);}
    Point operator *(const double &s) const {return Point(x * s, y * s);}
    Point operator /(const double &s) const {return Point(x / s, y / s);}

    double len2() {return x*x + y*y;}
    double len() {return sqrt(len2());}
    Point e() {return *this / len();}

    Point  R(double co, double si) {return Point(x*co-y*si,  x*si+y*co);}
    Point  L(double co, double si) {return Point(x*co+y*si, -x*si+y*co);}

    void get() {scanf("%lf%lf", &x, &y);}
    void print() {cout << "(" << x << ", " << y << ")"<< endl;}
};
typedef Point Vector;

class Line {
public:
    Point p1, p2;
    Line() {}
    Line(Point a, Point b) : p1(a), p2(b) {}

    void print() {cout << "Line:" << endl; p1.print(); p2.print(); cout << endl;}
};

class Circle {
public:
    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r) : o(o), r(r) {}

    void get() {o.get(); scanf("%lf", &r);}
    void print() {cout << "Circle:" << endl; o.print(); cout << "r:" << r << endl << endl;}
};

double cross(Vector v1, Vector v2) {return v1.x * v2.y - v1.y * v2.x;}
double cross(Point o, Point a, Point b) {return cross(a-o, b-o);}


Line tangent(Circle a, Circle b) {
    Vector v = (b.o - a.o).e();
    
    double _dis = (b.o - a.o).len();
    double co = (a.r - b.r) / _dis;
    double si = sqrt(1.0 - pow2(co));

    // cout << _dis << " " << co << endl;
    // cout << "dr: " << a.r - b.r << endl;
    // (b.o - a.o).print();
    // v.print();

    // cout << "v: ";
    // v.L(co, si).print();
    
    Line li;
    li.p1 =    v.L( co, si) * a.r + a.o;
    li.p2 = (-v).R(-co, si) * b.r + b.o;

    // li.print();
    return li;
}


double dis(Point p, Line l) {
    return fabs(cross(l.p1, l.p2, p)) / (l.p1 - l.p2).len();
}

int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++ cas)
    {
        Circle a, b, c;
        a.get(); b.get(); c.get();
        if (sign(a.o.x - b.o.x) > 0)
            swap(a, b);

        Line l = tangent(a, b);

        // c.o.print();
        // l.print();

        double co = fabs(l.p1.x - l.p2.x) / (l.p1 - l.p2).len();
        double ans = (dis(c.o, l) - c.r) / co;
        c.o.y -= ans;

        // cout << "dis: " << ans << endl;

        int xd = sign(l.p1.y - l.p2.y);
        if (xd == 0)
            ;
        else
        {
            if (xd > 0)
                a = b;
            double dr2 = pow2(c.r - a.r);
            ans += (sqrt((c.o - a.o).len2() - dr2) - sqrt(pow2(c.r + a.r) - dr2)) / (c.r * 2.0 * PI);
        }
        printf("Case %d: %.6lf\n", cas, ans);
    }
    return 0;
}
