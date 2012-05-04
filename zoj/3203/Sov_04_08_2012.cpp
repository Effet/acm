#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		double H, h, D;
		cin >> H >> h >> D;
		double y = (H-h)/H*D;
		double x1 = D - y;
		double x = sqrt(H*y) - y;

		double ans;
		if (x > 0 && x < x1)
			ans =  H*x/(x+y) + D - y - x;
		else
			ans = max(x1, h);

		printf("%.3lf\n", ans);
	}
}
