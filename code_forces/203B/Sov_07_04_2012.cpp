#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 1000 + 100;
const int MAX_M = 100000 + 100;

int rect[MAX_N][MAX_N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(rect, 0, sizeof(rect));
    int ans = -1;
    for (int xx = 1; xx <= m; ++ xx) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (ans == -1) {
            x += 10; y += 10;
            rect[x][y] = 1;
            for (int i = x - 2; i <= x; ++ i) {
                for (int j = y - 3; j <= y; ++ j) {
                    int cnt = 0;
                    for (int ii = 0; ii < 3; ++ ii)
                        for (int jj = 0; jj < 3; ++ jj) {
                            if (rect[i+ii][j+jj] != 1)
                                break;
                            ++ cnt;
                        }
                    if (cnt == 9) {
                        ans = xx;
                        break;
                    }
                }
                if (ans != -1)
                    break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
