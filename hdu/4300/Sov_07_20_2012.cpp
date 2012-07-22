#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

//来源及参考:http://www.matrix67.com/blog/archives/115
//（基于算法导论介绍的KMP算法）


const int MAX_LEN = 1000000 + 100;

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
    int i = n / 2 + 1;
    
    if (n & 1)
        ++ i;
    
    int j = 0;
    for (; i <= n; ++ i)
    {
        while (j > 0 && P[j+1] != T[i]) j = pre[j];
        if ( P[j+1] == T[i] ) ++ j;
        if ( j == m )
        {
            // printf("Preattern occurs with shift %d\n", i - m);
            j = pre[j];
        }
        // cout << "i, j :" << i << " " << j << endl;
        // cout << T[i] << " " << P[j] << endl;
    }
    return j;
}

char table[30], table2[30];
char str1[MAX_LEN];
char str2[MAX_LEN];
int n;

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t --)
    {
        cin >> table >> str2 + 1;

        for (int i = 0; i < 26; ++ i)
            table2[table[i]-'a'] = i + 'a';
        
        n = strlen(str2+1);
        for (int i = 1; i <= n; ++ i)
            str1[i] = table[str2[i]-'a'];
        str1[n+1] = '\0';

        // cout << str1+1 << endl << str2+1 << endl;

        make_prefix(str2, n);

        // for (int i = 1; i <= n; ++ i)
        //     cout << pre[i] << ' ';
        // cout << endl;
        
        int len2 = KMP(str1, n, str2, n);

        int len1 = n - len2;
        
        for (int i = 1; i <= len1; ++ i)
            cout << str2[i];
        for (int i = 1; i <= len1; ++ i)
            cout << table2[str2[i]-'a'];

        cout << endl;
    }
    return 0;
}
