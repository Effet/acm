#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

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

int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
}

int main() {
    initPrime();
    int t;
    cin >> t;
    while (t --) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a > b)
            swap(a,b);
        if (c > d)
            swap(c,d);
        int all = (b-a+1)*(d-c+1);
        int ok = 0;
        for (int i = a; i <= b; ++ i) {
            for (int j = c; j <= d; ++ j) {
                if (i == 0 && j == 0)
                    continue;
                if (i == 0 || j == 0) {
                    int x = abs(i+j);
                    if (vis[x] && x >= 3 && (x-3)%4==0)
                        ++ ok;
                } else {
                    if (vis[i*i+j*j])
                        ++ ok;
                }
            }
        }
        int g = gcd(ok,all);
        cout << ok/g << "/" << all/g << endl;
    }
    return 0;
}
