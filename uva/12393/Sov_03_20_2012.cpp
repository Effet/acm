#include <stdio.h>

#define MAX_N 1111111
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))

int n, a[MAX_N], pmin[MAX_N], emin[MAX_N];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("all.in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	while (scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i ++)
			scanf("%d", &a[i]);

		for (int i = 1; i < n; i ++)
			a[i] += a[i-1];

		pmin[0] = a[0];
		for (int i=1;i<n;i++)
			pmin[i] = Min(pmin[i-1],a[i]);
		emin[n-1] = a[n-1];
		for (int i=n-2;i>=0;i--)
			emin[i] = Min(emin[i+1],a[i]);

		int ans = pmin[n-1]>=0?1:0;
		for (int i = 1; i < n; i ++)
			if (pmin[i-1]>=a[i-1]-a[n-1] && emin[i]>=a[i-1])
				ans ++;
		printf("%d\n", ans);
	}
	return 0;
}
