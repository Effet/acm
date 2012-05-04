#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	int a[55];
	int cas = 0;
	while (cin >> n && n)
	{
		int avg = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
			avg += a[i];
		}
		avg /= n;

		int ans = 0;
		for (int i = 0; i < n; i ++)
			if (a[i] > avg)
				ans += a[i] - avg;

		cas ++;
		printf("Set #%d\nThe minimum number of moves is %d.\n\n", cas, ans);
	}
}
