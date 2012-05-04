#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll sPow(int x,int n,ll M){
	ll sum=1;
	while(n){
		if(n&1)sum = (sum%M)*(x%M)%M;
		x = (x%M)*(x%M)%M;
		n >>= 1;
	}
	return sum%M;
}

#define MAX_L 100010

long long B, P;
long long l, n;
long long pb[MAX_L];

long long c[MAX_L];

int Lowbit(int t){
	return t & ( -t );
}

void Plus(int pos,long long num){
	while(pos < MAX_L){
		c[pos] = (c[pos] + num + P) % P;
		pos += Lowbit(pos);
	}
}
long long Sum(int end){
	long long sum = 0;
	while(end > 0){
		sum = (sum + c[end]) % P;
		end -= Lowbit(end);
	}
	return sum;
}


int main()
{
	while (cin >> B >> P >> l >> n && B && P && l && n)
	{
		pb[0] = 1;
		for (int i = 1; i < MAX_L; i ++)
			pb[i] = (pb[i-1]*B) % P;

		memset(c, 0, sizeof(c));

		while ( n -- )
		{
			string Cmd;
			long long u, v;
			cin >> Cmd >> u >> v;
			if (Cmd[0] == 'E')
			{
				ll bb = Sum(u) - Sum(u-1);
				Plus(u, -bb);
				Plus(u, (pb[l-u]*v)%P);
			}
			else
			{
				ll re = sPow(pb[l-v], P-2, P);
				ll ans = (((Sum(v) - Sum(u-1) + P) % P ) * re ) % P;
				cout << ans << endl;
			}
		}
		cout << "-" << endl;
	}
}
