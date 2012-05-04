#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	char str[1111];
	while (gets(str))
	{
		int ans = 0;
		for (int i = 1; i < strlen(str); i ++)
		{
			if (isalpha(str[i-1]) && !isalpha(str[i]))
				ans ++;
		}
		cout << ans << endl;
	}
}
