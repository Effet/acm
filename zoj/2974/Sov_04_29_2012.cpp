#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 22

int n;
long long M;
double init[MAX_N];
double matrix[MAX_N][MAX_N];

void copy(double c[][MAX_N], double a[][MAX_N])
{
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			c[i][j] = a[i][j];
}

void print(double a[][MAX_N])
{
	for (int i = 0; i < n; ++ i)
	{
		for (int j = 0; j < n; ++ j)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

void multi(double c[][MAX_N], double a[][MAX_N], double b[][MAX_N])
{
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
		{
			c[i][j] = 0;
			for (int k = 0; k < n; ++ k)
				c[i][j] += a[i][k]*b[k][j];
		}
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 0; i < n; ++ i)
			cin >> init[i];

		memset(matrix,0,sizeof(matrix));
		for (int i = 0; i < n; ++ i)
		{
			int k;
			cin >> k;
			if (k == 0)
				matrix[i][i] = 1;
			else
			{
				int v;
				for (int j = 0; j < k; ++ j)
				{
					cin >> v;
					matrix[v-1][i] += 1.0/k;
				}
			}
		}
		cin >> M;
		double res[MAX_N][MAX_N];
		memset(res,0,sizeof(res));
		for (int i = 0; i < n; ++ i)
			res[i][i] = 1;
		double tmp[MAX_N][MAX_N];
		double tmp2[MAX_N][MAX_N];
		double a[MAX_N][MAX_N];
		copy(a,matrix);

		//print(a);

		while (M)
		{
			if (M%2 == 1)
			{
				multi(tmp,res,a);
				copy(res,tmp);
			}
			M /= 2;
			copy(tmp,a);
			copy(tmp2,a);
			multi(a,tmp,tmp2);
		}

		//print(res);

		double ans[MAX_N];
		for (int i = 0; i < n; ++ i)
		{
			ans[i] = 0;
			for (int j = 0; j < n; ++ j)
				ans[i] += res[i][j]*init[j];
		}
		for (int i = 0; i < n; ++ i)
		{
			printf("%.2lf", ans[i]);
			if (i < n - 1)
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}
