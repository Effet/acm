#include <cmath>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <ctype.h>
using namespace std;

#define MAX_N 1111
#define MOD 1000000000

int n, k;
string str;
long long C[MAX_N][MAX_N];
long long p2[MAX_N];
long long p24[MAX_N];
long long p25[MAX_N];
long long p26[MAX_N];

void init()
{
	C[0][0] = 1;
	for (int i = 1; i <= 1000; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
	}
	p2[0] = p24[0] = p25[0] = p26[0] = 1;
	for (int i = 1; i <= 1000; ++i)
	{
		p2[i] = (p2[i-1] * 2) % MOD;
		p24[i] = (p24[i-1] * 24) % MOD;
		p25[i] = (p25[i-1] * 25) % MOD;
		p26[i] = (p26[i-1] * 26) % MOD;
	}
}

void do_work()
{
	int len = str.size()/2;
	int d1 = 0, d2 = 0;
	for (int i = 0; i < len; i ++)
	{
		if (str[i] == str[str.size()-1-i])
			d1 ++;
		else
			d2 ++;
	}

	//cout << endl;
	//cout << "d1 d2 " << d1 << " " << d2 << endl;
	
	long long f1[MAX_N];
	long long f2[MAX_N];
	f1[0] = 1;
	for (int i = 1; i <= d1; i ++)
		f1[i] = (f1[i-1] + C[d1][i]*p25[i]) % MOD;
	f2[0] = p2[d2];
	for (int i = 1; i <= d2; i ++)
		f2[i] = (((C[d2][i]*p24[i]) % MOD ) * p2[d2-i] ) % MOD;

	long long ans = 0;
	for (int i = 0; i <= d2; i ++)
	{
		//int cnt = 2*i + (d2 - i);
		int cnt = d2 + i;
		if (cnt > k)
			break;

		cnt = k - cnt;

		int j = cnt/2;
		if (j > d1)
			j = d1;

		long long tmp = (f2[i] * f1[j]) % MOD;

		ans = (ans + tmp) % MOD;

		if (str.size() % 2 != 0 && cnt > 0)
		{
			j = (cnt - 1)/2;
			if (j > d1)
				j = d1;
			tmp = (f2[i] * f1[j]) % MOD;
			ans = (ans + tmp * 25) % MOD;
		}

	}
	cout << ans << endl;
}

int main()
{
	init();
	int t;
	cin >> t;
	for (int cas = 1; cas <= t; cas ++)
	{
		cin >> n >> k;
		cin >> str;
		//for (int i = 0; i < str.size(); i ++)
			//str[i] = tolower(str[i]);
		cout << "Case " << cas << ": ";
		do_work();
	}
}
