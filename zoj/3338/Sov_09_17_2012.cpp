#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdarg>
using namespace std;

const int MAX_L = 3;

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
};

struct Point {
    double x, y;
    Point(){}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator -(const Point &p) const {return Point(x-p.x, y-p.y);}
    double len2() {return x*x + y*y;}
    double len()  {return sqrt(len2());}
    double arg()  {return atan2(y, x);}
    void   get()  {cin >> x >> y;}
};


int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        Point p1[4], p2[4];
        p1[2].get();
        p1[0] = Point(0, 0);
        p1[1] = Point(p1[2].x, 0);
        p1[3] = Point(0, p1[2].y);
        for (int i = 0; i < 4; ++ i) p2[i].get();

        double sx = (p2[1] - p2[0]).len() / (p1[1] - p1[0]).len();
        double sy = (p2[3] - p2[0]).len() / (p1[3] - p1[0]).len();

        double th = (p2[1] - p2[0]).arg();

        double tx = p2[0].x - p1[0].x;
        double ty = p2[0].y - p1[0].y;
        
        // 缩放变换
        Matrix TrSca(3, 3
                     , sx, 0.0, 0.0
                     ,0.0,  sy, 0.0
                     ,0.0, 0.0, 1.0);

        // cout << sx << " " << sy << endl;
        // TrSca.print();

        // 旋转变换
        Matrix TrRot(3, 3
                     ,cos(th), -sin(th), 0.0
                     ,sin(th),  cos(th), 0.0
                     ,    0.0,      0.0, 1.0);
        // 平移变换
        Matrix TrTra(3, 3
                     ,1.0, 0.0, tx
                     ,0.0, 1.0, ty
                     ,0.0, 0.0, 1.0);

        // 复合
        Matrix Tr = TrTra*TrRot*TrSca;

        double a, b, c, a1, b1, c1;
        a = Tr.mat[0][0] - 1; b = Tr.mat[0][1]; c = Tr.mat[0][2];
        a1 = Tr.mat[1][0]; b1 = Tr.mat[1][1] - 1; c1 = Tr.mat[1][2];

        double x = (c1*b - c*b1) / (a*b1 - a1*b);
        double y = (c1*a - c*a1) / (b*a1 - b1*a);

        printf("%.2lf %.2lf\n", x, y);
    }
    return 0;
}
