#include <iostream>
using namespace std;

typedef long long ll;

const int MAX_N = 1000000;
const ll MOD = 1000000007;

ll dp[MAX_N + 100];

void pre_ans() {
    dp[0] = 1;
    dp[1] = 2;
    dp[2] = 9;
    for (int x = 3; x <= MAX_N; ++ x) {
        dp[x] = (dp[x-1]*3 + dp[x-2]*3 - dp[x-3] + MOD)%MOD;
    }
}

int main() {
    pre_ans();
    int t;
    cin >> t;
    while (t --) {
        int n;
        cin >> n;
        cout << dp[n] << endl;;
    }
    return 0;
}
