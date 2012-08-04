#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;


typedef long long ll;
typedef struct node { ll cnt, val; } t_pair;
typedef struct node2 { t_pair x; int v, w; } f_tuple;


const int MAX_N = 300000 + 10;
const int MAX_VETX = MAX_N;
const int MAX_EDGE = MAX_N;


struct edge {int to, next, w;} E[MAX_EDGE];
int n, head[MAX_VETX];

void insert_edge(int i, int u, int v, int w)
{
    E[i].to   = v;
    E[i].w    = w;
    E[i].next = head[u];
    head[u]   = i;
}


int  val[MAX_N];
bool vis[MAX_N];

ll ans;
ll rock[MAX_N];
ll roll[MAX_N];

f_tuple lazy[MAX_N], tmp;
int lz_top;
int num[MAX_N], top;

t_pair dfs(int u, int pre)
{
    int orig = lz_top;
    for (int i = head[u]; i != -1; i = E[i].next)
    {
        int v = E[i].to;
        int w = E[i].w;

        if (vis[v]) continue;
        vis[v] = 1;
        
        tmp.x = dfs(v,w);
        tmp.v = v;
        tmp.w = w;
        lazy[lz_top++] = tmp;
    }
    
    ll sum_c = 0, sum_v = 0;
    top = 0;
    while (lz_top > orig)
    {
        f_tuple lz = lazy[--lz_top];
        
        t_pair x = lz.x;
        int v = lz.v;
        int w = lz.w;

        ll add_cnt = x.cnt + 1;
        ll add_val = x.val + add_cnt * val[u] + val[v];
        
        if (rock[w] == 0)
            num[top++] = w;

        rock[w] += add_cnt;
        roll[w] += add_val;

        sum_c += add_cnt;
        sum_v += add_val;
    }

    ll cut = 0, sum = 0;
    t_pair ret;
    ret.cnt = 0; ret.val = 0;
    for (int i = 0; i < top; ++ i)
    {
        int w = num[i];
        
        // cnt & val
        ll c = rock[w];
        ll v = roll[w];
        rock[w] = roll[w] = 0;

        if (w != pre)
        {
            ret.cnt += c;
            ret.val += v;
        }
        
        sum += v * (sum_c - c);
        cut += c * (sum_c - c);
    }
    sum -= cut * val[u] / 2;
    ans += sum_v + sum;
    
    return ret;
}


int main(int c, char *argv[])
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; ++ i)
            scanf("%d", &val[i]);

        memset(head, -1, sizeof(head[0])*(n+1));
        for (int i = 0; i < n - 1; ++ i)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            insert_edge(i, a, b, c);
            // insert_edge(i<<1,   a, b, c);
            // insert_edge(i<<1|1, b, a, c);
        }

        memset(vis, false, sizeof(vis[0])*(n+1));
        memset(rock, 0, sizeof(rock[0])*(n+1));
        memset(roll, 0, sizeof(roll[0])*(n+1));
        lz_top = 0;
        
        ans = 0;
        vis[1] = 1;
        dfs(1, -1);
        // printf("%I64d\n", ans);
        cout << ans << endl;
    }
    return 0;
}
