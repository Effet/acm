#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX_LEN = 1000000 + 10;

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


char str[MAX_LEN];

int main()
{
   // Use str[1 .. n].
   while(scanf("%s", str + 1) != EOF)
   {
       if (str[1] == '.')
           break;

       int n = strlen(str + 1);
       make_prefix(str, n);
       
       if(n % (n - pre[n]) == 0 && n/(n - pre[n]) >= 2)
           printf("%d\n", n/(n-pre[n]));
       else
           printf("%d\n", 1);
   }
   return 0;
}
