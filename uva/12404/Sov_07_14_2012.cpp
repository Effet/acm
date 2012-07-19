#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define eps 0.000001
#define pow2(x) ((x)*(x))

struct point {
    double x, y;
};

// //矢量V以P为顶点逆时针旋转angle并放大scale倍
// point rotate(point v,point p,double angle,double scale){
// 	point ret=p;
// 	v.x-=p.x,v.y-=p.y;
// 	p.x=scale*cos(angle);
// 	p.y=scale*sin(angle);
// 	ret.x+=v.x*p.x-v.y*p.y;
// 	ret.y+=v.x*p.y+v.y*p.x;
// 	return ret;
// }

point rotate2(point v,point p,double dx, double dy, double a){
	point ret=p;
	v.x-=p.x,v.y-=p.y;
	p.x=dx/a;
	p.y=dy/a;
	ret.x+=v.x*p.x-v.y*p.y;
	ret.y+=v.x*p.y+v.y*p.x;
	return ret;
}

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        point A, B, C, D;
        double a, b, c, d;

        cin >> A.x >> A.y >> B.x >> B.y >> b >> c >> d;
        a = sqrt(pow2(A.x-B.x) + pow2(A.y-B.y));

        double bb = pow2(b), dd = pow2(d);
        double k = pow2(a - c) - bb - dd;
        double x = (4*bb*dd - pow2(k)) / (4*(k+bb+dd));
        double h = sqrt(x);

        // cout << h << endl;
        
        double xd = sqrt(dd - x);
        double xb = sqrt(bb - x);

        // cout << xd << " " << xb << endl;
        // cout << " a = " << a << endl;

        if ( abs(xd + xb + c - a) < eps )
        {
            D.x = xd; D.y = h;
            C.x = a - xb; C.y = h;
        }
        else if ( abs(xd - xb + c - a) < eps )
        {
            D.x = xd; D.y = h;
            C.x = a + xb; C.y = h;
        }
        else
        {
            D.x = - xd; D.y = h;
            C.x = a - xb; C.y = h;
        }

        
        // printf("%.8lf %.8lf %.8lf %.8lf\n", C.x, C.y, D.x, D.y);
        
        C.x += A.x; C.y += A.y;
        D.x += A.x; D.y += A.y;

        double dx = B.x - A.x;
        double dy = B.y - A.y;

        // double theta = acos(dx/a);

        // C = rotate(C, A, theta, 1);
        // D = rotate(D, A, theta, 1);
        C = rotate2(C, A, dx, dy, a);
        D = rotate2(D, A, dx, dy, a);

        printf("Case %d:\n", cas);
        printf("%.8lf %.8lf %.8lf %.8lf\n", C.x, C.y, D.x, D.y);
    }
    return 0;
}
