#include <iostream>
#include <set>
#include <cstdio>
using namespace std;

#define MAX_N 1005

bool vis[MAX_N];
int prime[66459];

void initPrime()
{
	int i;
	for(i = 3; i < MAX_N; i += 2)
	{
		vis[i] = 1;
		vis[i-1] = 0;
	}
	vis[2] = 1;
	int t, k;
	for(i = 3; i * i < MAX_N; i += 2)
	{
		k = i * 2;
		t = k + i;
		while(t < MAX_N)
		{
			vis[t] = 0;
			t += k;
		}
	}
	prime[0] = prime[1] = 2;
	for(i = 3; i < MAX_N; i += 2)
	{
		if(vis[i])
		{
			prime[prime[0]++] = i;
		}
	}
}

set<long long> s;
long long xx[MAX_N];

void init()
{
	initPrime();
	int n = 101;
	int m = 100000;
	s.clear();
	for (int i = 1; i <= n; ++ i)
		for (int j = i+1; j <= n; ++ j)
			for (int k = j+1; k <= n; ++ k)
				for (int b = 1; b <= m; ++ b)
				{
					long long x = (long long)prime[i]*prime[j]*prime[k]*b;
					if (x > 30003)
						break;
					s.insert(x);
				}
	int i = 0;
	for (set<long long>::iterator it = s.begin(); it!=s.end() && i < MAX_N; ++ it, ++ i)
	{
		xx[i] = *it;
	}
}

int main()
{
	init();
	int t, n;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		printf("%lld\n", xx[n-1]);
	}
	return 0;
}
