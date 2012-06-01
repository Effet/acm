#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int vis[16000];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d", &x);
            ++ vis[x];
        }
        int max_i = 9999, max_v = -1;
        for (int i = 9999; i >= 1001; -- i)
        {
            if (vis[i] > max_v)
            {
                max_v = vis[i];
                max_i = i;
            }
        }
        printf("%d\n", max_i);
    }
    return 0;
}
