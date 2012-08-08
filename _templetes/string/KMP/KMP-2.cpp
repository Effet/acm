//另一种解释，来源：浙大模板
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
