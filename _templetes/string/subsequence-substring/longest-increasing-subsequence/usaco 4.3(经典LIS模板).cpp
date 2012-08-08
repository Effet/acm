/* 
   ID: majunch2
   LANG: C++
   PROG: buylow
*/
//usaco 4.3
//很经典的O(nlogn)LIS问题，还可以求序列方案数

#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include <cmath>
#include <algorithm>
//#include <ctime>
using  namespace std;
const double inf = 1e15;

int p[5010],f[5010];  //p[i]为值，f[i]为以第i元素为末元素的最长上升子序列长度
int best[5010];  //best[i]表示长度为i的序列的当前最小末元素
int num[5010];   //num[i]表示以第i元素为末元素的最长上升子序列方案数

int find(int l,int r,int key)
{
	int mid;
	while (1)
	{
		mid=(l+r)>>1;
		if (best[mid]<key && key<=best[mid+1])
			return mid+1;
		if (best[mid-1]<key && key<=best[mid])
			return mid;
		if ( key<best[mid] )
			r=mid-1;
		else l=mid+1;
	}
}



int main()
{
	//freopen("buylow.in","r",stdin);
	//freopen("buylow.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=n;i>=1;i--)
		scanf("%d",&p[i]);
	memset(best,-1,sizeof(best));
	int k;
	int ans=1;
	best[1]=p[1];f[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (p[i]<=best[1]) k=1;  //这里寻k值要很小心，不然容易死循环
		else if (p[i]>best[ans]) k=++ans;
		else k=find(1,ans,p[i]);

		best[k]=p[i];
		f[i]=k;
	}
	printf("%d ",ans);
	
    //如果相同的序列只能算一种方案，那需要判重，最简单的就是用bool数组了，但由于序列的特性，这里只使用now同样可以
	for (int i=1;i<=n;i++)
	{
		if (f[i]==1) { num[i][0]=num[i][1]=1; continue; }
		int now=-1;
	    for (int j=i-1;j>=1;j--)
	       if (f[j]+1==f[i] && p[j]<p[i] && now!=p[j])
		   {
			   num[i]+=num[j];
			   now=p[j];        //这里值得思考一下，很简单，对于符合条件的
		   }                    //重复的两个数（假设为p[i1]=p[i2])肯定是连续枚举的，因为如果中
	}                      //还枚举了其他数(假设有p[j])那会矛盾。
			//若p[j]>p[i1],就有f[j]至少为f[i1]+1，不符合枚举条件；
			//若p[j]<p[i1],就有f[i2]至少为f[j]+1,这样p[i2]不会枚举到，矛盾。
   
	int now=-1;
	int sum=0;
	for (int i=1;i<=n;i++)
		if (f[i]==ans && now!=p[i])
		{
			sum+=num[i];
			now=p[i];
		}
	printf("%d/n",sum);


	return 0;
}
