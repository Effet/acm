//how many p in n!
int prime_factorial(int p, int n)
{
	int cnt = 0, r = n/p;
	while (r) {
		cnt+=r; r/=p;
	}
	return cnt;
}
