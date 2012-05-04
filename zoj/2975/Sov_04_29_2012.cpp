#include <iostream>
#include <cstdio>
using namespace std;

#define MAX_N 255

int n, m;
char ch[MAX_N][MAX_N];
int vis[MAX_N][MAX_N];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 0; i < n; ++ i)
			cin >> ch[i];
		int ans = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = i + 1; j < n; ++ j)
			{
				int dp[5] = {0,0,0,0,0};
				for (int k = 0; k < m; ++ k)
					if (ch[i][k] == ch[j][k])
					{
						if (ch[i][k] == 'B')
							++ dp[0];
						if (ch[i][k] == 'J')
							++ dp[1];
						if (ch[i][k] == 'H')
							++ dp[2];
						if (ch[i][k] == 'Y')
							++ dp[3];
						if (ch[i][k] == 'N')
							++ dp[4];
					}
				for (int d = 0; d < 5; ++ d)
					ans += dp[d]*(dp[d]-1)/2;
			}
		cout << ans << endl;
	}
	return 0;
}
