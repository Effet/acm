#include <iostream>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
using namespace std;

#define MAX 310

int cap[MAX][MAX];
int lev[MAX];
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
	int a[MAX],cur[MAX];
	int pre[MAX];
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
