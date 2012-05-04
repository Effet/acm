#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100 + 10;
int q[MAXN];
int top;
int bsearch( int x ){// 返回离散化后值 [0,n-1]
   int l = 0, r = top - 1, m;
   while( l <= r ){
      m = (l+r)>>1;
      if( q[m] == x )
         return m;
      else if( q[m] > x )
         r = m - 1;
      else
         l = m + 1;
   }
}

int main() {
   int n, x[MAXN];
   while ( cin >> n ) {
      for ( int i = 0; i < n; ++ i )
         cin >> x[i];

      // insert
      for ( int i = 0; i < n; ++ i )
         q[top++] = x[i];

      // 二分离散化
      sort( q, q+top );
      int j = 1;
      for ( int i = 1; i < top; ++ i )
         if ( q[i] != q[i-1] ) // 删除重复元素
            q[j++] = q[i];
      top = j;

      // 变更为离散化后的值
      for ( int i = 0; i < n; ++ i )
         x[i] = bsearch( x[i] );

      // 原来的值
      for ( int i = 0; i < n; ++ i )
         cout << q[x[i]] << ' ';
      cout << endl;

   }
   return 0;
}

