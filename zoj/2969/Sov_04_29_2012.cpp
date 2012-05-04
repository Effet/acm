#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, a[105];
		cin >> n;
		if (n == 0)
		{
			cin >> a[0];
			cout << 0 << endl;
			continue;
		}
		for (int i = n; i >= 0; -- i)
		{
			cin >> a[i];
			if (i == 0)
				cout << endl;
			else if (i == n)
				cout << a[i]*n;
			else
				cout << " " << a[i]*i;
		}
	}
	return 0;
}
