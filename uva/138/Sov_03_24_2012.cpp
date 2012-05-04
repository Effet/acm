#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	long long k = 6;
	int cnt = 0;
	while (true)
	{
		long long t = ( (k-1)*k+k )*2;
		long long n = (long long)sqrt(t+0.0);
		if (n * (n+1) == t)
		{
			printf("%10lld%10lld\n", k, n );
			cnt ++;
			if (cnt == 10)
				break;
		}
		k ++;
	}
}
