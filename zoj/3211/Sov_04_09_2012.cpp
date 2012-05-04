#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 333

struct node {
	int a, d;
} v[MAX_N];

bool cmp(node const & a, node const & b) {
	return a.d < b.d;
}

int dp[MAX_N][MAX_N];

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		int n, m; // m < n
		cin >> n >> m;
		for (int i = 0; i < n; ++ i)
			cin >> v[i].a;
		for (int i = 0; i < n; ++ i)
			cin >> v[i].d;

		sort(v, v+n, cmp);

		dp[0][0] = v[0].a;
		for (int i = 1; i < n; ++ i)
			dp[0][i] = max(dp[0][i-1],v[i].a);
		for (int i = 1; i < m; ++ i)
			dp[i][i] = dp[i-1][i-1] + v[i].a + v[i].d * i;

		for (int i = 1; i < m; i ++)
		{
			for (int j = i + 1; j < n; j ++)
				dp[i][j] = max(dp[i][j-1],dp[i-1][j-1]+v[j].a+v[j].d*i);
		}

		cout << dp[m-1][n-1] << endl;
	}
}
