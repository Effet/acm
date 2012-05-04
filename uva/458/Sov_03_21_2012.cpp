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
		int len = strlen(str);
		int k = -7;
		for (int i = 0; i < len; i ++)
		{
			str[i] = str[i]+k;
		}
		cout << str << endl;
	}
}
