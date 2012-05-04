#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

//二分图最大匹配,hungary算法,邻接表形式,复杂度O(m*e)
//返回最大匹配数,传入二分图大小m,n和邻接表list(只需一边)
//match1,match2返回一个最大匹配,未匹配顶点match值为-1
#include <string.h>
#define MAX_N 666
#define MAXN 770000
#define _clr(x) memset(x,0xff,sizeof(int)*MAXN)

vector<int> vs[MAXN];
int cnt;


int s[MAXN],t[MAXN];
int match1[MAXN], match2[MAXN];
int hungary(int m,int n){
	int p,q,ret=0,i,j,k;
	for (_clr(match1),_clr(match2),i=0;i<m;ret+=(match1[i++]>=0))
		for (_clr(t),s[p=q=0]=i;p<=q&&match1[i]<0;p++)
		{
			//for (e=list[k=s[p]];e&&match1[i]<0;e=e->next)
			k = s[p];
			for (int tt = 0; tt < vs[k].size() && match1[i]<0; ++ tt)
			{
				j = vs[k][tt];
				//if (t[j=e->to]<0){
				if (t[j] < 0) {
					s[++q]=match2[j],t[j]=k;
					if (s[q]<0)
						for (p=j;p>=0;j=p)
							match2[j]=k=t[j],p=match1[k],match1[k]=j;
				}
			}
		}
	return ret;
}


int n;
char mp[MAX_N][MAX_N];

int cc[MAX_N][MAX_N];

int main()
{
	int t;
	scanf("%d", &t);
	int cls = 0;
	while (t--)
	{
		cls ++ ;
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%s", mp[i]);
		cnt = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				cc[i][j] = mp[i][j]=='#'?cnt++:(-1);

		for (int i = 0; i < cnt; ++ i)
			vs[i].clear();
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
			{
				int u = cc[i][j], v;
				if (u != -1)
				{
					if (i+1 < n && cc[i+1][j] != -1)
					{
						v = cc[i+1][j];
						vs[u].push_back(v);
						vs[v].push_back(u);
					}
					if (j+1 < n && cc[i][j+1] != -1)
					{
						v = cc[i][j+1];
						vs[u].push_back(v);
						vs[v].push_back(u);
					}
				}
			}


		int ans = hungary(cnt, cnt) / 2;
		printf("Case %d: %d\n", cls, ans);
	}
	return 0;
}
