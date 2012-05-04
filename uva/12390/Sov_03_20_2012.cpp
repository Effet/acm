#include <stdio.h>
#include <math.h>

#define MAX_N 555555

int a[MAX_N];

int main()
{
	int n, b, i;
	int l, r, m, c;
	while (scanf("%d%d", &n, &b) && n+1 && b+1)
	{
		l = r = 0;
		for (i = 0; i < n; i ++)
		{
			scanf("%d", &a[i]);
			if (r < a[i])
				r = a[i];
		}
		while (l < r)
		{
			m = (l+r)/2;
			c = 0;
			for (i = 0; i < n;i ++)
			{
				c += ceil((a[i]+0.0)/m);
				//also
				//c += (a[i]+m-1)/m;
			}
			if (c > b)
				l = m + 1;
			else
				r = m;
		}
		printf("%d\n", l);
	}
	return 0;
}
