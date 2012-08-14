#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAX_N = 360 + 1;
const ll MOD = 1000000007;

ll C[MAX_N][MAX_N];
ll dp[MAX_N][MAX_N];
ll sum[MAX_N][MAX_N];

void initcmb()
{
	C[0][0] = 1;
	for (int i = 1; i < MAX_N; ++ i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++ j)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
}

void init()
{
    memset(sum, 0, sizeof(sum));
    memset(dp, 0, sizeof(dp));
    
    dp[1][1] = 1;
    for (int i = 1; i < MAX_N; ++ i)
        sum[1][i] = 1;
    
    dp[2][2] = 4;
    for (int i = 2; i < MAX_N; ++ i)
        sum[2][i] = 4;
    
    for (int n = 3; n < MAX_N; ++ n)
    {
        for (int d = 2; d < MAX_N; ++ d)
        {
            dp[n][d] = 0;

            if (n >= d && (d >= 10 || (d < 10 && n <= (1<<d) - 1)))
            {
                dp[n][d] = (dp[n][d] + dp[n-1][d-1] * 2) % MOD;
                int x = n - 2;
                for (int i = 1; i <= x; ++ i)
                {
                    ll add = (sum[i][d-1] * dp[n-1-i][d-1] % MOD)
                        + (dp[i][d-1] * sum[n-1-i][d-1] % MOD)
                        + MOD - (dp[i][d-1] * dp[n-1-i][d-1] % MOD);
                
                    add = (add % MOD) * C[x][i] % MOD;
                    dp[n][d] = (dp[n][d] + add) % MOD;
                }
                dp[n][d] = dp[n][d] * n % MOD;
            }
            
            sum[n][d] = (sum[n][d-1] + dp[n][d]) % MOD;
        }
    }
}

int main ()
{
    initcmb();
    init();
    
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        int n, d;
        cin >> n >> d;

        cout << "Case #" << cas << ": ";
        cout << dp[n][d] << endl;
    }
    return 0;
}
