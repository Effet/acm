#include<iostream>
using namespace std;
//举例 3x+4y=1 ax+by=1
//得到一组解x0=-1，y0=1 通解为x=-1+4k,y=1-3k
inline __int64 extend_gcd(__int64 a,__int64 b,__int64 &x,__int64 &y)//ax+by=1返回a,b的gcd，同时求的一组满足题目的最小正整数解
{
   __int64 ans,t;
   if(b==0){x=1;y=0;return a;}
   ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
   return ans;  
}   
//(a/b)%mod=c 逆元为p，(p*b)%mod=1
//(a/b)*(p*b)%mod=c*1%mod=c
// (p*b)%mod=1 等价于 p*b-(p*b)/mod*mod=1其中要求p，b已知 等价于 ax+by=1
//其中x=p（x就是逆元）,y=p/mod,a=b,b=b*mod 那么调用extend_gcd(b,b*mod,x,y)即可求(a/b)%mod的逆元等价于a*p%mod
int main()
{
   __int64 a,b,x,y,c,gcd,mod,p;//ax+by=c
   while(cin>>a>>b>>c)
   {
      gcd=extend_gcd(a,b,x,y);
      if(c%gcd){cout<<"无解!"<<endl;continue;}
      cout<<"x="<<x*c/gcd<<" y="<<y*c/gcd<<endl;            
   }
   return 0;
}
