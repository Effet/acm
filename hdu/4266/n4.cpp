#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

#define EPS 1e-8
#define INF 1e99
typedef double coord_t;
typedef vector<struct Point> Points;
typedef vector<struct Plane> Planes;

struct Point {
    coord_t x, y, z;
    Point operator -(const Point &p) const {return (Point){x-p.x, y-p.y, z-p.z};}
    Point operator ^(const Point &p) const {return (Point){y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x};}
    coord_t operator *(const Point &p) const {return x*p.x + y*p.y + z*p.z;}
    double length() const {return sqrt(x*x + y*y + z*z + 0.0);}
};

struct Plane {
    Point a, b, c;
    Point normal() { return (b - a) ^ (c - a); }
    double dist2p(const Point &p) {return fabs(normal()*(p - a)) / normal().length();}
    bool same_side(const Point &p1, const Point &p2) {return normal()*(p1 - a) * (normal()*(p2 - a)) > EPS;}
};


Planes ConvexHull_3D(Points &P)
{
    Planes CH;
    int n = P.size(), i, j, k, l;
    
    for (i = 0; i < n; i++)
        for (j = i+1; j < n; j++)
            for (k = i+1; k < n; k++)
            {
                Plane pl = {P[i], P[j], P[k]};
                Point p = pl.normal();
                for (l = 0; l < n; l++)
                    if (l != i && l != j && l != k && ! pl.same_side(p, P[l]))
                        break;
                if (l == n)
                    CH.push_back(pl);
            }
    return CH;
}


void solve(Planes &CH)
{
    // cout << CH.size() << endl;
    int m;
    // cin >> m;
    scanf("%d", &m);
    while (m--)
    {
        Point p;
        cin >> p.x >> p.y >> p.z;

        double ans = INF;
        for (int i = 0; i < CH.size(); ++ i)
            ans = min(ans, CH[i].dist2p(p));
        // cout << ans << endl;
        printf("%.4lf\n", ans);
    }
}

int main() {

    int n;
    while (scanf("%d", &n) != EOF)
    // while (cin >> n)
    {
        if (n == 0)
            break;
        
        vector<Point> P(n);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf%lf", &P[i].x, &P[i].y, &P[i].z);
            // cin >> P[i].x >> P[i].y >> P[i].z;

        Planes CH = ConvexHull_3D(P);
        solve(CH);
    }
    
    return 0;
}
