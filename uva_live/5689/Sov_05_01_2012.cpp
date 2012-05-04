#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

//求网络最大流,邻接表形式
//返回最大流量,flow返回每条边的流量
//传入网络节点数n,容量mat,邻接表list,源点source,汇点sink
//list[i](vector<int>)存放所有以i相邻的点,包括反向边!!!

#define MAXN 310
#define inf 1000000000

int max_flow(int n,int mat[][MAXN],vector<int> list[],int source,int sink,int flow[][MAXN]){
	int pre[MAXN],que[MAXN],d[MAXN],p,q,t,i,j,r;
	if (source==sink) return inf;
	for (i=0;i<n;i++)
		for (j=0;j<n;flow[i][j++]=0);
	for (;;){
		for (i=0;i<n;pre[i++]=0);
		pre[t=source]=source+1,d[t]=inf;
		for (p=q=0;p<=q&&!pre[sink];t=que[p++])
			for (r=0;r<list[t].size();++r){
				i=list[t][r];
				if (!pre[i]&&j==mat[t][i]-flow[t][i])
					pre[que[q++]=i]=t+1,d[i]=d[t]<j?d[t]:j;
				else if (!pre[i]&&j==flow[i][t])
					pre[que[q++]=i]=-t-1,d[i]=d[t]<j?d[t]:j;
			}
		if (!pre[sink]) break;

		for (i=sink;i!=source;)
			if (pre[i]>0)
				flow[pre[i]-1][i]+=d[sink],i=pre[i]-1;
			else
				flow[i][-pre[i]-1]-=d[sink],i=-pre[i]-1;
	}

	for (j=i=0;i<n;j+=flow[source][i++]);
	return j;
}

int min_cost_max_flow(int n,int mat[][MAXN],int cost[][MAXN],int source,int sink,int flow[][MAXN],int& netcost){
	int pre[MAXN],min[MAXN],d[MAXN],i,j,t,tag;
	if (source==sink) return inf;
	for (i=0;i<n;i++)
		for (j=0;j<n;flow[i][j++]=0);
	for (netcost=0;;){
		for (i=0;i<n;i++)
			pre[i]=0,min[i]=inf;
		//¿?¿?bellman_ford¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?
		for (pre[source]=source+1,min[source]=0,d[source]=inf,tag=1;tag;)
			for (tag=t=0;t<n;t++)
				if (d[t])
					for (i=0;i<n;i++)
						if (j=mat[t][i]-flow[t][i]&&min[t]+cost[t][i]<min[i])
							tag=1,min[i]=min[t]+cost[t][i],pre[i]=t+1,d[i]=d[t]<j?d[t]:j;
						else if (j=flow[i][t]&&min[t]<inf&&min[t]-cost[i][t]<min[i])
							tag=1,min[i]=min[t]-cost[i][t],pre[i]=-t-1,d[i]=d[t]<j?d[t]:j;
		if (!pre[sink])	break;
		for (netcost+=min[sink]*d[i=sink];i!=source;)
			if (pre[i]>0)
				flow[pre[i]-1][i]+=d[sink],i=pre[i]-1;
			else
				flow[i][-pre[i]-1]-=d[sink],i=-pre[i]-1;
	}
	for (j=i=0;i<n;j+=flow[source][i++]);
	return j;
}


#define MAX_N 310
#define pow2(a) ((a)*(a))

struct circ {
	double freq;
	int x, y, r;
};
bool cmp(circ const & a, circ const & b) {
	return a.freq < b.freq;
}

int n;
circ c[MAXN];
int mat[MAXN][MAXN];
int cost[MAXN][MAXN];
int flow[MAXN][MAXN];

vector<int> vs[MAXN];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%lf%d%d%d", &c[i].freq, &c[i].x, &c[i].y, &c[i].r);
		sort(c, c+n, cmp);
		
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < n; ++ i)
			vs[i].clear();
		for (int i = 0; i < n; ++ i)
			for (int j = i + 1; j < n; ++ j)
			{
				if (abs(c[i].freq-c[j].freq) < 1e-4)
					continue;
				if (pow2(c[i].x-c[j].x) + pow2(c[i].y-c[j].y) < pow2(c[i].r + c[j].r))
				{
					vs[i].push_back(j);
					mat[i][j] = 1;
					cost[i][j] = 1;
				}
			}
		//for (int i = 0; i < n; ++ i)
		//{
			//cout << i << " :";
			//for (int j = 0; j < vs[i].size(); ++ j)
				//cout << vs[i][j] << " ";
			//cout << endl;
		//}
		//int ans = max_flow(n, mat, vs, 0, n-1, flow);
		int costtt;
		int ans = min_cost_max_flow(n, mat,cost, 0, n-1,flow, costtt);
		//cout << ans << endl;
		if (ans > 1)
			printf("Game is VALID\n");
		else
			printf("Game is NOT VALID\n");
	}
	return 0;
}
