#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAX_N = 2e4 + 10;

class Point {
public:
    LL x, y;
    LL c;
    int id;
};

bool cmp(const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool cmp2(const Point &a, const Point &b) {
    return a.c < b.c || (a.c == b.c && a.id < b.id);
}
bool cmp3(const Point &a, const Point &b) {
    return a.id < b.id;
}

LL ccw(Point &o, Point &a, Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
LL dot(Point &o, Point &a, Point &b) {
    return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

int n;
Point P[MAX_N], H[MAX_N*2], A[MAX_N];

int convex_hull()
{
    int k = 0;

    sort(P, P + n, cmp);

    for (int i = 0; i < n; i++) {
        while (k >= 2 && ccw(H[k-2], H[k-1], P[i]) <= 0LL) --k;
        H[k++] = P[i];
    }

    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && ccw(H[k-2], H[k-1], P[i]) <= 0LL) --k;
        H[k++] = P[i];
    }

    return k - 1;
}

int main(int argc, char *argv[])
{
    while (cin >> n && n) {

        for (int i = 0; i < n; ++ i) {
            cin >> P[i].x >> P[i].y >> P[i].c;
            P[i].id = i + 1;
        }
        
        n = convex_hull();

        int k = 0;
        if (n >= 3)
        {
            for (int i = 0; i < n; ++ i)
                if (dot(H[i], H[(i+n-1)%n], H[(i+1)%n]) >= 0LL)
                    A[k++] = H[i];
        }

        if (k < 3)
            cout << "Impossible" << endl;
        else {
            sort(A, A + k, cmp2);
            sort(A, A + 3, cmp3);
            cout << A[0].id << " " << A[1].id << " " << A[2].id << endl;
        }
    }
    return 0;
}
