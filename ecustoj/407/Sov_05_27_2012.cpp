#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <math.h>
#include <cmath>
using namespace std;
int main()
{
    int t;
    while(scanf("%d\n",&t)==1)
    {
        while(t--)
        {
            char a[100];
            int i,j;
            gets(a);
            int tt=0;
            int count=0;
            if(count==strlen(a))
            {
                printf("0\n");
                continue;
            }
            for(i=0;i<strlen(a);i++)
            {
                if(a[i]!=' ')
                    break;
            }
            int x=i;
            for(i=strlen(a)-1;i>=0;i--)
                if(a[i]!=' ')
                    break;
            int y=i;
            for(i=x;i<=y;i++)
            {
                if(a[i]=='0')
                    count++;
            }
            if(count==y-x+1)
            {
                printf("0\n");
                continue;
            }
            for(i=x;i<=y;i++)
            {
                if(!(a[i]>='0'&&a[i]<='9'))
                    break;
            }
            if(i==y+1)
            {
                for(i=x;i<=y;i++)
                    if(a[i]!='0')
                        break;
                int q=i;
                for(i=q;i<=y;i++)
                        printf("%c",a[i]);
                printf("\n");
            }
            else
                printf("invalid input\n");

        }
    }
    return 0;
}
