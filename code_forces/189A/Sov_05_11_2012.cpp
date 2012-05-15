#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    int n, a, b, c;
    while (scanf("%d%d%d%d", &n, &a, &b, &c) != EOF) {
        int ans = -1;
        for (int i = 0; i <= n/a; ++ i)
            for (int j = 0; j <= (n-i*a)/b; ++ j)
            {
                if ( (n - i*a - j*b) % c == 0 )
                {
                    ans = max(ans, i + j + (n - i*a - j*b)/c);
                }
            }
        cout << ans << endl;
    }
    return 0;
}
