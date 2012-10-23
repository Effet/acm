#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cstdio>
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
    double x, y, z;
    Point(){}
    Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    Point  operator -() const {return Point(-x, -y, -z);}
    Point  operator +(const Point  &p) const {return Point(x+p.x, y+p.y, z+p.z);}
    Point  operator -(const Point  &p) const {return Point(x-p.x, y-p.y, z-p.z);}
    Point  operator *(const double &s) const {return Point(x*s, y*s, z*s);}
    Point  operator /(const double &s) const {return Point(x/s, y/s, z/s);}

    Point  operator ^(const Point  &v) const {return Point(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);}
    double operator *(const Point  &v) const {return x*v.x + y*v.y + z*v.z;}

    bool   operator <(const Point  &p) const {
        if (sign(x-p.x) == 0)
            return sign(y-p.y) < 0 || (sign(y-p.y) == 0 && sign(z-p.z) < 0);
        return sign(x-p.x) < 0;
    }

    double len2()  {return x*x + y*y + z*z;}
    double len()   {return sqrt(len2());}
    Point  e()     {return Point(x/len(), y/len(), z/len());}

    bool      parallel(Point v) {return sign((*this^v).len()) == 0;}
    bool perpendicular(Point v) {return sign(*this*v) == 0;}

    void   get()   {cin >> x >> y >> z;}
    void print()   {cout << x << " " << y << " " << z << endl;}
};

struct Line {
    Point a, b;
    Line(){}
    Line(Point _a, Point _b) : a(_a), b(_b) {}

    // 点到直线/直线到直线距离
    double    dis_to_p(Point p) {return ((p-a)^(b-a)).len()/(b-a).len();}
    double dis_to_line(Line  l) {Point n = (b-a)^(l.b-l.a); return fabs((b-a)*n)/n.len();}

    // 保证点不在线上
    bool     same_side(Point p1, Point p2) {return sign(((b-a)^(p1-a)) * ((b-a)^(p2-a))) > 0;}
    bool opposite_side(Point p1, Point p2) {return sign(((b-a)^(p1-a)) * ((b-a)^(p2-a))) < 0;}

    bool      parallel(Line l) {return (b-a).parallel(l.b-l.a);}
    bool perpendicular(Line l) {return (b-a).perpendicular(l.b-l.a);}

    // 直线与直线交点，须先判断共面不平行
    Point intersection(Line l) {return a + (b-a) * (((a-l.a)^(l.a-l.b)).len()/((a-b)^(l.a-l.b)).len());}

    void get() {a.get(); b.get();}
};


struct Plane {
    Point  a, b, c;
    Plane(){}
    Plane(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}

    // 法向量
    Point       normal() {return (b - a) ^ (c - a);}

    double    dis_to_p(Point p) {return fabs(normal()*(p - a)) / normal().len();}
    bool     same_side(Point p1, Point p2) {return sign(normal()*(p1-a) * (normal()*(p2-a))) > 0;}

    // 平面与直线 平行/垂直
    bool      parallel(Line  l) {return sign(normal()*(l.b-l.a)) == 0;}
    bool perpendicular(Line  l) {return sign((normal()^(l.b-l.a)).len()) == 0;}

    // 平面与平面 平行/垂直
    bool      parallel(Plane p) {return normal().parallel(p.normal());}
    bool perpendicular(Plane p) {return normal().perpendicular(p.normal());}

    // 须先判断不平行
    Point intersection(Line  l) {return l.a + (l.b-l.a) * (((normal()*(a-l.a)))/((normal()*(l.b-l.a))));}
    Line  intersection(Plane p) {
        return Line(parallel(Line(p.a,p.b)) ? intersection(Line(p.b,p.c)) : intersection(Line(p.a,p.b)),
                    parallel(Line(p.c,p.a)) ? intersection(Line(p.b,p.c)) : intersection(Line(p.c,p.a)));
    }
};


const int MAX_L = 4; // 3D

struct Matrix {
    int n, m;
    double mat[MAX_L][MAX_L];
    Matrix(){}
    Matrix(int _n, int _m, ...) : n(_n), m(_m) {
        va_list ap;
        va_start(ap, _m);
        for (int i = 0; i < _n; ++ i)
            for (int j = 0; j < _m; ++ j)
                mat[i][j] = va_arg(ap, double);
        va_end(ap);
    }
    Matrix operator *(const Matrix &b) const {
        Matrix r;
        r.n = n; r.m = b.m;
        memset(r.mat, 0, sizeof(r.mat));
        for (int i = 0; i < r.n; ++ i)
            for (int j = 0; j < r.m; ++ j)
                for (int k = 0; k < m; ++ k)
                    r.mat[i][j] += mat[i][k] * b.mat[k][j];
        return r;
    }
    void print() {
        cout << n << " " << m << endl;
        for (int i = 0; i < n; ++ i)
        {
            for (int j = 0; j < m; ++ j)
                cout << mat[i][j] << " ";
            cout << endl;
        }
    }
};

// 平移变换
Matrix Trs(double tx, double ty, double tz) {
    return Matrix(4, 4
                  , 1.0,  .0,  .0,  tx
                  ,  .0, 1.0,  .0,  ty
                  ,  .0,  .0, 1.0,  tz
                  ,  .0,  .0,  .0, 1.0);
}

// 缩放变换
Matrix Sca(double sx, double sy, double sz) {
    return Matrix(4, 4
                  , sx,  .0,  .0,  .0
                  , .0,  sy,  .0,  .0
                  , .0,  .0,  sz,  .0
                  , .0,  .0,  .0, 1.0);
}

// 旋转变换
Matrix R_x(double _cos, double _sin) {
    return Matrix(4, 4
                  , 1.0,   .0,    .0,  .0
                  ,  .0, _cos, -_sin,  .0
                  ,  .0, _sin,  _cos,  .0
                  ,  .0,   .0,    .0, 1.0);
}
Matrix R_y(double _cos, double _sin) {
    return Matrix(4, 4
                  ,  _cos,  .0, _sin,  .0
                  ,    .0, 1.0,   .0,  .0
                  , -_sin,  .0, _cos,  .0
                  ,    .0,  .0,   .0, 1.0);
}
Matrix R_z(double _cos, double _sin) {
    return Matrix(4, 4
                  , _cos, -_sin,  .0,  .0
                  , _sin,  _cos,  .0,  .0
                  ,   .0,    .0, 1.0,  .0
                  ,   .0,    .0,  .0, 1.0);
}
Matrix R_x(double th) {return R_x(cos(th), sin(th));}
Matrix R_y(double th) {return R_y(cos(th), sin(th));}
Matrix R_z(double th) {return R_z(cos(th), sin(th));}


// 将向量旋转至Z轴的``旋转矩阵''，先判断向量是否已经是Z轴方向且向量不为点
// 先将向量绕Z轴旋转至XOZ平面，再绕Y轴旋转至Z轴
Matrix Rtoz(Point v) {
    double len = sqrt(pow2(v.x) + pow2(v.y));
    return R_y(v.z/v.len(), -len/v.len()) * R_z(v.x/len, -v.y/len);
}
