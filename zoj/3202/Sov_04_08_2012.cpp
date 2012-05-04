#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		int n;
		int a[111];
		cin >> n;
		for (int i = 0; i < n; i ++)
			cin >> a[i];
		int mm = -1, d;
		for (int i = 0; i < n; i ++)
		{
			if (a[i] > mm)
			{
				mm = a[i];
				d = i;
			}
		}
		cout << d + 1 << " ";
		sort(a, a+n);
		cout << a[n-2] << endl;
	}

}
