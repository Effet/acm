#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        vector<int> a(52);
        for (int i = 0; i < 52; ++ i)
            cin >> a[i];
        int N, L, R;
        cin >> N >> L >> R;
        int T = R / gcd(R, R-L+1);
        int pos = R - (R-L+1) * (N % T) % R;
        // cout << pos << endl;

        rotate(a.begin(), a.begin()+pos, a.begin()+R);
        
        cout << "Case #" << cas << ": ";
        for (int i = 0; i < 52; ++ i)
        {
            cout << a[i];
            if (i < 52 - 1)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}
