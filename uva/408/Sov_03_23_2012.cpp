#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

bool vis[10000000+5];

int main()
{
	int s, m;
	while (cin >> s >> m)
	{
		memset(vis,false,sizeof(vis));
		vis[0] = true;
		int t = 0, len = 1;
		while (true)
		{
			t = (t+s)%m;
			if (vis[t])
				break;
			else
			{
				vis[t] = true;
				len ++;
			}
		}
		//cerr << len << endl;
		printf("%10d%10d    %s\n\n", s, m, len==m?"Good Choice":"Bad Choice");
	}
}
