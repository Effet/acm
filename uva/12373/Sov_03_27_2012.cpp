#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 1007

long long dp[MAX_N][MAX_N];

void init()
{
	memset(dp,0x00,sizeof(dp));
	for (int i = 1; i < MAX_N; i ++)
		for (int j = 1; j < MAX_N; j ++)
		{
			int a1 = max(i,j)*2;
			int a2 = (i+j)*2;
			if (a1<MAX_N && a2<MAX_N)
			{
				dp[a1][a2] ++;
				dp[a2][a1] ++;
			}
		}
	for (int h = 1; h <= 600; h ++)
		for (int w = 1; w <= 600; w++)
		{
			int c = h*h + w*w;
			int d = (int)sqrt((double)c);
			if (d*d == c)
			{
				for (int r = 1; r <= d-1; r ++)
				{
					int rr = d-r;
					int b = min(-r,h-rr);
					int t = max(r,h+rr);
					int L = min(-r,w-rr);
					int R = max(r,w+rr);

					int a1 = t-b;
					int a2 = R-L;
					if (a1<MAX_N && a2<MAX_N)
					{
						dp[a1][a2] += 2;
						//ddp[a2][a1] += 2;
					}
				}
			}
		}

	//test();

	for (int i = 1; i < MAX_N; i ++)
		for (int j = 1; j < MAX_N; j ++)
			dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
	for (int i = 1; i < MAX_N; i ++)
		for (int j = 1; j < MAX_N; j ++)
			dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
}

int main()
{
	//freopen("out", "w", stdout);
	init();
	int t, n, m;
	cin >> t;
	for (int cas = 1; cas <= t; cas ++)
	{
		cin >> n >> m;
		cout << "Case " << cas << ": " << dp[n][m] << endl;
	}
}
