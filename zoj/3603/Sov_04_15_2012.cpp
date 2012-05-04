#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int a[33][33];
		string s;
		int n;
		cin >> n;
		memset(a, 0, sizeof(a));
		for (int i = 0; i < n; ++i)
		{
			cin >> s;
			for (int j = 0; j < s.size(); ++j)
				a[i][s[j]-'A'] ++;
		}

		for (int i = 0; i < 26; i ++)
		{
			int cnt = 333;
			for (int j = 0; j < n; j ++)
				if (a[j][i] < cnt)
					cnt = a[j][i];
			for (int j = 0; j < cnt; j ++)
				putchar(i+'A');
		}
		putchar('\n');
	}
}
