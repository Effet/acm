#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

int main() {
    int w, h;
    while (scanf("%d%d", &w, &h) != EOF) {
        ll l = 0;
        for (int i = 2; i <= w; i += 2) {
            l += (ll)(w - i + 1);
        }
        ll r = 0;
        for (int i = 2; i <= h; i += 2) {
            r += (ll)(h - i + 1);
        }
        cout << l*r << endl;
//        printf("%d\n", l*r);
    }
    return 0;
}
