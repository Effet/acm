#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cstdio>
using namespace std;

typedef double DB;

const DB EPS = 1e-8, PI = acos(-1.0), TAU = 2*PI, INF = 1e99;

int sig(DB x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template<class T> T pow2(T x) {return x * x;}

struct PT {
    DB x, y, z;
    PT(DB x=0, DB y=0, DB z=0) : x(x), y(y), z(z) {}

    PT operator -() {return PT(-x, -y, -z);}
    PT operator +(PT p) {return PT(x+p.x, y+p.y, z+p.z);}
    PT operator -(PT p) {return PT(x-p.x, y-p.y, z-p.z);}
    PT operator *(DB s) {return PT(x*s, y*s, z*s);}
    PT operator /(DB s) {return PT(x/s, y/s, z/s);}

    PT operator ^(PT v) {return PT(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);}
    DB operator *(PT v) {return x*v.x + y*v.y + z*v.z;}

    bool operator <(const PT  &p) const {
        if (sig(x-p.x) == 0)
            return !sig(y-p.y) ? z<p.z : y<p.y;
        return sig(x-p.x) < 0;
    }

    DB len2() {return x*x + y*y + z*z;}
    DB len() {return sqrt(len2());}
    PT e() {return *this / len();}

    bool      parallel(PT v) {return sig((*this^v).len()) == 0;}
    bool perpendicular(PT v) {return sig(*this*v) == 0;}

    void   get()   {cin >> x >> y >> z;}
    void print()   {cout << x << " " << y << " " << z << endl;}
};

struct LI {
    PT a, b;
    LI(){}
    LI(PT a, PT b) : a(a), b(b) {}

    // 点到直线/直线到直线距离
    DB    dis_to_p(PT p) {return ((p-a)^(b-a)).len()/(b-a).len();}
    DB dis_to_line(LI  l) {PT n = (b-a)^(l.b-l.a); return fabs((b-a)*n)/n.len();}

    // 保证点不在线上
    bool     same_side(PT p1, PT p2) {return sig(((b-a)^(p1-a)) * ((b-a)^(p2-a))) > 0;}
    bool opposite_side(PT p1, PT p2) {return sig(((b-a)^(p1-a)) * ((b-a)^(p2-a))) < 0;}

    bool      parallel(LI l) {return (b-a).parallel(l.b-l.a);}
    bool perpendicular(LI l) {return (b-a).perpendicular(l.b-l.a);}

    // 直线与直线交点，须先判断共面不平行
    PT intersection(LI l) {return a + (b-a) * (((a-l.a)^(l.a-l.b)).len()/((a-b)^(l.a-l.b)).len());}

    void get() {a.get(); b.get();}
};


struct PL {
    PT  a, b, c;
    PL(){}
    PL(PT a, PT b, PT c) : a(a), b(b), c(c) {}

    // 法向量
    PT normal() {return (b - a) ^ (c - a);}

    DB    dis_to_p(PT p) {return fabs(normal()*(p - a)) / normal().len();}
    bool     same_side(PT p1, PT p2) {return sig(normal()*(p1-a) * (normal()*(p2-a))) > 0;}

    // 平面与直线 平行/垂直
    bool      parallel(LI  l) {return sig(normal()*(l.b-l.a)) == 0;}
    bool perpendicular(LI  l) {return sig((normal()^(l.b-l.a)).len()) == 0;}

    // 平面与平面 平行/垂直
    bool      parallel(PL p) {return normal().parallel(p.normal());}
    bool perpendicular(PL p) {return normal().perpendicular(p.normal());}

    // 须先判断不平行
    PT intersection(LI  l) {return l.a + (l.b-l.a) * (((normal()*(a-l.a)))/((normal()*(l.b-l.a))));}
    LI  intersection(PL p) {
        return LI(parallel(LI(p.a,p.b)) ? intersection(LI(p.b,p.c)) : intersection(LI(p.a,p.b)),
                    parallel(LI(p.c,p.a)) ? intersection(LI(p.b,p.c)) : intersection(LI(p.c,p.a)));
    }
};


const int MAX_L = 4; // 3D

struct Matrix {
    int n, m;
    DB mat[MAX_L][MAX_L];
    Matrix(){}
    Matrix(int _n, int _m, ...) : n(_n), m(_m) {
        va_list ap;
        va_start(ap, _m);
        for (int i = 0; i < _n; ++ i)
            for (int j = 0; j < _m; ++ j)
                mat[i][j] = va_arg(ap, DB);
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
Matrix Trs(DB tx, DB ty, DB tz) {
    return Matrix(4, 4
                  , 1.0,  .0,  .0,  tx
                  ,  .0, 1.0,  .0,  ty
                  ,  .0,  .0, 1.0,  tz
                  ,  .0,  .0,  .0, 1.0);
}

// 缩放变换
Matrix Sca(DB sx, DB sy, DB sz) {
    return Matrix(4, 4
                  , sx,  .0,  .0,  .0
                  , .0,  sy,  .0,  .0
                  , .0,  .0,  sz,  .0
                  , .0,  .0,  .0, 1.0);
}

// 旋转变换
Matrix R_x(DB _cos, DB _sin) {
    return Matrix(4, 4
                  , 1.0,   .0,    .0,  .0
                  ,  .0, _cos, -_sin,  .0
                  ,  .0, _sin,  _cos,  .0
                  ,  .0,   .0,    .0, 1.0);
}
Matrix R_y(DB _cos, DB _sin) {
    return Matrix(4, 4
                  ,  _cos,  .0, _sin,  .0
                  ,    .0, 1.0,   .0,  .0
                  , -_sin,  .0, _cos,  .0
                  ,    .0,  .0,   .0, 1.0);
}
Matrix R_z(DB _cos, DB _sin) {
    return Matrix(4, 4
                  , _cos, -_sin,  .0,  .0
                  , _sin,  _cos,  .0,  .0
                  ,   .0,    .0, 1.0,  .0
                  ,   .0,    .0,  .0, 1.0);
}
Matrix R_x(DB th) {return R_x(cos(th), sin(th));}
Matrix R_y(DB th) {return R_y(cos(th), sin(th));}
Matrix R_z(DB th) {return R_z(cos(th), sin(th));}


// 将向量旋转至Z轴的``旋转矩阵''，先判断向量是否已经是Z轴方向且向量不为点
// 先将向量绕Z轴旋转至XOZ平面，再绕Y轴旋转至Z轴
Matrix Rtoz(PT v) {
    DB len = sqrt(pow2(v.x) + pow2(v.y));
    return R_y(v.z/v.len(), -len/v.len()) * R_z(v.x/len, -v.y/len);
}

int main(int argc, char *argv[])
{
    
    return 0;
}


// ///////////////////////////////////////////////////////////////////////////
// Sphere Section
// ///////////////////////////////////////////////////////////////////////////

DB sphere_dist(DB R, DB lng1, DB lat1, DB lng2, DB lat2) {
    lng1 = lng1 * PI / 180;
    lat1 = lat1 * PI / 180;
    lng2 = lng2 * PI / 180;
    lat2 = lat2 * PI / 180;
    DB dlon = lng2 - lng1;
    DB dlat = lat2 - lat1;
    DB a = pow2(sin(dlat/2)) + cos(lat1) * cost(lat2) * pow2(sin(dlon/2));
    DB c = 2 * atan2(sqrt(a), sqrt(1-a));
    DB d = R * c;
    return d;
}
