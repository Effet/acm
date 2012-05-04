#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int p[3];

int pp(int v, int u, int k)
{
	int aa = (p[u]-p[v] + 720) % 720;
	int bb = (p[k]-p[u] + 720) % 720;
	if (aa == bb)
		return 1;
	else
		return 0;
}

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		for (int i = 0; i < 3; ++ i)
		{
			int a, b;
			scanf("%d:%d", &a, &b);
			p[i] = a*60 + b;
		}
		sort(p, p+3);
		int ans = pp(0,1,2) + pp(2,0,1) + pp(1,2,0);
		if (ans == 1)
		{
			int ti;
			if (pp(0,1,2))
				ti = p[1];
			else if (pp(2,0,1))
				ti = p[0];
			else
				ti = p[2];

			int mm = ti / 60;
			ti %= 60;
			char ch[3], ch2[3];;
			if (mm < 10)
			{
				ch[0] = mm + '0';
				ch[1] = 0;
			}
			else
			{
				ch[0] = mm/10 + '0';
				ch[1] = mm%10 + '0';
				ch[2] = 0;
			}
			ch2[0] = ti/10 + '0';
			ch2[1] = ti%10 + '0';
			ch2[2] = 0;
			printf("The correct time is %s:%s\n", ch, ch2);
		}
		else
		{
			printf("Look at the sun\n");
		}
	}
}
