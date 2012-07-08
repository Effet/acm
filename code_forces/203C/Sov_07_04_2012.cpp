#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 100;

vector<pair<int, int> > v;

int main() {
    int n, d, a, b;
    cin >> n >> d >> a >> b;
    v.clear();
    for (int i = 1; i <= n; ++ i) {
        int x, y;
        cin >> x >> y;
        v.push_back(pair<int,int>(a*x+b*y,i));
    }
    sort(v.begin(), v.end());
    // for (int i = 0; i < n; ++ i)
    //     cout << v[i].first <<  " " << v[i].second << endl;
    int cur = 0;
    while (d >= v[cur].first && cur < n) {
        d -= v[cur++].first;
    }
    cout << cur << endl;
    for (int i = 0; i < cur; ++ i) {
        cout << v[i].second << " ";
    }
    cout << endl;
    return 0;
}
        
