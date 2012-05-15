#include <iostream>
using namespace std;

int main() {
    int pre = 1, sec = 2, now = 3;
    int limit = 4000000;
    long long ans = 2;
    while (now <= limit) {
        if (now % 2 == 0)
            ans += (long long)now;
        pre = sec;
        sec = now;
        now = pre + sec;
    }
    cout << ans << endl;
    return 0;
}
