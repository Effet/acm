#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX_N = 1000 + 10;

int n, m;
int a[MAX_N], b[MAX_N];

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; ++ i)
            cin >> a[i];
        cin >> m;
        for (int i = 0; i < m; ++ i)
            cin >> b[i];

        int ans = INT_MAX;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
                ans = min(ans, abs(a[i] - b[j]));
        cout << ans << endl;
    }
    return 0;
}
