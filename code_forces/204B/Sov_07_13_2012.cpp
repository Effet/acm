#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX_N = 100000 + 100;

map<int,int> m;
int c_front[MAX_N*2], c_back[MAX_N*2], c_same[MAX_N*2];

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        m.clear();
        memset(c_front, 0, sizeof(c_front));
        memset(c_back, 0, sizeof(c_back));
        memset(c_same, 0, sizeof(c_same));
        int cnt = 0;
        for (int i = 0; i < n; ++ i) {
            int x, y;
            int ix, iy;
            cin >> x >> y;
            if (m.find(x) == m.end())
            {
                m.insert(make_pair(x, cnt));
                ix = cnt;
                ++ cnt;
            }
            else
            {
                ix = m[x];
            }

            if (m.find(y) == m.end() )
            {
                m.insert(make_pair(y, cnt));
                iy = cnt;
                ++ cnt;
            }
            else
            {
                iy = m[y];
            }

            c_front[ix] ++;
            c_back[iy] ++;
            if (x == y)
                c_same[ix] ++;
        }


        // cout << cnt << endl;
        // for (int i = 0; i < cnt; ++ i)
        //     cout << c_front[i] << " ";
        // cout << endl;

        
        int least = n/2;
        if (n & 1)
            ++ least;

        int ans = MAX_N;
        for (int i = 0; i < cnt; ++ i) {
            if (c_front[i] * 2 >= n)
            {
                ans = 0;
                break;
            }
            else
            {
                if ( (c_front[i] + c_back[i] - c_same[i])  < least)
                {
                    continue;
                }
                else
                {
                    ans = min(ans, least - c_front[i]);
                }

            }
        }
        if (ans == MAX_N)
            cout << -1 << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
