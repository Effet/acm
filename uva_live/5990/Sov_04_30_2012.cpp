#include <iostream>
#include <cstdio>
using namespace std;

#define MAX_N 100010

typedef long long ll;

ll mod = 1000000007;

long long fastpow(long long a, long long k, long long c)
{
	long long res = 1;
	while(k)
	{
		if (k%2 == 1)
			res = res * a % c;
		k /= 2;
		a = a * a % c;
	}
	return res;
}

int n;
int a[MAX_N];
int n_min, n_max;
int min_cnt, max_cnt, other_cnt;
int l_min_cnt[MAX_N];
int l_max_cnt[MAX_N];

ll dp[MAX_N];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i)
			scanf("%d", &a[i]);

		n_min = MAX_N;
		n_max = -MAX_N;
		for (int i = 1; i <= n; ++ i)
		{
			n_min = min(n_min, a[i]);
			n_max = max(n_max, a[i]);
		}

		if (n_min == n_max)
		{
			ll d_sum = (fastpow((ll)2,(ll)n,mod) - 1 + mod) % mod;
			ll a_sum = ( (1 + (ll)n)*(ll)n / 2 ) % mod;
			printf("%lld %lld\n", a_sum, d_sum);
			continue;
		}

		l_min_cnt[0] = l_max_cnt[0] = 0;
		min_cnt = max_cnt = 0;
		for (int i = 1; i <= n; ++ i)
		{
			l_min_cnt[i] = l_min_cnt[i-1] + (a[i]==n_min?1:0);
			l_max_cnt[i] = l_max_cnt[i-1] + (a[i]==n_max?1:0);
		}
		min_cnt = l_min_cnt[n];
		max_cnt = l_max_cnt[n];
		other_cnt = n - min_cnt - max_cnt;


		ll m_min = (fastpow((ll)2,(ll)min_cnt,mod) - 1 + mod) % mod;
		ll m_max = (fastpow((ll)2,(ll)max_cnt,mod) - 1 + mod) % mod;
		ll m_other = fastpow((ll)2,(ll)other_cnt,mod);
		ll sum = ((m_min * m_max) % mod * m_other) % mod;

		ll ans = 0;

		for (int i = 1, j = 1; i <= n; ++ i)
		{
			while (j <= n && (l_max_cnt[j] - l_max_cnt[i-1] <= 0 || l_min_cnt[j] - l_min_cnt[i-1] <= 0))
			{
				++ j;
			}
			if (j > n)
				break;
			ans = (ans + (ll)(n - j + 1)) % mod;
		}

		printf("%lld %lld\n", ans, sum);

	}
	return 0;
}
