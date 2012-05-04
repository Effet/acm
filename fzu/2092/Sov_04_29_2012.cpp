#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_N 12
#define MAX_T 202

int vr[5][2] = { {0,0},{0,1},{0,-1},{1,0},{-1,0} };

bool vis[MAX_N][MAX_N][MAX_T];
int mp[MAX_N][MAX_N][MAX_T];
int dp[MAX_N][MAX_N][MAX_N][MAX_N][MAX_T];
int n, m, p;

char g[MAX_N][MAX_N];

bool isleagl(int x, int y) {
	return x>=1&&x<=n && y>=1&&y<=m && g[x][y]=='.';
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i)
			scanf("%s", &g[i][1]);

		scanf("%d", &p);
		memset(mp, 0, sizeof(mp));
		int max_ti = 0;
		for (int i = 0; i < p; ++ i)
		{
			int ti, x, y, v;
			scanf("%d%d%d%d", &ti, &x, &y, &v);
			mp[x][y][ti] += v;

			max_ti = max(max_ti, ti);
		}

		memset(dp, 0, sizeof(dp));
		memset(vis,false,sizeof(vis));
		vis[1][1][0] = true;
		for (int ti = 0; ti < max_ti; ++ ti)
		{
			for (int x1 = 1; x1 <= n; ++ x1) for (int y1 = 1; y1 <= m; ++ y1)
			for (int x2 = 1; x2 <= n; ++ x2) for (int y2 = 1; y2 <= m; ++ y2)
			{
				if (g[x1][y1]=='.' && g[x2][y2]=='.' && vis[x1][y1][ti] && vis[x2][y2][ti])
				{
					for (int i = 0; i < 5; ++ i) for (int j = 0; j < 5; ++ j)
					{
						int x11 = x1 + vr[i][0];
						int y11 = y1 + vr[i][1];
						int x22 = x2 + vr[j][0];
						int y22 = y2 + vr[j][1];
						if (isleagl(x11,y11) && isleagl(x22,y22) )
						{
							vis[x11][y11][ti+1] = vis[x22][y22][ti+1] = true;
							int add;
							if (x11==x22&&y11==y22)
								add = mp[x11][y11][ti+1];
							else
								add = mp[x11][y11][ti+1]+mp[x22][y22][ti+1];

							int big = max(dp[x11][y11][x22][y22][ti+1],dp[x1][y1][x2][y2][ti]+add);
							dp[x11][y11][x22][y22][ti+1] = big;
						}
					}
				}
			}
		}

		int ans = 0;
		for (int x1 = 1; x1 <= n; ++ x1)
			for (int y1 = 1; y1 <= m; ++ y1)
				for (int x2 = 1; x2 <= n; ++ x2)
					for (int y2 = 1; y2 <= m; ++ y2)
						ans = max(ans,dp[x1][y1][x2][y2][max_ti]);
		printf("%d\n", ans);
	}
	return 0;
}
