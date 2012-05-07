#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
using namespace std;

#define MAX_N 10000007

int n;
int a[MAX_N];
int sum[MAX_N];
int m, k;
int mmp[MAX_N];
char str[MAX_N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		getchar();
		gets(str);
		n = strlen(str);
		for (int i = 0; i < n; ++ i)
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				a[i] = str[i] - 'a' + 1;
			else if (str[i] >= 'A' && str[i] <= 'Z')
				a[i] = str[i] - 'A' + 51;
			else
				a[i] = 32;
		}

		scanf("%d%d", &m, &k);

		int d;
		sum[0] = a[0] % m;
		for (int i = 1; i < n; ++ i)
			sum[i] = (sum[i-1] + a[i]) % m;


		for (int i = 0; i < m; ++ i)
			mmp[i] = -1;

		for (int i = n-1; i >= 0; -- i)
		{
			if (mmp[ sum[i] ] == -1)
				mmp[ sum[i] ] = i;
		}

		//cout << "mmp" << endl;
		//for (int i = 0; i < m; ++ i)
			//cout << mmp[i] << " ";
		//cout << endl;

		int min_i = -1, len = -1;

		for (int i = n-2; i >= 0; -- i)
		{
			int d = (sum[i] + k)%m;
			if (mmp[d] != -1)
			{
				int t_len = mmp[d] - i;
				if (t_len >= len)
				{
					len = t_len;
					min_i = i;
				}
			}
			if (mmp[sum[i]] == -1)
				mmp[sum[i]] = i;
		}
		if (mmp[k] != -1)
		{
			int t_len = mmp[k] + 1;
			if (t_len >= len)
			{
				len = t_len;
				min_i = -1;
			}
		}

		if (len == -1)
			printf("-1\n");
		else
		{
			printf("%d %d\n", min_i + 1, len);
		}
	}
	return 0;
}
