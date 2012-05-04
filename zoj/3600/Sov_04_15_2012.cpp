#include <iostream>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int d, t;
		cin >> d >> t;
		double a = 10, b = 11;
		if (d > 3)
		{
			if (d <= 10)
			{
				a += 2.0*(d-3);
				b += 2.5*(d-3);
			}
			else
			{
				a += 2.0*7 + 3.0 *(d-10);
				b += 2.5*7 + 3.75*(d-10);
			}
		}
		
		a += t*2.0/5 + 1;
		b += t*2.5/4;

		cout << (int)(b+0.5) - (int)(a+0.5) << endl;
	}
}
