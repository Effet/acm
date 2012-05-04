#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		int n, m, k;
		int a[22][22];
		//scanf("%d%d%d", &n, &m, &k);
		cin >> n >> m >> k;
		int num = 1;
		for (int i = 0; i < n; i ++)
			for (int j = 0; j < m; j ++)
				a[i][j] = num ++;

		for (int i = 1; i < n - 1; i ++)
			for (int j = 1; j < m - 1; j ++)
			{
				if (k > 0)
				{
					k --;
					a[i][j] = 0;
					a[i-1][j] = a[i][j-1] = 0;
					a[i+1][j] = a[i][j+1] = 0;
				}
			}

		for (int i = 0; i < n; i ++)
			for (int j = 0; j < m; j ++)
			{
				printf("%d", a[i][j]);
				if (j < m - 1)
					putchar(' ');
				else
					putchar('\n');
				//cout << a[i][j];
				//if (j < m - 1)
					//cout << " ";
				//else
					//cout << endl;
			}
	}
}
