#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define inf 100000007

int main()
{
	int t;
	cin >> t;
	int cls = 0;
	while (t--)
	{
		++ cls;
		int n;
		int a[111];
		cin >> n;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		int n_min = inf, n_max = - inf, n_gap = - 1;
		sort(a,a+n);
		for (int i = 0; i < n; ++ i)
		{
			if (i > 0)
				n_gap = max(n_gap, a[i] - a[i-1]);
			n_min = min(n_min, a[i]);
			n_max = max(n_max, a[i]);
		}
		printf("Class %d\n", cls);
		printf("Max %d, Min %d, Largest gap %d\n", n_max, n_min, n_gap);
	}
	return 0;
}
