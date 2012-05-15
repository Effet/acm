#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string add(string a, string b) {
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    if (a.size() > b.size())
        swap(a,b);

    string c = "";
    int r = 0;
    for (int i = 0; i < a.size(); ++ i)
    {
        r += a[i]-'0'+b[i]-'0';
        c += r%10 + '0';
        r /= 10;
    }
    for (int i = a.size(); i < b.size(); ++ i)
    {
        r += b[i]-'0';
        c += r%10 + '0';
        r /= 10;
    }
    while (r > 0) {
        c += r%10 + '0';
        r /= 10;
    }
    reverse(c.begin(),c.end());

    return c;
}

int main() {
    string b = "1";
    for (int i = 1; i <= 1000; ++ i)
        b = add(b,b);
    cout << b << endl;
    long long ans = 0;
    for (int i = 0; i < b.size(); ++ i)
        ans += b[i]-'0';
    cout << ans << endl;
    return 0;
}
