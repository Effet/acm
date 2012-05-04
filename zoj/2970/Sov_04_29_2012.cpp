#include <iostream>
#include <algorithm>
using namespace std;

int n, a[10000];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		string str;
		cin >> str >> n;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		sort(a, a+n);
		if (str == "Faster")
			cout << a[0] << endl;
		else
			cout << a[n-1] << endl;
	}
	return 0;
}
