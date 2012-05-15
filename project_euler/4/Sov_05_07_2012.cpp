#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

bool is_palindrome(int n) {
    string str;
    ostringstream out;
    out << n;
    str = out.str();
    for (int i = 0, j = str.size()-1; i < j; ++ i, -- j)
        if (str[i] != str[j])
            return false;
    return true;
}

int main() {
    int ans = -1;
    for (int i = 100; i <= 999; ++ i)
        for (int j = 100; j <= 999; ++ j)
            if ( is_palindrome(i*j) )
                ans = max(ans, i*j);
    cout << ans << endl;
    return 0;
}
