#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAX_N = 1000 + 10;
const int MAX_K = MAX_N * 2;
const int MOD   = 100000007;

ll dp1[MAX_N][MAX_K];
ll dp2[MAX_N][MAX_K];

void init()
{
    memset(dp1, 0, sizeof(dp1));
    memset(dp2, 0, sizeof(dp2));
    dp1[1][1] = 0; dp2[1][1] = 1;
    dp1[1][2] = 1; dp2[1][2] = 0;
    for (int n = 2; n < MAX_N; ++ n)
    {
        dp1[n][1] = 0; dp2[n][1] = 1;
        for (int k = 2; k <= 2*n; ++ k)
        {
            dp1[n][k] = (dp1[n-1][k-2] + dp1[n-1][k-1] * 2 + dp1[n-1][k] + dp2[n-1][k-2] + dp2[n-1][k-1] * 2)%MOD;
            dp2[n][k] = (dp1[n-1][k-1] + dp1[n-1][k] * 2 + // dp1[n-1][k+1] + 
                         dp2[n-1][k-1] + dp2[n-1][k]) % MOD;
        }
    }
}

int main(int argc, char *argv[])
{
    init();
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        cout << (dp1[n][k] + dp2[n][k]) % MOD << endl;
    }
    return 0;
}
