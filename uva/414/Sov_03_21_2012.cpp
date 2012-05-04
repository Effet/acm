#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	int n, a[1111];
	char c[111];
	while (cin >> n && n)
	{
		getchar();
		for (int k = 0; k < n; k ++)
		{
			gets(c);
			a[k] = 0;
			for (int i = 0; i < strlen(c); i ++)
				if (c[i] == 'X')
					a[k]++;
		}
		sort(a,a+n);
		int ans = 0;
		for (int i = n-2; i >= 0; i --)
			ans += a[n-1] - a[i];
		cout << ans << endl;
	}
}
