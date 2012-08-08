#include <iostream>
#include <cstring>
using namespace std;


//来源及参考:http://www.matrix67.com/blog/archives/115
//（基于算法导论介绍的KMP算法）


const int MAX_LEN = 10000000 + 10;

int pre[MAX_LEN];
// pre[j] is max-number satisfy ``P[1 .. pre[j]] = P[[j-pre[j]+1 .. j]''.
// String P[1 .. n].
void make_prefix(char *P, int m)
{
   pre[1] = 0;
   for (int i = 2, j = 0; i <= m; ++ i)
   {
      while (j > 0 && P[j+1] != P[i]) j = pre[j];
      if (P[j+1] == P[i]) ++ j;
      pre[i] = j;
   }
}

// String T[1 .. n], P[1 .. m].
int KMP(char *T, int n, char *P, int m)
{
    int r = 0;
   for (int i = 1, j = 0; i <= n; ++ i)
   {
      while (j > 0 && P[j+1] != T[i]) j = pre[j];
      if ( P[j+1] == T[i] ) ++ j;
      r = max(r, j);
      if ( j == m )
          break;
   }
   return r;
}

char str[MAX_LEN];
char str2[MAX_LEN];

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> str + 1;
        n = strlen(str + 1);
        make_prefix(str, n);
        for (int i = 1, j = n; i <= n; ++ i, -- j)
            str2[i] = str[j];
        int ans = KMP(str2, n, str, n);

        for (int i = ans; i >= 1; -- i)
            cout << str[i];
        cout << endl;

    }
    return 0;
}
