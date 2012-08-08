// 前 10^7 个数中有 664,579个素数
const int MAX_N = 10000005 / 2;

bool vis[MAX_N];
int prime[664590];

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
