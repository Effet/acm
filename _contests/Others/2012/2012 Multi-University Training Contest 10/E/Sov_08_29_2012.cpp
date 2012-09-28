#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

typedef long long LL;

const int MAX_N = 1000;

LL get_n(string n)
{
    // cout << "n : "<< n << endl;
    int k = n.size();
    LL r = n[0] - '0';
    for (int i = 1; i < k; ++ i)
        r = r * 10 + n[i] - '0';
    return r;
}

int z[MAX_N];
int a[MAX_N];
int k;
LL m;

void do_opt()
{
    LL mm = z[k-1];
    for (int i = k - 2; i >= 0; -- i)
        mm = mm * 10 + z[i];

    // cout << "mm: " << mm << endl;
    if (m == -1)
        m = mm;
    else
        m = min(m, mm);
}

void dfs(int i, int add)
{
    // cout << "i, add: "<< i << " " << add << endl;
    if (i == k)
    {
        do_opt();
        return ;
    }
    // cout << "i, add: "<< i << " " << add << endl;
    
    // for (int j = 0; j <= i; ++ i)
    LL sum = 0;
    for (int j = 1; j < i; ++ j)
        sum += z[j] * z[i-j];
    
    for (int j = 0; j < 10; ++ j)
    {
        // cout << j << endl;
        if ((j * z[0] * 2 + sum + add) % 10 == a[i])
        {
            z[i] = j;
            // cout << "i, j: " << i << " " << j << endl;
            dfs(i + 1, (j * z[0] * 2 + sum + add) / 10);
        }
    }
}

LL get_z(string n)
{
    k = n.size();
    for (int i = 0; i < k; ++ i)
        a[i] = n[k-1-i] - '0';

    m = -1;
    for (int i = 0; i < 10; ++ i)
    {
        if (i * i % 10 == a[0])
        {
            z[0] = i;
            dfs(1, i * i / 10);
        }
    }
    
    return m;
}

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        string n;
        cin >> n;
        LL m = get_z(n);
        
        if (m != -1)
            cout << m << endl;
        else
            cout << "None" << endl;
    }
    return 0;
}
