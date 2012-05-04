#include <iostream>
#include <cstdio>
using namespace std;

#define MAX_N 511
#define inf 1<<30

int t1[MAX_N];
int t2[MAX_N];
int t3[MAX_N];

int f1[MAX_N];
int f2[MAX_N];

int dp[MAX_N][MAX_N];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, M;
		cin >> n >> M;
		for (int i = 1; i <= n; ++ i)
			cin >> t1[i] >> t2[i] >> t3[i] >> f1[i] >> f2[i];

		for (int i = 0; i <= n; ++ i)
			for (int j = 0; j <= M; ++ j)
				dp[i][j] = inf;
		dp[0][M] = 0;
		for (int i = 0; i < n; ++ i)
		{
			int u = i + 1;
			for (int j = 0; j <= M; ++ j)
			{
				if (j >= f1[u])
				{
					dp[u][j-f1[u]] = min(dp[u][j-f1[u]],dp[i][j]+t1[u]);
				}
				dp[u][j] = min(dp[u][j],dp[i][j]+t2[u]);
				dp[u][min(M,j+f2[u])] = min(dp[u][min(M,j+f2[u])],dp[i][j]+t3[u]);
			}
		}
		int ans = inf;
		for (int j = 0; j <= M; ++ j)
			ans = min(ans,dp[n][j]);
		cout << ans << endl;
	}
	return 0;
}
