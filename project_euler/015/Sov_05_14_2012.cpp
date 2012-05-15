#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

long long dp[21][21];

long long dfs(int n, int m) {
    // cout << n << " " << m << endl;
    if (n > m)
        swap(n,m);
    if (n == 0) {
        if (m == 0)
            return 0;
        else
            return 1;
    }
    if (dp[n][m] != -1)
        return dp[n][m];
    else
        return dp[n][m] = dfs(n-1,m) + dfs(n,m-1);
}

long long solve(int n, int m) {
    if (n > m)
        swap(n, m);
    
    long long ans = 1;
    for (int i = n+m, j = 1; j <= n; -- i, ++ j)
        ans = ans*i/j;
    
    return ans;
}

int main() {
    memset(dp,-1,sizeof(dp));
    int n = 20;
    int m = 20;
    cout << dfs(n,m) << endl;
    cout << solve(n,m) << endl;
    // for (int i = 1; i <= 2; ++ i) {
    //     for (int j = 1; j <= 2; ++ j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
