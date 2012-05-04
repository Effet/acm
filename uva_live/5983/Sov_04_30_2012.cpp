#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

#define MAX_N 505

int R, C;
ll S[MAX_N][MAX_N];
ll dp[MAX_N][MAX_N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &R, &C);
		for (int i = 0; i < R; ++ i)
		{
			for (int j = 0; j < C; ++ j)
			{
				scanf("%lld", &S[i][j]);
				//cout << S[i][j] << " ";
			}
			//cout << endl;
		}


		ll inf = 1000000000000;
		ll l = 0;
		ll r = 500000005;
		while (l < r)
		{
			ll m = (l+r)/2;
			for (int i = 0; i < R; ++ i)
			{
				for (int j = 0; j < C; ++ j)
				{
					if (i == 0 && j == 0)
						dp[i][j] = S[i][i] + m;
					else if (i == 0)
						dp[i][j] = dp[i][j-1] + S[i][j];
					else if (j == 0)
						dp[i][j] = dp[i-1][j] + S[i][j];
					else
						dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + S[i][j];

					if (dp[i][j] <= 0)
						dp[i][j] = -inf;
				}
			}
			if (dp[R-1][C-1] <= 0)
				l = m + 1;
			else
				r = m;
		}
		printf("%lld\n", l);
	}
	return 0;
}
