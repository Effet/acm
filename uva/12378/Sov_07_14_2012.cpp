#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_LEN = 100000 + 10;

// int p[MAX_LEN*2];
// // s[1..n] is the input string, and s[0] = '#'.
// int Manacher( char *s, int n ){
//     int i, mx = 0, id = 0;
//     for ( i = 1; i <= n ; i++ ) {
//         p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
//         while (i+p[i]<=n && i-p[i]>0 && s[i+p[i]]==s[i-p[i]])
//             p[i]++;
//         if (i + p[i] > mx) {
//             mx = i + p[i];
//             id = i;
//         }
//     }
//     int ans = 1;
//     for(int i=1 ; i <= n ; ++i)
//         ans = max( p[i], ans );
//     return ans;
// }


char str[2*MAX_LEN];
int rad[2*MAX_LEN];
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


char s[MAX_LEN];

int main() {
    int T;
    scanf("%d", &T);
    while( T-- ){
        scanf("%s", s);

        int k = 1;
        for (int i = 1; s[i]; ++ i)
            if (s[i] != s[k-1])
                s[k++] = s[i];
        s[k] = '\0';

        // cout << s << endl;

        // ++ k;
        // for (int i = k; i >= 1; -- i)
        //     s[i] = s[i-1];
        // s[0] = '#';
        // printf("%d\n", Manacher(s,k-1) );
        printf("%d\n", Manacher(s)/2 );
    }
    return 0;
}
