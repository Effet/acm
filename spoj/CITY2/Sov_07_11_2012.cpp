#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 100;

ll a[MAX_N];

struct cmp1 {
    bool operator() (ll &a, ll &b) {
        return a < b;           // big first
    }
};

priority_queue<ll, vector<ll>, cmp1> q;

int main(int argc, char *argv[])
{
    int n;
    int cas = 1;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++ i)
            scanf("%lld", &a[i]);
        a[0] = -1;
        
        int ans = 0;
        while (!q.empty())
            q.pop();
        
        for (int i = 1; i <= n; ++ i)
        {
            if (a[i] == 0)
            {
                while (!q.empty())
                    q.pop();
                continue;
            }
            
            if (a[i] > a[i-1])
            {
                ++ ans;
                q.push(a[i]);
            }
            else if (a[i] < a[i-1])
            {
                
                while (!q.empty() && q.top() > a[i])
                    q.pop();
                
                if (q.empty() || q.top() < a[i]) {
                    ++ ans;
                    q.push(a[i]);
                }
            }
        }
        
        printf("Case %d: ", cas++);
        printf("%d\n", ans);
    }
    return 0;
}
