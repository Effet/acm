#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAX_N = 64 + 3;

ll dp[MAX_N][10];

void init()
{
    for (int i = 0; i < 10; ++ i)
        dp[1][i] = i + 1;
    for (int i = 2; i < MAX_N; ++ i)
    {
        dp[i][0] = 1;
        for (int j = 1; j < 10; ++ j)
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
}

int main(int argc, char *argv[])
{
    init();
    int p;
    cin >> p;
    while (p--)
    {
        int cas, n;
        cin >> cas >> n;
        cout << cas << " " << dp[n][9] << endl;
    }
    return 0;
}
