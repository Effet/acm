#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node {
	int u, v, l;
};
bool cmp(node const & a, node const & b)
{
	if (a.l == b.l)
	{
		if (a.u == b.u)
			return a.v < b.v;
		else
			return a.u < b.u;
	}
	return a.l < b.l;
}
bool cmp2(node const & a, node const & b)
{
	if (a.u == b.u)
		return a.v < b.v;
	else
		return a.u < b.u;
}

int t, n;
vector<node> v, ans;
vector<node>::iterator it;

int f[555];
int get_find(int x)
{
	if (f[x]==x)
		return x;
	else
	{
		f[x] = get_find(f[x]);
		return f[x];
	}
}

int main()
{
	cin >> t;
	while (t --)
	{
		cin >> n;
		v.clear();
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 1; j <= n; j ++)
			{
				int d;
				cin >> d;
				if (d > 0 && i < j)
				{
					node a;
					a.u = i;
					a.v = j;
					a.l = d;
					v.push_back(a);
				}
			}
		}
		sort(v.begin(), v.end(), cmp);
		for (int i = 1; i <= n; ++i)
			f[i] = i;
		ans.clear();
		for (it=v.begin(); it!=v.end(); ++it)
		{
			int x = it->u;
			int y = it->v;
			int fx = get_find(x);
			int fy = get_find(y);
			if (fx != fy)
			{
				if (fx < fy)
					f[fy] = fx;
				else
					f[fx] = fy;

				ans.push_back(*it);
				if (ans.size() == n - 1)
					break;
			}
		}
		if (ans.size() < n - 1)
			cout << -1 << endl;
		else
		{
			sort(ans.begin(), ans.end(), cmp2);
			for (it = ans.begin(); it != ans.end(); ++ it)
			{
				cout << it->u << " " << it->v;
				if (it+1 != ans.end())
					cout << " ";
				else
					cout << endl;
			}
		}
	}
}
