#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 505

int R, C;
char mp[MAX_N][MAX_N];
int mpp[MAX_N][MAX_N];

struct civ {
	int x, y;
};
queue<civ> q[30];
set<char> s;

int vr[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
bool vis[MAX_N][MAX_N][30];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &R, &C);
		for (int i = 0; i < R; ++ i)
			scanf("%s", mp[i]);

		s.clear();
		for (int i = 0; i < 26; ++ i)
			while (!q[i].empty()) q[i].pop();

		int cnt = 0;
		for (int i = 0; i < R; ++ i)
			for (int j = 0; j < C; ++ j)
			{
				if (mp[i][j] == '#')
					mpp[i][j] = -1;
				else if (mp[i][j] == '.')
				{
					mpp[i][j] = 0;
					++ cnt;
				}
				else
				{
					civ tmp;
					tmp.x = i;
					tmp.y = j;
					q[mp[i][j] - 'a'].push(tmp);

					mpp[i][j] = -1;
				}
			}

		memset(vis,false,sizeof(vis));
		int tim = 1;
		while (cnt)
		{
			++ tim;
			int ccc = 0;
			for (int cc = 0; cc < 26; ++ cc)
			{
				int dd = q[cc].size();
				ccc += dd;
				while (dd--)
				{
					civ u = q[cc].front();
					q[cc].pop();

					if (mp[u.x][u.y] != '*')
					for (int j = 0; j < 4; ++ j)
					{
						civ v = u;
						v.x += vr[j][0];
						v.y += vr[j][1];
						if (v.x >= 0 && v.x < R && v.y >= 0 && v.y < C && !vis[v.x][v.y][cc]
								&& mpp[v.x][v.y] != -1 && (mpp[v.x][v.y] == tim || mpp[v.x][v.y] == 0))
						{
							vis[v.x][v.y][cc] = true;
							if (mpp[v.x][v.y] == tim)
								mp[v.x][v.y] = '*';
							else if (mpp[v.x][v.y] == 0)
							{
								-- cnt;
								mpp[v.x][v.y] = tim;
								mp[v.x][v.y] = cc + 'a';
								q[cc].push(v);
							}
						}
					}
				}
			}
			if (ccc == 0)
				break;
		}
		for (int i = 0; i < R; ++ i)
			printf("%s\n", mp[i]);
		printf("\n");
	}
	return 0;
}
