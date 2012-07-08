#include <iostream>
#include <cstdio>
using namespace std;

#define MAX_N 111111

typedef long long ll;
//typedef __int64 ll;

int n;
ll a[MAX_N];

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; ++ i)
			cin >> a[i];

		ll cnt = 0, d = 1;
		while (d < n - 1)
			d *= 2;
		if (d > n - 1)
			d /= 2;

		for (int i = 0; i < n-1; ++ i)
		{
			cnt += a[i];

			if (i + d > n - 1)
				d/=2;

			a[i+d] += a[i];

			a[i] = 0;
			cout << cnt << endl;
		}
	}
	return 0;
}
