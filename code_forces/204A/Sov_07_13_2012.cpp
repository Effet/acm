#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

ll y[25];
ll t[25];

void init()
{
    y[0] = 0;
    y[1] = 9;
    y[2] = 9 + 9;
    t[3] = 10;
    for (int i = 3; i <= 19; ++ i) {
        y[i] = 9*t[i] + y[i-1];
        t[i+1] = t[i]*10;
    }
    // for (int i = 0; i < 18; ++ i)
    //     cout << y[i] << " ";
    // cout << endl;
    // for (int i = 0; i < 18; ++ i)
    //     cout << t[i] << " ";
    // cout << endl;
}

ll get_ans(char *s)
{
    int len = strlen(s);

    if (len == 1)
        return (s[0]-'0');
    else if (len == 2)
    {
        if (s[0] > s[1])
            return (s[0] - '0' - 1) + 9;
        else
            return (s[0] - '0') + 9;
    }
    else
    {
        ll ans = y[len-1] + t[len]*(s[0]-'0'-1);
        ll x = 0;
        for (int i = 1; i < len - 1; ++ i)
            x = x*10 + s[i]-'0';
        
        ans += x + 1;
        if (s[len-1] < s[0])
            -- ans;
        return ans;
    }
}

int main(int argc, char *argv[])
{
    init();
    char a[25], b[25];
    while (cin >> a >> b)
    {
        ll ans = get_ans(b) - get_ans(a);
        // cout << get_ans(b) << " " << get_ans(a) << endl;
        int len = strlen(a);
        if (a[0] == a[len-1])
            ++ ans;
        // cout << get_ans(b) << " " << get_ans(a) << endl;
        cout << ans << endl;
    }
    return 0;
}
