#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef double DB;

struct PT {
    DB x, y;
    PT(DB x=0, DB y=0): x(x), y(y) {}
    PT operator -(PT p) {return PT(x-p.x, y-p.y);}
    PT operator +(PT p) {return PT(x+p.x, y+p.y);}
    PT operator *(DB s) {return PT(x*s, y*s);}
    PT operator /(DB s) {return PT(x/s, y/s);}
    DB len() {return sqrt(x*x + y*y);}
};

DB all_dis(PT *p, int n, PT f) {
    DB r = 0;
    for (int i = 0; i < n; i++)
        r += (f-p[i]).len();
    return r;
}

PT fermat_point(PT *p, int n) {
	PT f(0,0), t;
    DB step = 0;
    for (int i = 0; i < n; i++)
        step+=fabs(p[i].x)+fabs(p[i].y), f=f+p[i];
    f = f/n;
	while (step > 1e-10) {
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                PT t = f + PT(i,j)*step;
                if (all_dis(p,n,t) < all_dis(p,n,f))
                    f = t;
            }
        step /= 2;
    }
	return f;
}

const int N = 111;
int n;
PT p[N];

int main(int argc, char *argv[])
{
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        PT f = fermat_point(p, n);
        DB d = all_dis(p, n, f);
        printf("%.0lf\n", d);
    }
    return 0;
}
