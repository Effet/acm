#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    int t;
    cin >> t;
    while (t --) {
        ll c, d;
        cin >> c >> d;
        ll sum = c+d;
        if (c & ~d)
            cout << -1 << endl;
        else {
            ll x = ~c & d;
            ll delt;
            if (x == 0)
                delt = 0;
            else {
                ll xx = x;
                ll ten = 1;
                while (xx != 1) {
                    xx /= 2;
                    ten *= 2;
                }
                delt = ten - (x - ten);
            }
            // cout << sum << " " << delt << endl;
            if ((sum -delt)%2 || (sum-delt)%2)
                cout << -1 << endl;
            else
                cout << (sum-delt)/2 << " " << (sum+delt)/2 << endl;
        }
    }
    return 0;
}
