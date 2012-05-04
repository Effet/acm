#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define eps 1e-7
#define zero(x) (((x)>0?(x):-(x))<eps)

typedef struct point_t{double x,y;}point;
typedef struct line_t{point a,b;}line;

double distance(point p1,point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double angle(point o, point a, point b)
{
	double d1, d2, d;
	d1 = distance(a,o);
	d2 = distance(b,o);
	d  = distance(a,b);
	return acos( (d1*d1+d2*d2-d*d)/(2*d1*d2) );
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("all.in", "r", stdin);
	//freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	char str[111];
	point p[3];
	int i, j;
	double a[2], chk;
	const double pi = acos(-1.0);
	while (gets(str) && str[0] != 'E')
	{
		sscanf(str, "%lf%lf", &p[0].x, &p[0].y);
		for (i = 1; i < 3; i ++)
		{
			gets(str);
			sscanf(str, "%lf%lf", &p[i].x, &p[i].y);
		}

		a[0] = angle(p[0],p[1],p[2]) / pi;
		a[1] = angle(p[1],p[0],p[2]) / pi;

		for (i = 3; i <= 1000; i ++)
		{
			for (j = 0; j < 2; j ++)
			{
				chk = a[j]*i;
				if (!zero( chk - round(chk) ))
					break;
			}
			if (j == 2)
				break;
		}

		printf("%d\n", i);
	}
	return 0;
}
