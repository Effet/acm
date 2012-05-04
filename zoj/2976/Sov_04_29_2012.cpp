#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define MAX_N 111
#define pow2(a) ((a)*(a))

double X[MAX_N];
double Y[MAX_N];
double Z[MAX_N];
double I[MAX_N];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; ++ i)
			cin >> X[i] >> Y[i] >> Z[i] >> I[i];
		double ans = 0;
		for (int x = -101; x <= 101; ++ x)
			for (int y = -101; y <= 101; ++ y)
			{
				double ret = 0;
				for (int i = 0; i < n; ++ i)
				{
					double rr = pow2(X[i]-x)+pow2(Y[i]-y)+pow2(Z[i]);
					double cxy = sqrt( pow2(Z[i]) ) / sqrt(rr);
					ret += I[i]*cxy/rr;
				}
				ans = max(ans, ret);
			}

		printf("%.2lf\n", ans);
	}
	return 0;
}
