#include <set>
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
    int evt, id;
    Range() {}
    Range(double t, int evt, int id) : t(t), evt(evt), id(id) {}

    bool operator <(const Range &s) const {
        return sig(t - s.t) < 0 || (sig(t - s.t) == 0 && evt > s.evt);
    }
};


// 圆并返回交了k次的面积
// http://hi.baidu.com/aekdycoin/item/b8ff6adc73c0e71dd78ed0d6
// http://www.zhongsisi.com/solving-simple-polygons/

const int MAX_N = 1100 + 10;
Circle C[MAX_N];
Range R[MAX_N<<1];
int mx;
set<set<int> > st;
// sort circle with desending of radii
bool cmp_r(const Circle &a, const Circle &b) {
    return a.r > b.r;
}
// Area of circular segment(弓形)
double segment_area(double r, double t) {
    return pow2(r) * (t - sin(t)) / 2;
}
void union_circle(Circle C[], int &n)
{
    sort(C, C + n, cmp_r);
    
    mx = -1; st.clear();
    for (int i = 0; i < n; i++)
    {
        int nc = 0, rcnt = 0;
        set<int> tst;
        tst.insert(i);
        for (int j = 0; j < n; ++ j)
        {
            if (j == i) continue;

            int pd = C[i].posi(C[j]);
            if (pd == 1 || pd == 2) // 外切或外离
            {
                if (pd == 1) {
                    double ag = (C[j].o - C[i].o).ang();
                    R[rcnt++] = Range(ag,  1, j);
                    R[rcnt++] = Range(ag, -1, j);
                }
                continue;
            }
            if (pd == -2 || pd == -1) { // 内含或内切
                if (j > i) {
                    R[rcnt++] = Range(-PI,  1, j);
                    R[rcnt++] = Range( PI, -1, j);
                }
                continue;
            }

            Line l = C[i].chord(C[j]);
            double jR = (l.a - C[i].o).ang(), jL = (l.b - C[i].o).ang();

            if (sig(jR - jL) > 0) {
                R[rcnt++] = Range(-PI,  1, j);
                R[rcnt++] = Range( PI, -1, j);
            }
            
            R[rcnt++] = Range(jR,  1, j);
            R[rcnt++] = Range(jL, -1, j);
        }
        sort(R, R + rcnt);

        double pj = - PI;
        for(int j = 0; j < rcnt; ++ j)
        {
            if (nc > mx) {
                mx = nc; st.clear();
            }
            
            if (nc == mx)
                st.insert(tst);
            
            nc += R[j].evt;
            pj = R[j].t;
            if (R[j].evt == 1)
                tst.insert(R[j].id);
            else
                tst.erase(R[j].id);
        }
    }
}


int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        double r;
        int n;
        scanf("%lf%d", &r, &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &C[i].o.x, &C[i].o.y);
            C[i].r = r;
        }
        
        union_circle(C, n);

        printf("%d %d\n", mx + 1, (int)st.size());
    }
    printf("\n"); // very very very big trick!!!
    return 0;
}
