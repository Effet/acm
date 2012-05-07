#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define MAX_N 1007
#define MAX_M 1000007

struct edge {
	int u, v, x, y;
	int d;
} e[MAX_M];

bool cmp(edge const & a, edge const & b) {
	return a.d < b.d;
}

int n, m;

int father[MAX_N];
int get_father(int v)
{
	if (v == father[v])
		return v;
	else
	{
		father[v] = get_father(father[v]);
		return father[v];
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; ++ i)
		{
			scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].x, &e[i].y);
			e[i].d = e[i].y - e[i].x;
		}
		sort(e, e+m, cmp);
		for (int i = 0; i <= n; ++ i)
			father[i] = i;
		long long ans = 0;
		for (int i = 0; i < m; ++ i)
		{
			int fx = get_father(e[i].u);
			int fy = get_father(e[i].v);
			if (e[i].d <= 0)
				ans += e[i].y;
			else
			{
				if (fx != fy)
					ans += e[i].y;
				else
					ans += e[i].x;
			}

			if (fx != fy)
				father[fx] = fy;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
