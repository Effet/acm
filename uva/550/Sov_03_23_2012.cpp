#include <iostream>
using namespace std;

int main()
{
	int base, aa, b;
	while (cin >> base >> aa >> b)
	{
		int a = (aa*b)%base;
		int r = (aa*b)/base;
		int l = 1;
		while (true)
		{
			if (a == aa && r == 0)
				break;
			else
			{
				int t = a;
				a = (a*b+r)%base;
				r = (t*b+r)/base;

				l ++;
			}
		}
		cout << l << endl;
	}
}
