#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAX_N = 1000;

int vis[MAX_N];
int a[MAX_N];

LL dfs(int x)
{
    vis[x] = 1;
    if (vis[a[x]])
        return 1;
    else
        return dfs(a[x]) + 1;
}

LL gcd(LL a, LL b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

LL lcm(LL a, LL b)
{
    return a / gcd(a, b) * b;
}

vector<int> x[MAX_N];
// int idx[MAX_N];
// int x[MAX_N][MAX_N];

int main(int argc, char *argv[])
{
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF)
    {
        if (n == 0 && k == 0)
            break;

        if (k >= n)
        {
            // printf("1\n");
            cout << 1 << endl;
            continue;
        }
        
        for (int i = 1; i <= k; ++ i)
            x[i].clear();
        
        for (int i = 1; i <= n; ++ i)
            x[((i - 1) % k) + 1].push_back(i);

        int top = 1;
        for (int i = 1; i <= k; ++ i)
            for (int j = x[i].size()-1; j >= 0; -- j)
                a[top++] = x[i][j];

        // memset(idx, 0, sizeof(idx));
        // for (int i = 1; i <= n; ++ i)
        // {
        //     int tt = (i - 1) % k + 1;
        //     x[tt][idx[tt] ++] = i;
        // }

        // int top = 1;
        // for (int i = 1; i <= k; ++ i)
        //     for (int j = idx[i] - 1; j >= 0; -- j)
        //         a[top++] = x[i][j];

        // for (int i = 1; i <= n; ++ i)
        //     cout << a[i] << " ";
        // cout << endl;

        memset(vis, 0, sizeof(vis));
        LL ans = 1;
        for (int i = 1; i <= n; ++ i)
            if (!vis[i])
                ans = lcm(ans, dfs(i));
        
        // LL ans = dfs(1);
        
        cout << ans << endl;

        // printf("%I64d\n", ans);
    }
    return 0;
}
