#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 1000000 + 10;

char str[2*MAX_N];
int rad[2*MAX_N];
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


char s[MAX_N];

int main(int argc, char *argv[])
{
    int cas = 1;
    while (scanf("%s", s) != EOF)
    {
        if (strcmp(s, "END") == 0)
            break;
        printf("Case %d: %d\n", cas++, Manacher(s) - 1);
    }
    return 0;
}
