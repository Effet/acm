#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


const int MAX_N = 100 + 10;
const int MAX_M = 200 + 10;


int n;
int val[MAX_N];
int dp[MAX_N][MAX_M];
int s, m;
vector<pair<int,int> > e[MAX_N];
bool vis[MAX_N];


void dfs(int u)
{
    dp[u][0] = val[u];
    for (int i = 0; i < e[u].size(); ++ i)
    {
        int v = e[u][i].first;
        int nxt_v = e[u][i].second;
        if (!vis[v])
        {
            vis[v] = true;
            dfs(v);
            for (int j = m; j >= 0; -- j)
                for (int cost = nxt_v; cost <= j; ++ cost)
                    dp[u][j] = max(dp[u][j], dp[u][j-cost] + dp[v][cost-nxt_v]);
        }
    }
}


int main()
{
    while (cin >> n)
    {
        for (int i = 1; i <= n; ++ i)
            cin >> val[i];

        for (int i = 1; i <= n; ++ i)
            e[i].clear();
        
        for (int i = 1; i <= n - 1; ++ i)
        {
            int x, y, t;
            cin >> x >> y >> t;
            e[x].push_back(make_pair(y, t*2));
            e[y].push_back(make_pair(x, t*2));
        }
        cin >> s >> m;

        memset(vis, false, sizeof(vis));
        memset(dp, 0, sizeof(dp));
        vis[s] = true;
        dfs(s);

        int ans = 0;
        for (int i = 0; i <= m; ++ i)
            ans = max(ans, dp[s][i]);
        
        cout << ans << endl;
    }
    return 0;
}
