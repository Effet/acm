#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_LEN = 25000 + 50;

char str[MAX_LEN];
int last[300];
int cnt[300];
bool vis[300];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        scanf("%s", str);

        memset(last, 0, sizeof(last));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < strlen(str); ++ i) {
            last[int(str[i])] = i;
            cnt[int(str[i])] += 1;
        }
        int ans = 0;
        int pos = strlen(str) - 1;
        int cur = pos;
        memset(vis, false, sizeof(vis));
        while (pos >= 0 && cur >= 0) {
            while (vis[str[cur]])
                -- cur;

            vis[str[cur]] = true;
            
            ans += (last[str[cur]] - pos)*cnt[str[cur]];
            pos -= cnt[str[cur]];
            if (pos < 0)
                break;
        }
        printf("%d\n", ans*5);
    }
    return 0;
}
