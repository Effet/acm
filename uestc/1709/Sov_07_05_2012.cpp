#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAX_N = 500000 + 100;
const int MAX_LEN = 34;

int n;
ll a[MAX_N];


// 0:and, 1:or, 2:xor
ll gether_ans(int sig) {
    int m[MAX_LEN];
    for (int i = 0; i < MAX_LEN; ++ i)
        m[i] = 0;
    
    ll sum = 0;
    for (int i = 0; i < n; ++ i) {
        ll x = a[i];
        for (int j = 0; j < MAX_LEN; ++ j) {
            if (sig == 0) {
                if (x % 2)
                    m[j] += 1;
                else
                    m[j] = 0;
            } else if (sig == 1) {
                if (x % 2)
                    m[j] = i + 1;
            } else {
                if (x % 2)
                    m[j] = i - m[j] + 1;
            }
            x /= 2;
        }
        ll y = 0;
        for (int j = MAX_LEN - 1; j >= 0; -- j)
            y = y*2 + (ll)m[j];
        sum += y;
    }
    return sum;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++ cas) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i)
            scanf("%lld", &a[i]);

        ll cnt = (ll)(1+n)*n/2;

        ll p1 = gether_ans(0);
        ll p2 = gether_ans(1);
        ll p3 = gether_ans(2);

        printf("Case #%d: %.6lf %.6lf %.6lf\n", cas, (double)p1/cnt, (double)p2/cnt, (double)p3/cnt);
    }
    return 0;
}
