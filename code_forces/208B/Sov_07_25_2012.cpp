#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int MAX_N = 52 + 3;

struct node
{
    char a, b;
} x[MAX_N];

int n;
int mat[MAX_N][MAX_N];

set<string> s;

bool flag;
void dfs(int r)
{
    if (r == 0)
    {
        flag = true;
        return ;
    }

    if (flag)
        return ;

    for (int i = r - 1; i >= 0 && i >= r - 3; i -= 2)
    {
        if (flag)
            return ;
        
        if (x[i].a == x[r].a || x[i].b == x[r].b)
        {
            swap(x[i], x[r]);
            string str = "";
            for (int j = 0; j <= r - 1; ++ j)
                str += x[j].a + x[j].b;
            if (s.find(str) == s.end())
            {
                s.insert(str);
                dfs(r - 1);
            }
            swap(x[i], x[r]);
        }
    }
}

int main(int argc, char *argv[])
{
    cin >> n;
    for (int i = 0; i < n; ++ i)
    {
        char str[5];
        cin >> str;
        x[i].a = str[0];
        x[i].b = str[1];
    }

    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            if (x[i].a == x[j].a || x[i].b == x[j].b)
                mat[i][j] = 1;

    for (int k = 0; k < n; ++ k)
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                if (mat[i][k] && mat[k][j])
                    mat[i][j] = 1;

    flag = true;
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            if (mat[i][j] == 0)
                flag = false;

    if (flag == true)
    {
        flag = false;
        s.clear();
        dfs(n - 1);
    }
    
    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
