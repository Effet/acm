#include <iostream>
#include <cmath>
using namespace std;

typedef int LL;
LL ex_gcd( LL a, LL b, LL& x, LL& y )
{
   LL ans, t;
   if ( b == 0 ) { x = 1; y = 0; return a; }
   ans = ex_gcd( b, a%b, x, y );
   t = x; x = y; y = t - (a/b)*y;
   return ans;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int a, m, x, y;
		cin >> a >> m;
		int gcd = ex_gcd(a, m, x, y);
		if (gcd != 1)
		{
			cout << "Not Exist" << endl;
			continue;
		}

		cout << x+m*( (int)ceil((1.0-x)/m) ) << endl;
	}
}
