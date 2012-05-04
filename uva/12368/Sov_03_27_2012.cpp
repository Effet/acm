#include <map>
#include <iostream>
using namespace std;

map<long long,int> m;
map<long long,int>::iterator it;

void init()
{
	m.clear();
	for (int k = 0; k < (1<<10); k ++)
	{
		long long num = 0;
		long long cnt = 1;
		for (int i = 0; i < 10; i ++)
		{
			if (k & (1<<i))
			{
				num += i*cnt;
				cnt *= 10;
			}
		}
		m.insert( pair<long long,int>(num,k) );
	}
	//for (it = m.begin(); it!=m.end(); it++)
		//cout << it->first << " " << it->second << endl;
}

bool ok(int stat, int o)
{
	if (o < 10 && ( stat&(1<<o) ) )
		return true;

	for (int i = 1; i < o; i ++)
	{
		int a = i;
		int b = o - i;
		int f[4], top = 0;
		while (a)
		{
			f[top++] = a%10;
			a/=10;
		}
		while (b)
		{
			f[top++] =b%10;
			b/=10;
		}
		bool flag = true;
		for (int j = 0; j < top; j ++)
		{
			if (stat&(1<<f[j]))
				;
			else
				flag = false;
		}
		for (int j = 0; j < top; j ++)
			for (int k = j + 1; k < top; k ++)
				if (f[j] == f[k])
					flag = false;

		if (flag)
			return true;
	}

	int f[4], top = 0;
	while (o)
	{
		f[top++] = o%10;
		o /= 10;
	}
	bool flag = true;
	for (int j = 0; j < top; j ++)
	{
		if (stat&(1<<f[j]))
			;
		else
			flag = false;
	}
	for (int j = 0; j < top; j ++)
		for (int k = j + 1; k < top; k ++)
			if (f[j] == f[k])
				flag = false;

	if (flag)
		return true;
	else
		return false;
}


bool dp[1111][111];
void initrr()
{
	for (int k = 0; k < (1<<10); k ++)
		for (int i = 1; i <= 100; i ++)
			dp[k][i] = ok(k,i);
}

int main()
{
	init();
	initrr();
	int n, a[11];
	int cas = 0;

	//cout << ok(1, 2) << endl;
	while (cin >> n && n)
	{
		for (int i = 0; i < n; i ++)
			cin >> a[i];
		for (it = m.begin(); it != m.end(); it++)
		{
			int i;
			for (i = 0; i < n; i ++)
			{
				//if (!ok(it->second, a[i]))
				if (!dp[it->second][a[i]])
					break;
			}
			if (i == n)
			{
				cas ++;
				cout << "Case " << cas << ": "
					<< it->first << endl;
				break;
			}
		}

	}
}
