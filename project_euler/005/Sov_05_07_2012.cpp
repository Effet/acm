#include <iostream>
using namespace std;

int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
}
int lcm(int a, int b) {
    return a/gcd(a,b)*b;
}

int main()
{
    int ans = 1;
    for (int i = 2; i <= 20; ++i)
        ans = lcm(ans, i);
    cout << ans << endl;
}
