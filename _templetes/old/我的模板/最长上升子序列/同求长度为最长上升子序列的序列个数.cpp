#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int b[100005], p[100005];
int n, a[100005];
void fun() //传入n个数,a[]
{
   memset( p, 0, sizeof(p) );
   b[1]=a[0];
   int i;
   int begine=1,end=1;
   for(i=1;i<n;i++)
   {
      if(a[i]>b[end])
         b[++end]=a[i];
      else
      {
         int x=begine,y=end;
         while(x<y)
         {
            int mid=(x+y)/2;
            if(b[mid]>=a[i])
               y=mid;
            else
               x=mid+1;
         }
         b[y]=a[i];
         if ( p[y-1]>0 || y == 1 )
            ++ p[y];
      }
   }
   //   for ( int i=1; i<=end; i++ ){
   //      printf( " %d", p[i] );
   //   }
   //   printf( "\n" );
   printf("%d\n%d\n",end, p[end]+1); //输出最长上升子序列的长度

}

int main() {
   while ( scanf( "%d", &n ) != EOF ) {
      for ( int i=0; i<n; i++ ){
         scanf( "%d", &a[i] );
      }
      fun( );
   }
   return 0;
}

