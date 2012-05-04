#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 1111

int p[MAX_N];
int tt[MAX_N];

int cnt[MAX_N];
int p2[MAX_N];
int t2[MAX_N];

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			scanf("%d", &p[i]);
		for (int i = 1; i <= n; ++ i)
			scanf("%d", &tt[i]);
		tt[0] = 0;
		for (int i = n; i >= 1; -- i)
			tt[i] -= tt[i-1];

		int c_cnt;
		cnt[1] = c_cnt = 1;
		p2[1] = p[1];
		t2[1] = tt[1];
		for (int i = 2; i <= n; ++ i)
		{
			if (tt[i] <= t2[c_cnt])
			{
				p2[c_cnt] += p[i];
				cnt[c_cnt] ++;
			}
			else
			{
				++ c_cnt;
				p2[c_cnt] = p2[c_cnt-1] + p[i];
				t2[c_cnt] = tt[i];
				cnt[c_cnt] = cnt[c_cnt-1] + 1;
			}
		}

		//cerr << "p2 ";
		//for (int i = 1; i <= c_cnt; i ++)
			//cerr << p2[i] << " ";
		//cerr << endl;

		//cerr << "t2 ";
		//for (int i = 1; i <= c_cnt; i ++)
			//cerr << t2[i] << " ";
		//cerr << endl;
		//cerr << "cnt ";
		//for (int i = 1; i <= c_cnt; i ++)
			//cerr << cnt[i] << " ";
		//cerr << endl;

		int opt_i = 1;
		for (int i = 2; i <= c_cnt; ++ i)
		{
			//if ( (p2[opt_i]+0.0) / cnt[opt_i] < (p2[i]+0.0) / cnt[i])
			if ( p2[opt_i] * cnt[i] < p2[i] * cnt[opt_i])
				opt_i = i;
		}
		double avg = (double)t2[opt_i];
		double opt_t = (p2[opt_i]+0.0)/cnt[opt_i];
		printf("%.6lf %.6lf\n", avg, opt_t);
	}

}
