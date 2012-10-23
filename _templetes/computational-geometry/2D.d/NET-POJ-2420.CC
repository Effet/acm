// http://poj.org/showmessage?message_id=176290
//题目大意：已知n个点坐标，求其费马点，输出费马点到各个点距离之和，精确到个位，四舍五入
//算法：1.模拟退火；
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define RANGE 10000
#define MAXN 110
#define eps 1e-3
const double pi=acos(-1.0);

struct Point{
	double x,y;
}p[MAXN];
int n;

int SA(int cnt=3){		//cnt为执行模拟退火的次数，默认为3
	double step,tmp,ans,theta;
	double delta=pi/4,ret=1e40,rate=0.83;	//降温速率
	int i;
	Point pt,cur;
	srand(time(NULL));
	while (cnt--) {
		step = rate*RANGE;	//初始温度
		cur.x = (rand()%RANGE+1.0)/RANGE;
		cur.y = (rand()%RANGE+1.0)/RANGE;
		for (ans=i=0; i<n; ++i)
			ans += sqrt( (cur.x-p[i].x)*(cur.x-p[i].x) + (cur.y-p[i].y)*(cur.y-p[i].y) );

		while ( step>eps ){
			for (theta=0; theta<2*pi+eps; theta+=delta) {	//在该点附近产生8个点
				pt.x = cur.x + step*cos(theta);
				pt.y = cur.y + step*sin(theta);
				for (tmp=i=0; i<n; ++i)
					tmp += sqrt( (pt.x-p[i].x)*(pt.x-p[i].x) + (pt.y-p[i].y)*(pt.y-p[i].y) );
				if (tmp<ans)	{ans=tmp;cur=pt;}
			}
			step *= rate;
		}
		if (ans<ret)	ret=ans;
	}
	return ret+0.5;
}

int main(){
	scanf("%d", &n);
	for (int i=0;i<n;++i)		scanf("%lf %lf", &p[i].x , &p[i].y);
	printf("%d\n", SA());
	return 0;
}


//算法：2.牛顿迭代。
#include <stdio.h>
#include <math.h>
#define MAXN 110
#define eps 1e-3

struct Point{
	double x,y;
}p[MAXN];
int n;
double dist[MAXN];

//令f(x,y)=Sigma( sqrt((x-xi)^2 + (y-yi)^2) ),本题要求f(x,y)的最小值。
//此函数是凸的。可验证极小值唯一。且当p0,p1..pn-1不在一条线上时，极小值点唯一。
//于是只需求得f'x=f'y=0的点即可。用牛顿迭代法解此二元方程组。

//简记disti=sqrt( (x-xi)^2 + (y-yi)^2 ),求导得：
//fx=Sigma( (x-xi)/disti) );			fy=Sigma( (y-yi)/disti );
//fxx=Sigma( (y-yi)^2/(dist^3) );		fyy=Sigma( (x-xi)^2/(dist^3) );
//fxy = -Sigma( (x-xi)*(y-yi)/(disti^3) );

//迭代公式为：
//x_k+1 = x_k + (fx*fyy-fy*fxy)/(fxy*fxy-fxx*fyy)|(x_k,y_k);
//y_k+1 = y_k + (fy*fxx-fx*fxy)/(fxy*fxy-fxx*fyy)|(x_k,y_k);

int Newton(){
	double ret=1e40,ans=1e40,tmp=0;
	double fx,fxx,fy,fyy,fxy;	//各阶偏导数的值
	double tx,ty,d3;			//三个简化计算的临时变量
	int i;
	Point cur,pt;
	cur.x = cur.y = 0;
	for (i=0;i<n;++i)	{ cur.x += p[i].x; cur.y += p[i].y;}
	cur.x = cur.x/n + 0.5;		//取平均点作为迭代初值(+0.5是为了避免初值落在某个点上)
	cur.y = cur.y/n + 0.5;
	for (ans=i=0; i<n; ++i)
        ans += dist[i] = sqrt( (cur.x-p[i].x)*(cur.x-p[i].x) + (cur.y-p[i].y)*(cur.y-p[i].y) );

	while (1){
		fx=fy=fxx=fyy=fxy=0;		//计算各阶偏导数
		for (i=0; i<n; ++i) {
			tx = cur.x - p[i].x;
			ty = cur.y - p[i].y;
			d3 = dist[i]*dist[i]*dist[i];

			fx  += tx/dist[i];
			fy  += ty/dist[i];
			fxx += ty*ty/d3;
			fyy += tx*tx/d3;
			fxy -= tx*ty/d3;		//注意这里是减号！！(虽然数据太弱加号也能AC……=。=)
		}

		tmp = fxy*fxy-fxx*fyy;		//迭代出新解
		pt.x = cur.x + (fx*fyy-fy*fxy)/tmp;
		pt.y = cur.y + (fy*fxx-fx*fxy)/tmp;

		for (tmp=i=0; i<n; ++i)
			tmp += dist[i] = sqrt( (pt.x-p[i].x)*(pt.x-p[i].x) + (pt.y-p[i].y)*(pt.y-p[i].y) );

		if (fabs(tmp-ans)<eps)		break;
		else	{cur=pt;ans=tmp;}
	}

	return ans+0.5;
}

int main(){
	scanf("%d", &n);
	for (int i=0;i<n;++i)		scanf("%lf %lf", &p[i].x , &p[i].y);
	printf("%d\n", Newton());
	return 0;
}
