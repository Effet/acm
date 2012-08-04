#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAX_N = 100 + 10;

int n;
struct node
{
    char s[100];
} a[MAX_N];

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int pos = -1;
        for (int i = 0; i < n; ++ i)
        {
            cin >> a[i].s;
            if (a[i].s[0] != '#')
                pos = i;
        }

        if (pos != -1)
        {
            for (int i = pos + 1; i < n; ++ i)
                cout << a[i].s << " ";
            cout << a[pos].s;
            if (pos == 0)
                cout << endl;
            else
                cout << " ";
            for (int i = 0; i < pos; ++ i)
            {
                cout << a[i].s;
                if (i == pos - 1)
                    cout << endl;
                else
                    cout << " ";
            }
        }
        else
        {
            for (int i = 0; i < n; ++ i)
            {
                cout << a[i].s;
                if (i == n - 1)
                    cout << endl;
                else
                    cout << " ";
            }
        }
    }
    return 0;
}
