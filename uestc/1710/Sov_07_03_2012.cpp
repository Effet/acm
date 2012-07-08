#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++ cas) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        printf("Case #%d:\n", cas);
        for (int i = 0; i < q; ++ i) {
            int x;
            scanf("%d", &x);
            if (n + m < x || x < 2) {
                printf("0\n");
            } else {
                int b;
                if (x-1 > m)
                    b = 1 + x - 1 - m;
                else
                    b = 1;
                int ans = min(x-1, n) - b  + 1;
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
