#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#include <stdlib.h>
#include <math.h>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};

double xmult(point p1,point p2,point p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

int inside_polygon(point q,int n,point* p,int on_edge=1){
	point q2;
	int i=0,count;
	while (i<n)
		for (count=i=0,q2.x=rand()+offset,q2.y=rand()+offset;i<n;i++)
			if (zero(xmult(q,p[i],p[(i+1)%n]))&&(p[i].x-q.x)*(p[(i+1)%n].x-q.x)<eps&&(p[i].y-q.y)*(p[(i+1)%n].y-q.y)<eps)
				return on_edge;
			else if (zero(xmult(q,q2,p[i])))
				break;
			else if (xmult(q,p[i],q2)*xmult(q,p[(i+1)%n],q2)<-eps&&xmult(p[i],q,p[(i+1)%n])*xmult(p[i],q2,p[(i+1)%n])<-eps)
				count++;
	return count&1;
}


#define MAX_N 1001

bool mp[MAX_N][MAX_N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		memset(mp, false, sizeof(mp));
		int d = 100;
		for (int tt = 0; tt < n; ++ tt)
		{
			char Cmd[5];
			scanf("%s", Cmd);
			if (Cmd[0] == 'C')
			{
				int x, y, r;
				scanf("%d%d%d", &x, &y, &r);
				for (int i = - r; i <=r; ++ i)
					for (int j = -r; j <= r; ++ j)
					{
						if (i*i + j*j > r*r)
							continue;
						int xx = x + i;
						int yy = y + j;
						mp[xx+d][yy+d] = true;
					}
			} else if (Cmd[0] == 'T')
			{
				point p[3];
				for (int j = 0; j < 3; ++ j)
					scanf("%lf%lf", &p[j].x, &p[j].y);
				for (int i = 0; i <= 55; ++ i)
					for (int j = 0; j <= 55; ++ j)
					{
						point pp;
						pp.x = i;
						pp.y = j;
						if (inside_polygon(pp,3,p,1))
						{
							mp[i+d][j+d] = true;
						}
					}

			} else if (Cmd[0] == 'S')
			{
				int x, y, l;
				scanf("%d%d%d", &x, &y, &l);
				for (int i = 0; i <= l; ++ i)
					for (int j = 0; j <= l; ++ j)
						mp[x+i+d][y+j+d] = true;
			}
		}
		int ans = 0;
		for (int i = 0; i <= 250; ++ i)
			for (int j = 0; j <= 250; ++ j)
				if (mp[i][j])
					++ ans;
		printf("%d\n", ans);
	}
	return 0;
}
