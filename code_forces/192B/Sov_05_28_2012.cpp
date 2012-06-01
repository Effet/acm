#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define inf 1000000

int n, a[1007];
bool vis[1007];

bool is_road() {
    if (a[1] <= 0)
        return false;
    
    vis[1] = true;
    for (int i = 2; i <= n; ++ i)
        vis[i] = false;

    for (int i = 1; i < n; ++ i) {
        if (vis[i] != true)
            continue;
        for (int j = i+1; j <= i+2 && j <= n; ++ j)
        {
            if (a[j] <= 0)
                continue;
            else
                vis[j] = true;
        }
    }
    return vis[n];
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++ i)
            scanf("%d", &a[i]);
        int ans = 0;
        while (is_road() ) {
            ++ ans;
            for (int i = 1; i <= n; ++ i)
                -- a[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
