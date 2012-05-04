#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

#define MAX_N 1111

int dg[MAX_N];

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		memset(dg, 0, sizeof(dg));
		for (int i = 0; i < n - 1; ++ i)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			++ dg[a];
			++ dg[b];
		}

		int ans = 0;
		for (int i = 1; i <= n; ++ i)
		{
			if (dg[i] <= 1)
				++ ans;
		}
		printf("%d\n", (int)ceil(ans*1.0/2) );
	}

	return 0;
}
