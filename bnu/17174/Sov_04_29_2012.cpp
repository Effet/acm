#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int cnt = 1;
	int a[606];
	int n, len;
	for (int i = 0; i < 9999; ++ i)
	{
		n = i;
		len = 0;
		while (n)
		{
			len++;
			n /= 10;
		}
		n = i;
		while (n)
		{
			if (n % len)
				break;
			-- len;
			n /= 10;
		}
		if (n == 0)
		{
			a[cnt ++] = i;
		}

		if (cnt > 599)
			break;
	}

	//cout << cnt << endl << endl;

	int k;
	while (scanf("%d", &k) && k != 0)
		printf("%d\n", a[k]);
}
