#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define MAX_N 1111

int rr, r[MAX_N];
int cc, c[MAX_N];
int sum;

int min_swap(int *aa, int l)
{
	int Min = INT_MAX;
	int avg = sum/l;
	int a[MAX_N], b[MAX_N];
	for (int k = 0; k < l; k ++)
	{
		for (int i = k, ii = k, j = 0; j < l; j ++, i ++, ii --)
		{
			a[j] = aa[i%l];
			b[j] = aa[(ii+l)%l];
		}
		int cnt = 0, cntrr = 0;
		for (int i = 0; i < l; i ++)
		{
			cnt += abs(a[i] - avg);
			a[(i+1)%l] += a[i] - avg;

			cntrr += abs(b[i] - avg);
			b[(i+1)%l] += b[i] - avg;
		}
		Min = min(Min, min(cnt,cntrr) );
	}
	return Min;
}

int main()
{
	int t;
	cin >> t;
	for (int cas = 1; cas <= t; cas ++)
	{
		cin >> rr >> cc;
		while (getchar() != '\n');
		memset(r, 0x00, sizeof(r));
		memset(c, 0x00, sizeof(c));
		sum = 0;
		for (int i = 0; i < rr; i ++)
		{
			string str;
			getline(cin, str);
			//cout << str << endl;
			for (int j = 0; j < cc; j ++)
			{
				int d = str[j]-'0';
				r[i] += d;
				c[j] += d;
				sum += d;
			}
		}

		//cout << sum << " " << endl;

		cout << "Case " << cas << ": ";

		if (sum % rr == 0 && sum % cc == 0)
			cout << "both " << min_swap(r,rr) + min_swap(c,cc) << endl;
		else if (sum % rr == 0)
			cout << "row " << min_swap(r,rr) << endl;
		else if (sum % cc == 0)
			cout << "column " << min_swap(c,cc) << endl;
		else
			cout << "impossible" << endl;
	}
}
