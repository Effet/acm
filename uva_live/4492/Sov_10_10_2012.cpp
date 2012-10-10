#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const double TAU = 2.0 * PI;
const double INF = 1e99;

int sig(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template<class T> T pow2(T x) {return x * x;}


class Vector {
public:
    double x, y;
    Vector() {}
    Vector(double x, double y): x(x), y(y) {}
    
    Vector operator -() const {return Vector(-x, -y);}
    Vector operator +(const Vector &v) const {return Vector(x+v.x, y+v.y);}
    Vector operator -(const Vector &v) const {return Vector(x-v.x, y-v.y);}
    Vector operator *(const double &s) const {return Vector(x * s, y * s);}
    Vector operator /(const double &s) const {return Vector(x / s, y / s);}

    double operator *(const Vector &v) const {return x*v.x + y*v.y;}
    double operator ^(const Vector &v) const {return x*v.y - y*v.x;}

    // rotate vector (Right/Left hand)
    Vector  R(double co, double si) {return Vector(x*co-y*si, y*co+x*si);}
    Vector  L(double co, double si) {return Vector(x*co+y*si, y*co-x*si);}
    Vector  R(double th) {return R(cos(th), sin(th));}
    Vector  L(double th) {return L(cos(th), sin(th));}

    double len2() {return x*x + y*y;}
    double len()  {return sqrt(len2());}
    double ang()  {return atan2(y, x);}  // angle of vector
    Vector e(double s = 1.0) {return *this / len() * s;}
};
typedef Vector Point;


class Line {
public:
    Point a, b;
    Line() {}
    Line(Point a, Point b): a(a), b(b) {}
};

class Circle {
public:
    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r): o(o), r(r) {}
    
    // interior          (d < R - r)         ----> -2
    // interior tangents (d = R - r)         ----> -1
    // concentric        (d = 0)
    // secants           (R - r < d < R + r) ---->  0
    // exterior tangents (d = R + r)         ---->  1
    // exterior          (d > R + r)         ---->  2
    int posi(Circle c) {
        double d = (o - c.o).len();
        int in = sig(d - fabs(r - c.r)), ex = sig(d - (r + c.r));
        return in<0 ? -2 : in==0? -1 : ex==0 ? 1 : ex>0? 2 : 0;
    }

    // IMPORTANT: Ensure this->posi(c) = 0
    // chord(弦) of two circle
    // two points is ccw in *this circle
    Line chord(Circle c) {
        Vector v = c.o - o;
        double co = (pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len());
        double si = sqrt(fabs(1.0 - pow2(co)));
        return Line(v.L(co, si).e(r) + o, v.R(co, si).e(r) + o);
    }
};


// -PI <= th <= PI
struct Range {
    double t;
    int evt;
    Point p;
    Range() {}
    Range(double t, int evt, Point p) : t(t), evt(evt), p(p) {}

    bool operator <(const Range &s) const {
        return sig(t - s.t) < 0 || (sig(t - s.t) == 0 && evt > s.evt);
    }
};


// 圆并返回交了k次的面积
// http://hi.baidu.com/aekdycoin/item/b8ff6adc73c0e71dd78ed0d6
// http://www.zhongsisi.com/solving-simple-polygons/

const int MAX_N = 1000 + 10;
Circle C[MAX_N];
Range R[MAX_N<<1];
double area[MAX_N];
// sort circle with desending of radii
bool cmp_r(const Circle &a, const Circle &b) {
    return a.r > b.r;
}
// Area of circular segment(弓形)
double segment_area(double r, double t) {
    return pow2(r) * (t - sin(t)) / 2;
}
void union_circle(Circle C[], int &n, double *area)
{
    sort(C, C + n, cmp_r);
    // 因为问题只须要将圆并的面积减圆交的面积，因为
    // 因此特殊处理，将重复的圆去掉
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (sig(C[i].r) == 0) break;
        int j = 0;
        for (; j < k; j++)
            if (sig(C[i].r - C[j].r) == 0 && sig((C[i].o - C[j].o).len()) == 0)
                break;
        if (j == k)
            C[k++] = C[i];
    }
    n = k;
    for (int i = 0; i <= n; i++) area[i] = 0;
    for (int i = 0; i < n; i++)
    {
        Point mpi = Point(- C[i].r, 0.0) + C[i].o;
        int nc = 0, rcnt = 0;
        R[rcnt++] = Range(-PI,  1, mpi);
        R[rcnt++] = Range( PI, -1, mpi);
        for (int j = 0; j < n; ++ j)
        {
            if (j == i) continue;

            int pd = C[i].posi(C[j]);
            if (pd == 1 || pd == 2) continue; // 外切或外离
            if (pd == -2 || pd == -1) { // 内含或内切
                if(sig(C[j].r - C[i].r) > 0) nc++;
                continue;
            }

            Line l = C[i].chord(C[j]);
            double jR = (l.a - C[i].o).ang(), jL = (l.b - C[i].o).ang();

            if (sig(jR - jL) > 0) ++ nc;
            R[rcnt++] = Range(jR,  1, l.a);
            R[rcnt++] = Range(jL, -1, l.b);
        }
        sort(R, R + rcnt);

        double pj = - PI;
        Point  pp = mpi;
        for(int j = 0; j < rcnt; ++ j)
        {
            double ts = segment_area(C[i].r, R[j].t - pj) + (pp ^ R[j].p) / 2;
            area[nc  ] += ts;
            area[nc-1] -= ts;
            nc += R[j].evt;
            pj = R[j].t; pp = R[j].p;
        }
    }
}


int main(int argc, char *argv[])
{
    int cas = 1;
    int a[8];
    while (true) {
        int zc = 0;
        for (int i = 0; i < 8; i ++) {
            scanf("%d", &a[i]);
            if (a[i] == 0)
                zc++;
        }
        if (zc == 8)
            break;

        Point p[4];
        for (int i = 0; i <= 3; i++)
            p[i] = Point((double)a[i<<1], (double)a[i<<1|1]);

        Circle c[4];
        int k = 0;
        for (int i = 0; i <= 1; i++)
            for (int j = 2; j <= 3; j++)
                c[k++] = Circle((p[i] + p[j]) / 2, (p[i] - p[j]).len() / 2);

        int n = 4;
        union_circle(c, n, area);

        double ans = 0;
        for (int i = 1; i <= n - 1; i++)
            ans += area[i];

        printf("Case %d: %.3lf\n\n", cas++, ans);
    }
    return 0;
}
