#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#define pow2(x) ((x)*(x))

const int loop = 53;
const int rng = 51;
const int MAX_N = loop * 2 + 3;
const int MAX_P_N = MAX_N * MAX_N + 10;


bool vis[MAX_P_N];

void init_prime() {
    for (int i = 3; i < MAX_P_N; i += 2) {
        vis[i] = true;
        vis[i-1] = false;
    }
    vis[2] = true;
    for (int i = 3; i * i < MAX_P_N; i += 2) {
        int k = i * 2;
        int t = k + i;
        while (t < MAX_P_N) {
            vis[t] = false;
            t += k;
        }
    }
    // for (int i = 1; i < 10; ++ i)
    //     cout << vis[i] << " ";
    // cout << endl;
}


bool mmp[MAX_N][MAX_N];

void build_map() {
    init_prime();
    
    mmp[loop][loop] = false;
    int cur = 2;
    for (int i = 1; i < loop; ++ i) {
        for (int j = loop+i-1; j >= loop-i; -- j) mmp[j][loop+i] = vis[cur++];
        for (int j = loop+i-1; j >= loop-i; -- j) mmp[loop-i][j] = vis[cur++];
        for (int j = loop-i+1; j <= loop+i; ++ j) mmp[j][loop-i] = vis[cur++];
        for (int j = loop-i+1; j <= loop+i; ++ j) mmp[loop+i][j] = vis[cur++];
    }
    // for (int i = 0; i <= loop*2; ++ i) {
    //     for (int j = 0; j <= loop*2; ++ j)
    //         cout << mmp[i][j] << " ";
    //     cout << endl;
    // }
}


pair<int,int> get_pos(int xx) {
    if (xx == 1)
        return pair<int,int>(loop,loop);
    
    int b = int(sqrt(xx+0.0));
    if (!(b&1))
        -- b;

    if (xx == b*b)
        return pair<int,int>(loop+(b-1)/2,loop+(b-1)/2);

    int p = (xx- pow2(b) -1)/(b + 1);
    int r = (xx- pow2(b) -1)%(b + 1);

    // cout << endl << xx << endl;
    // cout << "p:r " << p << " " << r << endl;

    int i = (b+1)/2;

    int x, y;
    if (p == 0) {
        x = loop+i-1 - r;
        y = loop+i;
    } else if (p == 1) {
        x = loop-i;
        y = loop+i-1 - r;
    } else if (p == 2) {
        x = loop-i+1 + r;
        y = loop-i;
    } else {
        x = loop+i;
        y = loop-i+1 + r;
    }

    return pair<int,int>(x,y);
}

struct node {
    int x, y, c;
};

bool vis2[MAX_N][MAX_N];
int vr[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

node q[MAX_P_N];
int l, r;

int bfs(pair<int,int> stt, pair<int,int> dest) {

    // cout << stt.first << " " << stt.second << " : " << dest.first << " " << dest.second << endl;
    
    memset(vis2, false, sizeof(vis2));
    node cur;
    cur.x = stt.first;
    cur.y = stt.second;
    cur.c = 0;
    
    // queue<node>q;    
    // q.push(cur);
    l = r = 0;
    q[r++] = cur;
    
    vis2[cur.x][cur.y] = true;
    
    // while (!q.empty()) {
    while (l < r) {
        // cur = q.front();
        // q.pop();
        cur = q[l++];
        if (cur.x == dest.first && cur.y == dest.second)
            return cur.c;
        
        for (int i = 0; i < 4; ++ i) {
            node nxt = cur;
            nxt.x += vr[i][0];
            nxt.y += vr[i][1];
            nxt.c ++;
            
            if (!vis2[nxt.x][nxt.y] && !mmp[nxt.x][nxt.y] &&
                nxt.x >= loop-rng && nxt.x <= loop+rng && nxt.y >= loop-rng && nxt.y <= loop+rng) {
                vis2[nxt.x][nxt.y] = true;
                // q.push(nxt);
                q[r++] = nxt;
            }
        }
    }
    
    return -1;
}

int main(int argc, char *argv[])
{
    build_map();
    int x, y;
    int cas = 1;
    while (cin >> x >> y)
    {
        int ans = bfs(get_pos(x),get_pos(y));
        cout << "Case " << cas++ << ": ";
        if (ans == -1)
            cout << "impossible" << endl;
        else
            cout << ans << endl;
    } 

    return 0;
}
