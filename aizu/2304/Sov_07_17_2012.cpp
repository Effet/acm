#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

const int MAX_N = 300 + 10;
const int MAX_M = 1000 + 10;


int cap[MAX_N][MAX_N];
int lev[MAX_N];
queue<int> q;
int BFS(int s,int t)
{
	int u,v;
	memset(lev,-1,sizeof(lev));
	q.push(s);
	lev[s] = 0;
	while( !q.empty() )
	{
		u = q.front();
		q.pop();
		for(v=0; v<=t; v++)
			if( cap[u][v] > 0 && lev[v] == -1 )
			{
				lev[v] = lev[u] + 1;
				q.push(v);
			}
	}
	return lev[t] != -1;
}
int Dinic(int s,int t)
{
	int a[MAX_N],cur[MAX_N];
	int pre[MAX_N];
	int flow = 0;
	int i,u,flag,v,ag,k;
	while( BFS(s,t) )
	{
		for(i=0; i<=t; i++)
		{					// cur里初始化是第一个节点哈 
			cur[i] = 0;		// DFS中，如果需要回溯，就回溯到cur中的节点。 
			a[i] = INT_MAX;  // a里面存的是剩余流量 
		}
		u = s;
		while(1)
		{
			flag = 0;
			for(v=cur[u]; v<=t; v++)
				if( cap[u][v] > 0 && lev[u] + 1 == lev[v] )
				{
					flag = 1;
					break;
				}
			if( flag )
			{
				cur[u] = v + 1;
				pre[v] = u;
				a[v] = cap[u][v];
				if( a[v] > a[u] )
					a[v] = a[u];
				u = v;			// 从找到的节点后开始在层次图里找路 
				if( u == t ) 	// 找到t后，增广 
				{
					ag = a[t];
					flow += ag;
					for(v=t; v!=s; v=pre[v])
					{
						cur[pre[v]] = v;	//	退回上一步。。 
						cap[pre[v]][v] -= ag;
						cap[v][pre[v]] += ag;
						a[v] -= ag;		
						if( cap[pre[v]][v] == 0 )
							u = pre[v];
					}
				}
			}
			else
				if( u != s )	// 如果u ！= s 那么这条路走不通的话，从u的上一个节点继续找。 
				{
					lev[u] = INT_MAX;  // 相当于从层次图里删除这个节点。 
					u = pre[u];
				}
				else  // 如果从源点找不到增广路，就结束咧。 
					break;
		}
	}
	return flow;
}


int n, m;
int s, t;
struct point {
    int x, y;
} p[MAX_M];
int vv[MAX_M];

int main(int argc, char *argv[])
{
    while (cin >> n >> m)
    {
        memset(cap, 0, sizeof(cap));
 
        for (int i = 1; i <= m; ++ i)
        {
            int x, y;
            cin >> x >> y;
            // -- x; -- y;
            p[i].x = x; p[i].y = y;
            
            cap[x][y] = 1;
            cap[y][x] = 1;
        }

        cin >> s >> t;
        // -- s; -- t;

        cap[0][s] = INT_MAX;
        cap[t][n+1] = INT_MAX;

        int ans = Dinic(0, n+1);
        cout << ans << endl;

        int cnt = 0;
        for (int i = 1; i <= m; ++ i)
        {
            int xx = p[i].x;
            int yy = p[i].y;
            if (cap[xx][yy] > 1)
                vv[cnt++] = i;
        }

        cout << cnt << endl;
        for (int i = 0; i < cnt; ++ i)
        {
            cout << vv[i] << endl;
        }
    }

    return 0;
}
