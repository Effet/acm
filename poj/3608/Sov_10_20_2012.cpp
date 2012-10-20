#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef double DB;
const DB EPS = 1e-8;

int sig(DB x) {return x<-EPS ? -1: x>EPS ? 1 : 0;}

struct PT {
    DB x, y;
    PT(DB x=0, DB y=0): x(x), y(y) {}
    PT operator - (PT p) {return PT(x-p.x,y-p.y);}
    DB operator * (PT v) {return x*v.x + y*v.y;}
    DB operator ^ (PT v) {return x*v.y - y*v.x;}
    DB len()  {return sqrt(x*x + y*y);}
};

// dot & cross product
DB   dot(PT o, PT a, PT b) {return (a-o)*(b-o);}
DB cross(PT o, PT a, PT b) {return (a-o)^(b-o);}

struct LI {
    PT a, b;
    LI(PT a, PT b): a(a), b(b) {}
};

// distance from point to line
DB dis_p_li(PT p, LI l) {
    // dis(high) = area / bottom
    return fabs(cross(l.a, l.b, p)) / (l.a - l.b).len();
}
// distance from point to segment
DB dis_p_seg(PT p, LI s) {
    if (dot(s.a, s.b, p) > 0
        && dot(s.b, s.a, p) > 0) return dis_p_li(p, s);
    else
        return min((p - s.a).len(), (p - s.b).len());
}
DB dis_seg_seg(LI s1, LI s2) {
    // needn't, because s1 is parallel to s2 in Rotating Calipers.
    // if (intersect_seg_seg(s1, s2, true)) return .0;
    return min(
        min(dis_p_seg(s1.a, s2), dis_p_seg(s1.b, s2)),
        min(dis_p_seg(s2.a, s1), dis_p_seg(s2.b, s1))
        );
}

// p, q must be convex-hull and have same ccw or cw
DB dis_poly2_poly(PT *p, PT *q, int n, int m) {
    int i = 0, j = 0, tn = n, tm = m;
    for (int ti = 1; ti < n; ti++) if (p[ti].y<p[i].y) i = ti;
    for (int ti = 1; ti < m; ti++) if (q[ti].y>q[j].y) j = ti;
    DB r = (p[i] - q[j]).len();
    while (tn > 0 || tm > 0) {
        LI pl(p[i], p[(i+1)%n]), ql(q[j], q[(j+1)%m]);
        int dt = sig((pl.b-pl.a) ^ (ql.b-ql.a));
        
        if (dt <= 0) i=(i+1)%n, --tn;
        if (dt >= 0) j=(j+1)%m, --tm;
        
        if (dt < 0) r = min(r, dis_p_seg(ql.a, pl));
        else if (dt > 0) r = min(r, dis_p_seg(pl.a, ql));
        else r = min(r, dis_seg_seg(pl, ql));
    }
    return r;
}

const int N = 10010;
PT p[N], q[N];
int n, m;

int main(int argc, char *argv[])
{
    while (scanf("%d%d", &n, &m) && n && m) {
        for (int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
        for (int i = 0; i < m; i++) scanf("%lf%lf", &q[i].x, &q[i].y);
        printf("%.6lf\n", dis_poly2_poly(p, q, n, m));
    }
    return 0;
}
