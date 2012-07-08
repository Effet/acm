#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 100;

int n;
int max_a;
ll v[MAX_N];
ll v2[MAX_N];

int main() {
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++ cas) {
        scanf("%d", &n);
        memset(v, 0, sizeof(v));
        max_a = -1;
        for (int i = 0; i < n; ++ i) {
            int ai;
            ll xi;
            scanf("%d%lld", &ai, &xi);
            v[ai] += xi;
            max_a = max(max_a, ai);
        }
        memset(v2, 0, sizeof(v2));
        v2[0] = v[0];
        for (int i = 1; i <= max_a; ++ i) {
            v2[i] = v[i] + v2[i-1]/2;
            v2[i-1] %= 2;
        }
        int last_p = -1;
        for (int i = max_a; i > 0; -- i) {
            
            if (v[i] % 2 == 0)
                v2[i-1] += (v2[i] - v[i])*2;
            else if (v2[i] > v[i]) {
                v2[i-1] += (v2[i] - v[i] - 1)*2;
                v[i-1] -= 2;
            } else {
                last_p = i;
                break;
            }
        }
        v2[0] %= 2;
        v2[last_p] = 0;
        
        printf("Case #%d: ", cas);

        ll r = 1;
        for (int i = 0; i <= last_p; ++ i) {
            if (v2[i] == 1) {
                v2[i] = r % 2;
                r /= 2;
            } else {
                v2[i] = (1+r)%2;
                r = (r + 1)/2;
            }
        }

        v2[last_p] = (v2[last_p] + 1)%2;

        int pos = last_p;
        for (; pos >= 0; -- pos) {
            if (v2[pos] != 0) {
                for (int i = pos; i >= 0; -- i)
                    printf("%lld", v2[i]);
                break;
            }
        }
        
        if (pos < 0)
            printf("0");
        printf("\n");
    }
    return 0;
}
