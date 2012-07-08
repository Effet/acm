#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int l, r, tmp;
        scanf("%d/%d", &l, &r);
        while (!(l==1&&r==1)) {
            if (l < r) {
                putchar('L');
                // (l,r) = (r-l,l)
                tmp = l;
                l = r - l;
                r = tmp;
            }
            else {
                putchar('R');
                // (l,r) = (r,l-r)
                tmp = r;
                r = l - r;
                l = tmp;
            }
        }
        putchar('\n');
    }
    return 0;
}
