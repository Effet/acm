  //一堆房子，有的房子之间有门，有的房子有侵入者，有的房子没有侵入者，
	 // 有一个房间需要保护。I代表有侵入者，NI代表没有侵入者，
	 // 一开始的N,M代表的n个房间和m房间需要保护。NI或者I后边跟一个k，
	 // 然后后边k个数表示从第i个房间可以到达这些个房间不需要钥匙，
	 // 而这k个房间到达第i个房间只能到达一次或者从第i个房间过去再过来。。。

	 
	 
//  一头染色，一头不染色 为割边
#include <iostream>  
#include <vector>
#include<algorithm>
using namespace std;
#define inf 2000000000
#define N 210
#define M 20000
struct edge{
	int from,to,val,next;
}e[M];
int w[N],que[N],dis[N],edge,cur[N];
void add(int from,int to,int va){
    e[edge].from=from;
	e[edge].to=to;
	e[edge].val=va;
    e[edge].next=w[from];
	w[from]=edge++;

    e[edge].from=to;
	e[edge].to=from;
	e[edge].val=0;
    e[edge].next=w[to];
	w[to]=edge++;
}
int bfs(int n,int s,int t){
    int head,tail,id;
    head=tail=0;que[tail++]=s;
    memset(dis,-1,sizeof(int)*n);
	dis[s]=0;
	while(head<tail) // bfs,得到顶点i的距s的最短距离dis[i]
	{
		for(id=w[que[head++]];id!=-1;id=e[id].next)
			if(e[id].val>0&&dis[e[id].to]==-1)
            {
				dis[e[id].to]=dis[e[id].from]+1;
                que[tail++]=e[id].to;
                if(e[id].to==t) return 1;
            }
	}
    return 0;
}
int Dinic(int n,int s,int t){
    int Mflow=0,tmp,i;
    while(bfs(n,s,t)){
        int u=s,tail=0;
        for(i=0;i<n;i++) cur[i]=w[i];
        while(cur[s]!=-1){
			if(u!=t&&cur[u]!=-1&&e[cur[u]].val>0&&dis[u]!=-1&&dis[u]+1==dis[e[cur[u]].to]){
				que[tail++]=cur[u];
				u=e[cur[u]].to;
			}
            else if(u==t){
                for(tmp=inf,i=tail-1;i>=0;i--)
					tmp=min(tmp,e[que[i]].val);
                for(Mflow+=tmp,i=tail-1;i>=0;i--){
                    e[que[i]].val-=tmp;
                    e[que[i]^1].val+=tmp;
                    if(e[que[i]].val==0) tail=i;
                }
                u=e[que[tail]].from;
            }
            else{
                while(tail>0&&u!=s&&cur[u]==-1) u=e[que[--tail]].from;
                cur[u]=e[cur[u]].next;
            }
		}
    }
    return Mflow;
}
int main()
{
	char str[3];
	int c,k,i,j,m,T,num,t;
	int n,a,b;
	scanf("%d",&T);
	while(T--)
	{
		memset(w,-1,sizeof(w));
		edge=0;
		scanf("%d%d",&n,&t);
		for(i=0;i<n;i++)
		{
			scanf("%s%d",str,&num);
			if(str[0]=='I') add(n,i,10000);
			while(num--)
			{
				scanf("%d",&a);
				add(i,a,10000);
				add(a,i,1);
			}
		}
		t=Dinic(n+1,n,t);
		if(t>=10000) printf("PANIC ROOM BREACH\n");
		else printf("%d\n",t);
	}
	return 0;
}



Isap
#include <iostream>  
#include <vector>
#include<algorithm>
using namespace std;
#define inf 2000000000
#define M 100000
#define N 1010
struct data
{
    int u,v,cap,next;
}e[M];
int w[N],stack[N],dis[N];
int now[N],pre[N],cnt[N],cur[N],cut[N],top,edge;
void add(int u,int v,int cap)
{
    e[edge].u=u;
    e[edge].v=v;
    e[edge].cap=cap;
    e[edge].next=w[u];
    w[u]=edge++;

    e[edge].u=v;
    e[edge].v=u;
    e[edge].cap=0;
    e[edge].next=w[v];
    w[v]=edge++;
}
int Isap(int n,int st,int ed)
{
    int edge_flow;
    int now_flow,found,min;
    int i,j,t;
    memset(dis,0,sizeof(dis));
    memset(now,-1,sizeof(now));
    memset(cnt,0,sizeof(cnt));
    i=st;
    edge_flow=0;
    now_flow=inf;
    cnt[0]=n;
    while(dis[st]<n)
    {
        cur[i]=now_flow;
        found=0;
        if(now[i]==-1) t=w[i];
        else t=now[i];
        while(t!=-1)
        {
            j=e[t].v;
            if(e[t].cap>0&&dis[j]+1==dis[i])
            {
                found=1;
                now[i]=t;
                if(e[t].cap<now_flow) now_flow=e[t].cap;
                pre[j]=t;
                i=j;
                if(i==ed)
                {
                    edge_flow+=now_flow;
                    while(i!=st)
                    {
                        e[pre[i]].cap -= now_flow;
                        e[pre[i]^1].cap+=now_flow;
                        i=e[pre[i]].u;
                    }
                    now_flow=inf;
                }
                break;
            }
            t=e[t].next;
        }
        if(found) continue;
        if(--cnt[dis[i]]==0) break;
        min=n-1;
        t=w[i];
        while(t!=-1)
        {
            if(e[t].cap>0&&dis[e[t].v]<min)
            {
                min=dis[e[t].v];
                now[i]=t;
            }
            t=e[t].next;
        }
        dis[i]=min+1;
        cnt[dis[i]]++;
        if(i!=st)
        {
            i=e[pre[i]].u;
            now_flow=cur[i];
        }
    }
    return edge_flow;
}
int main()
{
	char str[3];
	int c,k,i,j,m,T,num,t,n,a;
	scanf("%d",&T);
	while(T--)
	{
		memset(w,-1,sizeof(w));
		edge=0;
		scanf("%d%d",&n,&t);
		for(i=0;i<n;i++)
		{
			scanf("%s%d",str,&num);
			if(str[0]=='I') add(n,i,10000);
			while(num--)
			{
				scanf("%d",&a);
				add(i,a,10000);
				add(a,i,1);
			}
		}
		t=Isap(n+1,n,t);
		if(t>=10000) printf("PANIC ROOM BREACH\n");
		else printf("%d\n",t);
	}
	return 0;
}
