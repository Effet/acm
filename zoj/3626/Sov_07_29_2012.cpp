#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX_N = 300 + 10;
const int MAX_M = 300 + 10;

int n;
int val[MAX_N];
int dp[MAX_N][MAX_M];
int sum[MAX_N][MAX_M];
int s, m;
vector<pair<int,int> > e[MAX_N];
bool vis[MAX_N];

void dfs(int u, int pre_v)
{
    vector<int> son;
    for (int i = 0; i < e[u].size(); ++ i)
    {
        int v = e[u][i].first;
        int nxt_v = e[u][i].second;
        if (!vis[v])
        {
            vis[u] = true;
            son.push_back(v);
            dfs(v, nxt_v);
        }
    }

    for (int i = 0; i <= m; ++ i)
        dp[u][i] = 0;
    
    if (son.size() == 0)
    {
        if (pre_v <= m)
            dp[u][pre_v] = val[u];

        // cout << u << ": ";
        // for (int i = 0; i <= m;  ++ i)
        //     cout << dp[u][i] << " ";
        // cout << endl;
        return ;
    }

    memset(sum, 0, sizeof(sum));
    
    for (int j = 0; j <= m; ++ j)
        sum[0][j] = dp[son[0]][j];
    for (int i = 1; i < son.size(); ++ i)
    {
        // int v = son[i];
        for (int j = 0; j <= m; ++ j)
        {
            for (int k = 0; k <= j; ++ k) {
                // if (j == 4 && k == 2)
                //     cout << sum[i-1][k] << " " << dp[son[i]][j-k] << endl;
                sum[i][j] = max(sum[i][j], sum[i-1][k] + dp[son[i]][j-k]);
            }
        }
    }
    
    for (int j = pre_v; j <= m; ++ j)
        dp[u][j] = sum[son.size()-1][j-pre_v] + val[u];

    // cout << u << ": ";
    // for (int i = 0; i <= m;  ++ i)
    //     cout << dp[u][i] << " ";
    // cout << endl;

}

int main(int argc, char *argv[])
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
        vis[s] = true;
        dfs(s, 0);

        int ans = 0;
        for (int i = 0; i <= m; ++ i)
            ans = max(ans, dp[s][i]);
        
        cout << ans << endl;
    }
    return 0;
}
