#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

int i, l, k, a, b, T, t[555], A[555];
char s[555], d[555];
int main(){
   //freopen("in.txt", "r", stdin);
   for(scanf("%d", &T); T--;){
      scanf("%d%d%s", &a, &b, s);
      for(k = i = strlen(s); 0<i--;)
         t[k-1-i] = s[i]-(s[i]<58 ? 48 : s[i]<97 ? 55 : 61);
      for(l = 0; k;){
         for(i = k; 1<i--;){
            t[i-1] += t[i]%b*a;
            t[i] /= b;
         }
         A[l++] = t[0]%b;
         t[0] /= b;
         for(; 0<k&&!t[k-1]; k--);
      }
      for(d[l] = i = 0; i<l; i++)
         d[l-1-i] = A[i]+(A[i]<10 ? 48 : A[i]<36 ? 55 : 61);
      printf("%d %s\n%d %s\n\n", a, s, b, d);
   }
   return 0;
}
