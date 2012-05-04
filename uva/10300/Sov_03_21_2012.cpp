#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	int n, f, s, a, r;
	int ans;
	cin >> n;
	while (n--)
	{
		cin >> f;
		ans = 0;
		while (f--)
		{
			cin >> s >> a >> r;
			ans += s * r;
		}
		cout << ans << endl;
	}
}
