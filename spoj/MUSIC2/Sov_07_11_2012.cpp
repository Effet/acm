#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    char a[5], b[15];
    int cas = 1;
    while (cin >> a >> b) {
        cout << "Case " << cas << ": ";

        if (strlen(a) == 1)
            cout << "UNIQUE" << endl;
        else {
            if (a[1] == '#') {
                char c = a[0] + 1;
                if (c > 'G')
                    c = 'A';
                cout << c << "b ";
            } else {
                char c = a[0] - 1;
                if (c < 'A')
                    c = 'G';
                cout << c << "# ";
            }
            cout << b << endl;
        }
        ++ cas;
    }
    return 0;
}
