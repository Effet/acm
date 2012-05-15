#include <iostream>
using namespace std;

int get_num(int sum) {
    for (int a = 0; a <= sum; ++ a)
        for (int b = a + 1; b <= sum; ++ b)
        {
            int c = sum - a - b;
            if (c <= b)
                continue;
            if (a*a + b*b == c*c)
                return a*b*c;
        }
    return -1;
}
            
int main() {
    cout << get_num(1000) << endl;
    return 0;
}
