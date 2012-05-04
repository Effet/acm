#include <stdio.h>

#define Max(a,b) ((a)>(b)?(a):(b))

int f(int i)
{
	if (i==1) return 1;
	if (i%2==0) return f(i/2) + 1;
	else return f(3*i+1) + 1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	int n, m, big, i;
	int nn, mm;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		nn = n; mm = m;
		if (n > m){n^=m;m^=n;n^=m;}
		for (big=0,i=n; i<=m; i ++)
			big=Max(big,f(i));
		printf("%d %d %d\n", nn, mm, big);
	}
	return 0;
}
