#include <iostream>
using namespace std;

typedef long long ll;

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		ll a, b, c;
		cin >> a >> b;
		c = a + b;
		int cnt = 0;
		while (c)
		{
			if (c%10 == 5)
				++ cnt;
			c /= 10;
		}
		cout << cnt << endl;
	}
	return 0;
}
