#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	double a, b, c;
	while (cin >> a >> b >> c)
	{
		if (b*b - a*c <= 0)
			printf("-1\n");
		else
			printf("%.6lf\n", (2*a*b*c + a*c*c + a*a*c)/(b*b-a*c));
	}
	return 0;
}
