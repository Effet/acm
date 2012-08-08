/*str是这样一个字符串（下标从1开始）：
  举例：若原字符串为"abcd"，则str为"$#a#b#c#d#"，最后还有一个终止符。
  n为str的长度，若原字符串长度为nn，则n=2*nn+2。
  rad[i]表示回文的半径，即最大的j满足str[i-j+1...i] = str[i+1...i+j]，
  而rad[i]-1即为以str[i]为中心的回文子串在原串中的长度*/

#define MAXN 100001
char str[2*MAXN];
int rad[2*MAXN];
int Manacher(char *s)
{
    int i,mx = 0,id,len,n,ans=0;
    len = strlen(s);
    n = len*2+2;
    str[0] = '$';
    for(i=0;i<=len;i++){
        str[i*2+1] = '#';
        str[i*2+2] = s[i];
    }
    for(i=1; i<n; i++)
    {
        if( mx > i )
            rad[i] = rad[2*id-i]<mx-i?rad[2*id-i]:mx-i; 
        else
            rad[i] = 1;
        for(; str[i+rad[i]] == str[i-rad[i]]; rad[i]++)
            ;
        if( rad[i] + i > mx )
        {
            mx = rad[i] + i;
            id = i;
        }
    }
    for(i=0;i<n;i++)
        ans=rad[i]>ans?rad[i]:ans;
    return ans;
}
