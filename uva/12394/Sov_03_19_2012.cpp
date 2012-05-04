#include <stdio.h>
#include <string.h>

#define MAX_N 1111

struct Node {
	char name[15];
	int books[8];
} a[MAX_N];

int k, n;

int q[MAX_N*10], top;

int vio(int p)
{
	int i, j;
	if (top != k) return 1;
	for (i = 0; i < top; i ++)
	{
		if (!strcmp(a[ q[i] ].name,a[ p ].name)) return 1;
		for (j = i + 1; j < top; j ++)
			if (q[i] == q[j])
				return 1;
	}
	return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
	//freopen("all.in", "r", stdin);
	//freopen("out", "w", stdout);
#endif

	int i, ii, j, ans;

	while(scanf("%d%d", &k, &n) && n && k) {
		for(i = 1; i <= n; i ++){
			scanf("%s", a[i].name);
			for(j = 1; j <= k; j ++)
				scanf("%d", &a[i].books[j]);
		}

		/*for books*/
		for (ans = 0, i = 1; i <= n; i ++)
		{
			for (top = 0, ii = 1; ii <= n; ii ++) for (j = 1; j <= k; j ++)
				if (a[ii].books[j] == i) q[top++] = ii;
			if (vio(i)) ans ++;
		}

		if (ans == 0) printf ("NO PROBLEMS FOUND\n");
		else if (ans == 1) printf ("1 PROBLEM FOUND\n");
		else printf ("%d PROBLEMS FOUND\n", ans);
	}
	return 0;
}
