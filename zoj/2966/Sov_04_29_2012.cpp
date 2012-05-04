#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 1000

struct node {
	int a, b, k;
};

bool cmp(node const & a, node const & b) {
	return a.k < b.k;
}

int father[MAX_N];
int getFather(int v)
{
	if (father[v] == v)
		return v;
	else
	{
		father[v] = getFather(father[v]);
		return father[v];
	}
}

vector<node> e;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, E;
		cin >> n >> E;
		e.clear();
		while (E--)
		{
			node tmp;
			cin >> tmp.a >> tmp.b >> tmp.k;
			e.push_back(tmp);
		}
		sort(e.begin(), e.end(), cmp);
		for (int i = 0; i < n; ++ i)
			father[i] = i;
		int ans = 0;
		for (int i = 0; i < e.size(); ++ i)
		{
			int fx = getFather(e[i].a);
			int fy = getFather(e[i].b);
			if (fx != fy)
			{
				father[fx] = fy;
				ans += e[i].k;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
