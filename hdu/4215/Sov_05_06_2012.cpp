#include <iostream>
using namespace std;

typedef long long ll;

int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
}

int e[100];
int f[100];
int x[100];
void init()
{
    e[0] = f[0] = 0;
    for (int i = 1; i < 30; ++ i)
    {
        e[i] = e[i-1];
        f[i] = f[i-1];
        for (int j = 1; j <= i; ++ j)
        {
            if (gcd(i, j) == 1)
                ++ e[i];
            if (i  %j == 0)
                ++ f[i];
        }
    }
    for (int i = 1; i < 30; ++ i)
    {
        x[i] = 0;
        for (int a = 1; a <= i; ++ a)
            for (int b = a; b <= i; ++ b)
                if (f[b]-f[a-1] == e[b]-e[a-1])
                    ++ x[i];
    }
}
                    

int main()
{
    init();
    int t;
    cin >> t;
    int cls;
    while (t--)
    {
        ++ cls;
        ll n;
        cin >> n;
        cout << "Case " << cls << ": ";
        if (n < 30)
            cout << x[n] << endl;
        else
            cout << 10 << endl;
    }
    return 0;
}
