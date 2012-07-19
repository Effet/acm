//来源及参考:http://www.matrix67.com/blog/archives/115
//（基于算法导论介绍的KMP算法）


const int MAX_LEN = 100000 + 10;

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
void KMP(char *T, int n, char *P, int m)
{
   for (int i = 1, j = 0; i <= n; ++ i)
   {
      while (j > 0 && P[j+1] != T[i]) j = pre[j];
      if ( P[j+1] == T[i] ) ++ j;
      if ( j == m )
      {
         printf("Preattern occurs with shift %d\n", i - m);
         j = pre[j];
      }
   }
}
