#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double OMG = acos(-1.0)/12.0;
const int MAX_N = 1000 + 10;

#define pow2(x) ((x)*(x))
// template <class T> T pow2(T x) {return x*x;}

struct Pillar {
    int x, h;
};

bool cmp(const Pillar &a, const Pillar &b) {
    return a.x < b.x;
}

// 0 is line, positive is ccw
int ccw(const Pillar &a, const Pillar &b, const Pillar &c) {
    return (b.x - a.x) * (c.h - a.h) - (b.h - a.h) * (c.x - a.x);
}

Pillar p[MAX_N];
int hull[MAX_N], cnt;
int L, n, t1, t2;

double f(int x, int h, double co, double si) {return (x*si + h*co) / OMG;}
double f(int x, int h, double th) {return f(x, h, cos(th), sin(th));}

double solve(int c)
{
    double r = .0;

    cnt = 0;
    for (int i = 0; i < n - 1; ++ i)
    {
        while (cnt >= 2) {
            if (ccw(p[i], p[hull[cnt-1]], p[hull[cnt-2]]) > 0)
                break;
            -- cnt;
        }
        hull[cnt++] = i;

        Pillar o = p[i+1]; o.h = 0;
        double pco = 1.0, psi = .0;
        int k = cnt - 2;
        for (; k >= 0; -- k)
        {
            Pillar now = p[hull[k]], pre = p[hull[k+1]];
            
            if (now.h <= pre.h || ccw(o, pre, now) >= 0)
                break;

            double _dx = pre.x - now.x + .0;
            double _dh = now.h - pre.h + .0;

            if (atan2(_dx, _dh) / OMG >= c)
                break;
            
            int dx = o.x - pre.x;
            int dh = pre.h;
            
            double _dis = sqrt(pow2(_dx) + pow2(_dh));
            double co = _dh/_dis, si = _dx/_dis;
            
            r += f(dx, dh, co, si) - f(dx, dh, pco, psi);
            pco = co; psi = si;
        }

        int dx = o.x - p[hull[k+1]].x;
        int dh = p[hull[k+1]].h;

        double mth = min(c * OMG, atan2(dx + .0, dh + .0));
        r += f(dx, dh, mth) - f(dx, dh, pco, psi);
    }

    return r;
}


int main(int argc, char *argv[])
{
    while (scanf("%d%d", &L, &n) != EOF)
    {
        if (L == 0 && n == 0)
            break;
        
        scanf("%d%d", &t1, &t2);
        
        for (int i = 0; i < n; ++ i)
            scanf("%d%d", &p[i].x, &p[i].h);
        sort(p, p+n, cmp);

        double d1 = .0, d2 = .0;
        if (t1 < 12) d1 = solve(12 - t1);
        if (t2 < 12) d2 = solve(12 - t2);

        for (int i = 0; i < n; ++ i)
            p[i].x = L - p[i].x;
        sort(p, p+n, cmp);

        if (t1 > 12) d1 = solve(t1 - 12);
        if (t2 > 12) d2 = solve(t2 - 12);

        double ans = .0;
        if (t1 < 12 && t2 > 12)
            ans = d1 + d2;
        else
            ans = fabs(d1 - d2);

        printf("%.5lf\n", ans);
    }
    return 0;
}
