#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
using namespace std;

typedef long long ll;

map<ll,ll> mm;
const int limit = 1000000;

ll get_3n_p_1(ll n) {
    map<ll,ll>::iterator it = mm.find(n);
    if (it != mm.end() )
        return it->second;
    else {
        ll nxt = (n%2==0)?n/2:3*n+1;
        ll len = get_3n_p_1(nxt) + 1;
        mm.insert(pair<ll,ll>(nxt,len) );
        return len;
    }
}

int main() {
    mm.clear();
    mm.insert(pair<ll,ll>((ll)1,(ll)1) );
    int ans = 1;
    ll len_m = -1;
    for (int i = 2; i <= limit; ++ i) {
        ll len = get_3n_p_1( (ll)i );
        // cout << i << " " << len << endl;
        if (len > len_m) {
            len_m = len;
            ans = i;
        }
    }
    // cout << len_m << endl;
    cout << ans << endl;
    return 0;
}
