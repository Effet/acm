#include <iostream>
#define mod 10000

int fibonacci(int n) {
   int ra,rb,a,b,x,y;
   if (n<2) return n;
   ra=rb=a=b=1;
   n-=2;
   while (n) {
      if (n&1) {
         x=ra*a+rb*b;
         y=ra*b+rb*(a-b+mod);
         ra=x%mod;rb=y%mod;
      }
      n>>=1;
      x=a*a+b*b;
      y=(2*a+mod)*b-b*b;
      a=x%mod;b=y%mod;
   }
   return ra;
}

int main() {
   for (int n;scanf("%d",&n),n!=-1;) {
      printf("%d\n",fibonacci(n));
   } return 0;
}
