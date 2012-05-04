#include <iostream>
#include <algorithm>
#include <map>
#include <cstdio>
using namespace std;

#define MAX_N 111111

struct node1 {
	int l, r;
	bool operator< (node1 const & aa) const {
		if (this->l == aa.l)
			return (this->r < aa.r);
		else
			return (this->l < aa.l);
	}
} a[MAX_N], b[MAX_N];

struct node2 {
	int id;
	long long cnt, cnt2;
} na[MAX_N], nb[MAX_N];

map<node1, node2> m1;
map<node1, node2>::iterator it;

int pre_order[MAX_N], top;
void mk_pre_order(node1 *tr)
{
	pre_order[0] = top = 1;
	int l = 0, r = 0;
	while (l <= r)
	{
		for (int i = l; i <= r; ++ i)
		{
			int now = pre_order[i];
			if (tr[now].l != -1)
				pre_order[top++] = tr[now].l;
			if (tr[now].r != -1)
				pre_order[top++] = tr[now].r;
		}
		l = r + 1;
		r = top - 1;
	}
}

void do_work()
{
	int cnt = 0;

	m1.clear();

	mk_pre_order(a);
	for (int i = top - 1; i >= 0; -- i)
	{
		int now = pre_order[i];
		if (a[now].l != -1)
			a[now].l = na[ a[now].l ].id;

		if (a[now].r != -1)
			a[now].r = na[ a[now].r ].id;

		it = m1.find(a[now]);
		if (it == m1.end())
		{
			na[now].id = cnt ++;
			na[now].cnt = 1;
			na[now].cnt2 = 0;
			m1.insert(pair<node1, node2>(a[now], na[now]) );
		}
		else
		{
			na[now].id = (it->second).id;
			++ (it->second).cnt;
		}

	}

	mk_pre_order(b);
	for (int i = top - 1; i >= 0; -- i)
	{
		int now = pre_order[i];
		if (b[now].l != -1)
			b[now].l = nb[ b[now].l ].id;

		if (b[now].r != -1)
			b[now].r = nb[ b[now].r ].id;

		it = m1.find(b[now]);
		if (it == m1.end())
		{
			nb[now].id = cnt ++;
		}
		else
		{
			nb[now].id = (it->second).id;
			++ (it->second).cnt2;
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t --)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i)
			scanf("%d%d", &a[i].l, &a[i].r);
		for (int i = 1; i <= m; ++ i)
			scanf("%d%d", &b[i].l, &b[i].r);


		do_work();

		long long ans = 0;
		for (it = m1.begin(); it != m1.end(); ++ it)
			ans += (it->second).cnt * (it->second).cnt2;

		printf("%lld\n", ans);
	}
}
