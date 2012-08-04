const int MAXN = 1000;

/* 找寻最近的大于n的位置 */
LL q[MAXN+10];
LL bsearch( LL n )
{
   LL l = 1, r = MAXN, m;
   LL t;
   while ( l < r )
   {
      m = (l+r)/2;
      if ( q[m] >= n )
      {
         if ( q[m-1] < n )
            return m;
         else
            r = m - 1;
      }
      else
         l = m + 1;
   }
   return l;
}

