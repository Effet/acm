
int fastpow(long long a, long long k, long long c)
{
	long long res = 1;
	while(k)
	{
		if (k&1)
			res = res * a % c;
		k >>= 1;
		a = a * a % c;
	}
	return int(res);
}
