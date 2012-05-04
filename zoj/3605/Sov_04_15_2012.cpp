#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 55

double dp[MAX_N][MAX_N][MAX_N];
int a[MAX_N];
int b[MAX_N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m, K, s;
		scanf("%d%d%d%d", &n, &m, &K, &s);
		for (int i = 1; i <= m; ++ i)
			scanf("%d%d", &a[i], &b[i]);

		memset(dp, 0, sizeof(dp));
		dp[s][0][0] = 1;
		for (int k = 0; k < m; ++ k)
			for (int j = 0; j <= k && j <= K; ++ j)
			{
				for (int i = 1; i <= n; ++ i)
				{
					int ii;
					if (i != a[k+1] && i != b[k+1])
						ii = i;
					else if (i == a[k+1])
						ii = b[k+1];
					else
						ii = a[k+1];

					double now = dp[i][j][k];
					int sum = m-k;
					int cnt = K-j;
					double p_yes = (cnt+0.0)/sum;
					double p_not = 1.0 - p_yes;
					dp[i][j][k+1] += p_not*now;
					dp[ii][j+1][k+1] += p_yes*now;
				}
			}

		double opt_max = -1;
		int id = 0;
		for (int i = 1; i <= n; ++ i)
		{
			if (dp[i][K][m] > opt_max)
			{
				opt_max = dp[i][K][m];
				id = i;
			}
		}
		printf("%d\n", id);
	}
}
