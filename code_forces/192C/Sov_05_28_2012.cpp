#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

    
int main() {
    int n, dp[28][28];
    char str[12];
    while (scanf("%d", &n) != EOF) {
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for (int i = 0; i < n; ++ i) {
            scanf("%s", str);
            int len = strlen(str);
            int a = str[0] - 'a';
            int c = str[len-1] - 'a';
            for (int b = 0; b < 26; ++ b) {
                if (dp[b][a] > 0) {
                    dp[b][c] = max(dp[b][c],dp[b][a]+len);
                }
                if (b == c)
                    ans = max(ans, dp[b][c]);
            }
            dp[a][c] = max(dp[a][c], len);
            if (a == c)
                ans = max(ans, dp[a][c]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
 
