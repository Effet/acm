#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAX_N = 30 + 10;

int n, m;
ll a[MAX_N];
ll sum[MAX_N];
ll lleft;

void dfs(int u, int r) {
    if (u > n) {
        if (r < lleft)
            lleft = r;
        return ;
    }
    
    // ll ff = r*100 + u;
    // if (s.find(ff) != s.end())
    //     return ;
    // s.insert(ff);

    if (sum[u] <= r)
        lleft = min(lleft, r - sum[u]);
    else
    {
        dfs(u+1, r);
        if (a[u] <= r)
            dfs(u+1, r-a[u]);
    }
}

int main(int argc, char *argv[])
{
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; ++ i)
            cin >> a[i];
        sort(a+1, a+n+1, greater<int>());

        a[0] = a[n+1] = 0;
        sum[0] = sum[n+1] = 0;
        sum[n] = a[n];
        for (int i = n - 1; i >= 1; -- i)
            sum[i] = sum[i+1] + a[i];

        lleft = m;
        dfs(1, m);

        // cout << lleft << endl;
        cout << m - lleft << endl;
    }
    return 0;
}
