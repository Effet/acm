//don't forget spaces at the end of line
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	char a[111][111];
	int n = 0, len = 0;
	while (gets(a[n]))
	{
		for (int i = strlen(a[n]) - 1;  i >= 0; i --)
		{
			if (a[n][i] == ' ')
				a[n][i] = 0;
			else
				break;
		}
		len = max(len,(int)strlen(a[n]));
		n ++;
	}

	for (int j = 0; j < len; j ++)
	{
		for (int i = n-1; i >= 0; i --)
		{
			if (j < (int)strlen(a[i]))
				putchar(a[i][j]);
			else
				putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
