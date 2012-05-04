#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

long long ex_gcd(long long a, long long b, long long &x, long long &y)
{
	long long r, t;
	if(b == 0)
	{
		x = 1; y = 0;
		return a;
	}
	r = ex_gcd(b, a % b, x, y);
	t = x; x = y; y = t - a / b * y;
	return r;
}

long long x, y;
long long ag, bg;

long long do_min(long long t)
{
	long long x1 = x + bg*t;
	long long y1 = y - ag*t;
	if (x1 * y1 > 0)
		return max( abs(x1), abs(y1) );
	else
		return abs(x1) + abs(y1);
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		long long A, B, a, b;
		cin >> A >> B >> a >> b;
		long long d = abs(B - A);
		long long gcd = ex_gcd(a, b, x, y);
		if (d % gcd)
		{
			cout << -1 << endl;
			continue;
		}

		d/=gcd;
		x *= d;
		y *= d;
		ag = a/gcd;
		bg = b/gcd;

		//cerr << d << " " << a << " " << b << endl;
		//cerr << "x, ag " << x << " " << bg << endl;
		//cerr << "y, ag " << y << " " << -ag << endl;

		double xx = (y-x+0.0)/(bg+ag);
		long long x1 = (long long)floor(xx);
		long long x2 = (long long)ceil(xx);

		long long ans = 1111111111111111111;

		ans = min(ans, do_min(x1));
		ans = min(ans, do_min(x2));

		cout << ans << endl;

	}
}
