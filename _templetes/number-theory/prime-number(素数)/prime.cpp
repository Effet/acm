 
const int maxn = 10000005 / 2;

bool vis[maxn];
int prime[664590];

void initPrime()
{
	int i;
	for(i = 3; i < maxn; i += 2)
	{
		vis[i] = 1;
		vis[i-1] = 0;
	}
	vis[2] = 1;
	int t, k;
	for(i = 3; i * i < maxn; i += 2)
	{
		k = i * 2;
		t = k + i;
		while(t < maxn)
		{
			vis[t] = 0;
			t += k;
		}
	}
	prime[0] = prime[1] = 2;
	for(i = 3; i < maxn; i += 2)
	{
		if(vis[i])
		{
			prime[prime[0]++] = i;
		}
	}
}

//how many p's in n!
int prime_expr(int p, int n)
{
	int cnt = 0, r = n/p;
	while (r) {
		cnt+=r; r/=p;
	}
	return cnt;
}
