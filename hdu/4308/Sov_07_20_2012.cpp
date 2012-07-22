#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef long long ll;

const int MAX_N = 5000 + 5;

int r, c, cost;
char mat[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
struct point {
    int i, j;
    ll cost;
    bool operator <(const point &a) const {
        return cost > a.cost;
    }
} Y, C, p[5000*600];
int top;

// queue<point> q;

priority_queue<point> q;
int vr[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

ll bfs()
{
    top = 0;
    for (int i = 0; i < r; ++ i)
        for (int j = 0; j < c; ++ j)
        {
            if (mat[i][j] == 'Y')
                Y.i = i, Y.j = j, Y.cost = 0;
            if (mat[i][j] == 'C')
                C.i = i, C.j = j;
            if (mat[i][j] == 'P')
            {
                p[top].i = i; p[top].j = j;
                ++ top;
            }
        }

    // cout << Y.i << " " << Y.j << endl;
    // cout << C.i << " " << C.j << endl;

    while (!q.empty())
        q.pop();

    memset(vis, false, sizeof(vis));
    q.push(Y);
    
    struct point cur, nxt;
    while (!q.empty())
    {
        cur = q.top();
        // cout << "cur : "<< cur.i << " " << cur.j << endl;
        q.pop();
        vis[cur.i][cur.j] = true;
        if (cur.i == C.i && cur.j == C.j)
            return cur.cost;
        for (int i = 0; i < 4; ++ i)
        {
            nxt = cur;
            nxt.i += vr[i][0];
            nxt.j += vr[i][1];
            if (nxt.i >= 0 && nxt.i < r && nxt.j >= 0 && nxt.j < c && !vis[nxt.i][nxt.j])
            {
                if (mat[nxt.i][nxt.j] == '#')
                    continue;
                
                if (mat[nxt.i][nxt.j] == 'P')
                    for (int j = 0; j < top; ++ j)
                    {
                        p[j].cost = cur.cost;
                        q.push(p[j]);
                    }
                else if (mat[nxt.i][nxt.j] == '*')
                {
                    nxt.cost += cost;
                    q.push(nxt);
                }
                else
                    q.push(nxt);
            }
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    while (scanf("%d%d%d", &r, &c, &cost) != EOF)
    {
        for (int i = 0; i < r; ++ i)
            scanf("%s", mat[i]);
        ll ans = bfs();
        if (ans == -1)
            printf("Damn teoy!\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
