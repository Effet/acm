#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef double DB;
const DB EPS = 1e-8;

int sig(DB x) {return x<-EPS ? -1 : x>EPS ? 1 : 0;}

struct PT {
    DB x, y;
    PT(DB x=0, DB y=0): x(x), y(y) {}
    PT operator -() {return PT(-x, -y);}
    PT operator -(PT p) {return PT(x-p.x, y-p.y);}
    PT operator +(PT p) {return PT(x+p.x, y+p.y);}
    PT operator *(DB s) {return PT(x*s, y*s);}
    PT operator /(DB s) {return PT(x/s, y/s);}
    DB operator ^(PT p) {return x*p.y-y*p.x;}

    PT R(DB co, DB si) {return PT(x*co-y*si, y*co+x*si);}
    DB len() {return sqrt(x*x + y*y);}
};

struct LI {
    PT a, b;
    LI(PT a, PT b): a(a), b(b) {}
};

struct CR {
    PT o; DB r;
    CR(PT o, DB r=1): o(o), r(r) {}
};


// cross point of two line
PT cross_li_li(LI l1, LI l2) { // ensure not rarallel
    return l1.a +
        (l1.b-l1.a) * (((l1.a-l2.b) ^ (l2.a-l2.b)) /
                       ((l1.a-l1.b) ^ (l2.a-l2.b)));
}

PT circumcenter(PT a, PT b, PT c) {
    PT ab=(a+b)/2, ac=(a+c)/2, ba=(b-a).R(0,1), ca=(c-a).R(0,1);
    return cross_li_li(LI(ab,ab+ba), LI(ac,ac+ca));
}

// minimum covering circle problem
// O(n) in random-implement.
bool out(PT p, CR c) {
    return (p-c.o).len()>c.r+EPS;
}
CR smallest_circle(PT *p, int n) {
    CR c(p[0], 0);
    random_shuffle(p, p+n);
    for (int i = 1; i < n; i++)
        if (out(p[i], c)) {
            c = CR(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (out(p[j], c)) {
                    c.o = (p[i]+p[j])/2;
                    c.r = (p[j]-c.o).len();
                    for (int k = 0; k < j; k++)
                        if (out(p[k], c)) {
                            c.o = circumcenter(p[i], p[j], p[k]);
                            c.r = (p[i] - c.o).len();
                        }
                }
            }
        }
    return c;
}


const int N = 505;
PT p[N];
int n;

int main(int argc, char *argv[])
{
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        CR c = smallest_circle(p, n);
        printf("%.2lf %.2lf %.2lf\n", c.o.x, c.o.y, c.r);
    }
    return 0;
}
