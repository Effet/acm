//提一下，数组首地址减一的地址是未申请的地址，应该是非法的，
//但是在操作中并未有对这个非法地址以及地址中值的操作，
//这个地址只在数值上有用


//来源及参考:http://www.matrix67.com/blog/archives/115
//（基于算法导论介绍的KMP算法）
const int maxLen = 10000;

int pre[maxLen];
void computePrefix( char *P, int m )
{  /* pre[j]是所有满足P[1..pre[j]] = pre[j-pre[j]+1..j]的最大值 */
   pre[1] = 0; -- P;   /* 将数组向后移一位，即pre[0..m-1]变成pre[1..m]。*/
   for ( int i=2, j=0; i<=m; ++i ) {
      while ( j>0 && P[j+1] != P[i] ) { j = pre[j]; }
      if ( P[j+1] == P[i] ) j += 1;
      pre[i] = j;
   }
}

void KMP(char *T, int n, char *P, int m)
{
   -- T; -- P;
   for(int i=1, j=0; i<=n; ++i) {
      while ( j>0 && P[j+1] != T[i] ) { j = pre[j]; }
      if ( P[j+1] == T[i] ) j += 1;
      if ( j == m ) {
         printf("preattern occurs with shift %d\n", i-m);
         j = pre[j];
      }
   }

}


//下面是另一种解释，来源：浙大模板
//fail[j]代表了，在t串在j点失配时（s[i] != t[j]）
//应将t串j改变后的值，即t[1..fail[j]-1]仍是与s[i]匹配的，
//这时候就是试验s[i] 是否与 t[fail[j]]相匹配了，否则再递归操作。
const int maxlen = 1000;

int fail[maxlen];
void makefail( char *t, int lt )
{
    --t;
    for(int i=1,j=0;i<=lt;i++,j++){
        fail[i]=j;
        while(j>0 && t[i]!=t[j]) j=fail[j];
    }
}

// start matching pattern T in S[i..)
// return match pos or longest match length with corresponding pos
int kmp(char *s, int ls, char *t, int lt, int i,int &longest,int &lp)
{
    longest = lp = 0; --s; --t;
    for(int j=1; i<=ls; i++,j++) {  
        while( j>0 && s[i]!=t[j] ) j=fail[j];
        if( j>longest ) { longest = j; lp = i-j; }
        if( j==lt ) return i-lt;        
    }
    return -1;
}

