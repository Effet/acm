#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

struct point {
    double x, y, z;
} p[30];

#define pow2(x) ((x)*(x))
double cal(int i, int j)
{
    return pow2(p[i].x-p[j].x) + pow2(p[i].y-p[j].y) + pow2(p[i].z-p[j].z);
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        double ans = 0;
        for (int i = 0; i < n; ++ i)
            cin >> p[i].x >> p[i].y >> p[i].z;
        
        for (int i = 0; i < (1<<n); ++ i) {
            int cnt = 0;
            for (int j = 0; j < n; ++ j)
                if (i & (1<<j))
                    ++ cnt;
            
            if (cnt == m) {
                double ans_p = 0;
                for (int k = 0; k < n; ++ k) {
                    if (i & (1<<k)) {
                        for (int l = 0; l < n; ++ l) {
                            if (l != k && (i & (1<<l))) {
                                // cout << l << " " << k << endl;
                                ans_p += cal(k, l);
                            }
                        }
                    }
                }
                ans = max(ans, ans_p);
            }
        }
        printf("%.20lf\n", ans/2);
        // cout << ans / 2 << endl;
    }

    return 0;
}
