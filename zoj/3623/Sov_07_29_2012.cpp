#include <iostream>
#include <climits>
#include <cmath>
#include <map>
using namespace std;

const int MAX_N = 30 + 10;
const int MAX_L = 330 + 10;

struct boss {
    int t, l;
}b[MAX_N];

map<int,int> m;

int n, L;

int dfs(int len, int spd)
{
    if (m.find(len*1000+spd) != m.end())
        return m[len*1000+spd];
    
    if (len <= 0)
        return 0;
    
    int ret = INT_MAX;
    for (int i = 0; i < n; ++ i)
    {
        if (len >= b[i].t*spd)
            ret = min(ret, b[i].t + dfs(len - b[i].t*spd, spd + b[i].l));
        else
            ret = min(ret, (int)ceil((len+0.0)/spd));
    }
    
    return m[len*1000+spd] = ret;
}

int dp[MAX_L*10];

int main(int argc, char *argv[])
{
    while (cin >> n >> L)
    {
        for (int i = 0; i < n; ++ i)
            cin >> b[i].t >> b[i].l;

        m.clear();
        int ans =dfs(L, 0);
        
        cout << ans << endl;
    }
    return 0;
}
