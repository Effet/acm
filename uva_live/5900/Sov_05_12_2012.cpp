#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;
vector<pair<ll,ll> >p;

void get_ans(ll m) {
    p.clear();
	for (ll k = 26; k >= 1; -- k) {
		double x = pow(m, 1.0/k);
		for (int i = 1; i <= k; ++ i) {
			x *= pow(i, 1.0/k);
		}

        ll a = max((ll)x-k, k+1);

        // cout << "a: " << a << endl;
        
		ll n = -1;
		for (int d = 0; ; ++ d) {
			ll y = 1;
            
			for (ll i = 1; i <= k; ++ i) {
				y = y*(a+d+i-1)/i;
				if (y > m)
                    break;
            }
            if (y > m)
                break;
            else {
                if (y == m) {
                    n = a + k -1 + d;
                }
            }
		}
		if (n != -1) {
            // cout << n << " " << n - k + 1 << endl;
            p.push_back(pair<ll,ll>(n,k) );
            if (n != k*2)
                p.push_back(pair<ll,ll>(n,n-k) );
        }
	}
    printf("%d\n", p.size() );
    for (int i = 0; i < p.size(); ++ i)
    {
        if (i != 0)
            putchar(' ');
        
        printf("(%lld,%lld)", p[i].first, p[i].second);
    }
    if (p.size() != 0)
        putchar('\n');
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		ll m;
		cin >> m;
		get_ans(m);
	}
	return 0;
}
