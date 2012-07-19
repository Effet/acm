#include <iostream>
using namespace std;

const int MAX_N = 50000 + 100;

int mat[MAX_N];
int ans[MAX_N];

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        int r, c;
        cin >> r >> c;
        for (int i = 0; i < r; ++ i)
            for (int j = 0; j < c; ++ j)
                cin >> mat[i*c + j];

        int flag = 0;
        for (int i = 0; i < r; ++ i)
            for (int j = 0; j < c; ++ j)
                if ( ((r-1-i) + (c-1-j)) % 2 == 1)
                    flag ^= mat[i*c + j];

        cout << "Case " << cas << ": ";
        if (flag == 0)
            cout << "lose" << endl;
        else
            cout << "win" << endl;
    }
    return 0;
}
