#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 111

int n, m;
int a[MAX_N];
bool adj[MAX_N][MAX_N];
int ans, pos;

void dfs(int u)
{
	int Max = -1, v;
	for (int i = 0; i < n; i ++)
		if (adj[u][i] && Max < a[i])
			Max = a[i], v = i;
	if (Max == -1)
		pos = u;
	else
		ans += Max, dfs(v);
}

int main()
{
	int t;
	cin >> t;
	for (int cas = 1; cas <= t; cas ++)
	{
		cin >> n >> m;
		for (int i = 0; i < n; i ++)
			cin >> a[i];
		memset(adj, false, sizeof(adj));
		for (int i = 0; i < m; i ++)
		{
			int d, dd;
			cin >> d >> dd;
			adj[d][dd] = true;
		}
		ans = 0;
		dfs(0);
		cout << "Case " << cas << ": "
			<< ans << " " << pos << endl;
	}
}
