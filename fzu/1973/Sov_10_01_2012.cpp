#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const double PI = acos(-1.0);
const double EPS = 1e-8;
const int MAX_N = 1000 + 10;

int sig(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}

class Point {
public:
	int x, y, id;
	double angl;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
    Point operator -(const Point &p) const {return Point(x-p.x, y-p.y);}
    Point operator +(const Point &p) const {return Point(x+p.x, y+p.y);}
    double ang() {return atan2(y + .0, x + .0);}
};

bool ccw(Point &o, Point &a, Point &b) {
	return (LL)(a.x - o.x) * (b.y - o.y) - (LL)(a.y - o.y) * (b.x - o.x) > (LL)0;
}

bool cmp(const Point &a, const Point &b) {
	return a.angl < b.angl;
}


int n;
Point P[MAX_N], p[MAX_N << 1];  // p[] is temp array
int cnt[MAX_N][MAX_N << 1];
void init() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; ++ i) {
        Point pilot = P[i];
        int cntj = 0;
        for (int j = 0; j < n; ++ j) {
            if (j == i)
                continue;
            p[cntj] = P[j];
            p[cntj].angl = (p[cntj] - pilot).ang();
            ++ cntj;
            p[cntj] = pilot + pilot - P[j];
            p[cntj].id = P[j].id + n;
            p[cntj].angl = (p[cntj] - pilot).ang();
            ++ cntj;

        }
        
        sort(p, p + cntj, cmp);

        int tcnt = 0;
        for (int j = 0; j < cntj; ++ j) {
            int id = p[j].id;
            if (id < n)     // real point
                cnt[i][id] = tcnt ++;
            else            // imag point
                cnt[i][id] = tcnt;
        }
    }
}
int points_in_triangle(int x[3])
{
    if (!ccw(P[x[0]], P[x[1]], P[x[2]]))
        swap(x[1], x[2]);

    int ans = n - 3;
    for (int i = 0; i < 3; ++ i) {
        int pilot = x[i], imag = x[(i+1)%3] + n, real = x[(i+2)%3];
        int y = cnt[pilot][imag] - cnt[pilot][real];
        if (y > 0)
            y -= 1;
        else
            y += n - 2;
        
        ans -= y;
    }
    return ans;
}


int main() {
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++ cas) {
        printf("Case %d:\n", cas);

        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &P[i].x, &P[i].y);
            P[i].id = i;
        }

        init();
        
        int m;
        scanf("%d", &m);

        while (m--) {
            int x[3];
            for (int i = 0; i < 3; ++ i)
                scanf("%d", &x[i]);
            
            printf("%d\n", points_in_triangle(x));
        }
    }
}


