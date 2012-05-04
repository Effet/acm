#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 11111111

bool ok[MAX_N];
int x[101];

void init(int n)
{
	memset(ok, false, sizeof(ok));
	for (int i = 7; i <= n; ++ i)
	{
		if (i%7 == 0)
			ok[i] = true;
		else
		{
			int d = i;
			while (d)
			{
				if (d%10 == 7)
				{
					ok[i] = true;
					break;
				}
				d /= 10;
			}
		}
	}

	memset(x, 0, sizeof(x));
	int d = 0, dd = 1;
	for (int i = 7; i <= n; ++ i)
	{
		if (ok[i]) {
			++ d;
			if (dd <= 99 && d >= dd)
			{
				x[dd++] = i - d + 1;
			}
		} else {
			d = 0;
		}
	}
	//for (int i = 1; i <= 99; ++ i)
		//cout << x[i] << endl;
}

int main()
{
	init(MAX_N - 1);
	int t;
	cin >> t;
	while (t --)
	{
		int n;
		cin >> n;
		cout << x[n] << endl;
	}
	return 0;
}
