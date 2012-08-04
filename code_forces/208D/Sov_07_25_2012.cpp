#include <iostream>
using namespace std;

typedef long long ll;

int main(int argc, char *argv[])
{
    int n;
    ll a[50], b[5], c[5] = {0};
    
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> a[i];
    for (int i = 0; i < 5; ++ i)
        cin >> b[i];

    ll rem = 0;
    for (int i = 0; i < n; ++ i)
    {
        a[i] += rem;
        rem = 0;
        for (int j = 4; j >= 0; -- j)
        {
            if (a[i] >= b[j])
            {
                c[j] += a[i] / b[j];
                a[i] %= b[j];
            }
        }
        rem += a[i];
    }

    for (int j = 4; j >= 0; -- j)
    {
        if (rem >= b[j])
        {
            c[j] += rem / b[j];
            rem %= b[j];
        }
    }

    for (int i = 0; i < 5; ++ i)
        cout << c[i] << " ";
    cout << endl;
    cout << rem << endl;
        
    return 0;
}
