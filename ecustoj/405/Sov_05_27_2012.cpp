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

#define MAX 100005
struct tree {
    int left;
    int right;
    int sum;
} a[MAX * 3];
int b[MAX];
void build(int L, int R, int id) {
    a[id].left = L;
    a[id].right = R;
    if (L == R) {
        a[id].sum = b[L];
        return;
    }
    int mid = (L + R) / 2;
    build(L, mid, id * 2);
    build(mid + 1, R, id * 2 + 1);
    a[id].sum = a[id * 2].sum + a[id * 2 + 1].sum;
}
int sum = 0;
int answer(int L, int R, int id) {
    if (a[id].left == L && a[id].right == R) {
        sum += a[id].sum;
        return sum;
    }
    int mid = (a[id].left + a[id].right) / 2;
    if (R <= mid) {
        answer(L, R, id * 2);
    } else if (L > mid)
        answer(L, R, id * 2 + 1);
    else {
        answer(L, mid, id * 2);
        answer(mid + 1, R, id * 2 + 1);
    }
}

void input(int id,int x,int y)
{
    if(a[id].left==a[id].right&&a[id].left==x)
    {
        a[id].sum+=y;
        return ;
    }
    a[id].sum+=y;
    int mid=(a[id].left+a[id].right)/2;
    if(mid>=x)
        input(id*2,x,y);
    else
        input(id*2+1,x,y);

}
int main() {
    int n, m,z;
    int t;
    while(scanf("%d",&t)==1)
    {
        while(t--)
        {
            scanf("%d%d%d",&n,&m,&z);
            m=z+m;
            int i;
            for (i = 1; i <= n; i++)
                b[i]=0;
            build(1, n, 1);
            while (m--) {
                char c[2];
                scanf("%s", c);
                if (c[0] == 'P') {
                    int x, y;
                    scanf("%d%d", &x, &y);
                    input(1,x,y);
                } else {
                    int x, y;
                    sum=0;
                    scanf("%d%d", &x, &y);
                    printf("%d\n",answer(x,y,1));
                }
            }
        }
    }
    return 0;
}
