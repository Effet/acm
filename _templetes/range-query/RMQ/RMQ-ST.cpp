// http://www.cppblog.com/acmiyou/archive/2009/05/18/83278.aspx

#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
#define M 100010
#define MAXN 500
#define MAXM 500
int dp[M][18];
int dp2[MAXN][MAXM][10][10]
/*
 *一维RMQ ST算法
 *构造RMQ数组 makermq(int n,int b[]) O(nlog(n))的算法复杂度
 *dp[i]j] 表示从i到i+2^j -1中最大的一个值
 *dp[i][j]=max{dp[i][j-1],dp[i+2^(j-1)][j-1]}
 *查询RMQ rmq(int s,int v)
 *将s ->v 分成两个2^k的区间
 *即 k=(int)log2(s-v+1)
 *查询结果应该为 max(dp[s][k],dp[v-2^k+1][k])
 */
int rmq(int s,int v)
{
    int k=(int)(log((v-s+1)*1.0)/log(2.0));
    return max(dp[s][k],dp[v-(1<<k)+1][k]);
}
void makermq(int n,int b[])
{
    int i,j;
    for(i=1;i<=n;i++)
        dp[i][0]=b[i];
    for(j=1;(1<<j)<=n;j++)
        for(i=1;i+(1<<j)-1<=n;i++)
            dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}

/*
 *二维RMQ ST算法
 *构造RMQ数组 makermq(int n,int m,int b[][]) O(n*m*log(n)*log(m))算法复杂度
 *dp2[row][col][i][j] 表示 行从row ->row +2^i-1 列从col ->col +2^j-1 二维区间里最大值
 *dp2[row][col][i][j] = 下行
 *max{dp2[row][col][i][j-1],dp2[row][col][i-1][j],dp2[row][col+2^(j-1)][i][j-1],dp2[row+2^(i-1)][col][i-1][j]}
 *查询RMQ rmq(int sx,int ex,int sy,int ey)
 *同一维的将sx->ex 分为两个2^kx区间 将 sy->ey分为两个2^ky的区间
 *kx=(int)log2(ex-sx+1) ky=(int)log2(ey-sy+1)
 *查询结果为
 *max{dp2[sx][sy][kx][ky],dp2[sx][ey-2^ky+1][kx][ky],dp2[ex-2^kx+1][sy][kx][ky],dp2[ex-2^kx+1][ey-2^ky+1][kx][ky]}
 */

void makermq(int n,int m,int b[][MAXM])
{
    int row,col,i,j;
    for(row=1;row<=n;row++)
        for(col=1;col<=m;col++)
            dp2[row][col][0][0]=b[row][col];
    for(i=0;(1<<i)<=n;i++)
        for(j=0;(1<<j)<=m;j++)
        {
            if(i==0&&j==0) continue;
            for(row=1;row+(1<<i)-1<=n;row++)
                for(col=1;col+(1<<j)-1<=m;col++)
                {
                    if(i==0)
                        dp2[row][col][i][j]=max(dp2[row][col][i][j-1],dp2[row][col+(1<<(j-1))][i][j-1]);
                    else
                        dp2[row][col][i][j]=max(dp2[row][col][i-1][j],dp2[row+(1<<(i-1))][col][i-1][j]);
                }
        }
}
int rmq(int sx,int ex,int sy,int ey)
{
    int kx=(int)(log((ex-sx+1)*1.0)/log(2.0)),ky=(int)(log((ey-sy+1)*1.0)/log(2.0));
    return max(max(dp2[sx][sy][kx][ky],dp2[sx][ey-(1<<ky)+1][kx][ky]),max(dp2[ex-(1<<kx)+1][sy][kx][ky],dp2[ex-(1<<kx)+1][ey-(1<<ky)+1][kx][ky]));
}
