#include<iostream>
using namespace std;
//���� 3x+4y=1 ax+by=1
//�õ�һ���x0=-1��y0=1 ͨ��Ϊx=-1+4k,y=1-3k
inline __int64 extend_gcd(__int64 a,__int64 b,__int64 &x,__int64 &y)//ax+by=1����a,b��gcd��ͬʱ���һ��������Ŀ����С��������
{
   __int64 ans,t;
   if(b==0){x=1;y=0;return a;}
   ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
   return ans;  
}   
//(a/b)%mod=c ��ԪΪp��(p*b)%mod=1
//(a/b)*(p*b)%mod=c*1%mod=c
// (p*b)%mod=1 �ȼ��� p*b-(p*b)/mod*mod=1����Ҫ��p��b��֪ �ȼ��� ax+by=1
//����x=p��x������Ԫ��,y=p/mod,a=b,b=b*mod ��ô����extend_gcd(b,b*mod,x,y)������(a/b)%mod����Ԫ�ȼ���a*p%mod
int main()
{
   __int64 a,b,x,y,c,gcd,mod,p;//ax+by=c
   while(cin>>a>>b>>c)
   {
      gcd=extend_gcd(a,b,x,y);
      if(c%gcd){cout<<"�޽�!"<<endl;continue;}
      cout<<"x="<<x*c/gcd<<" y="<<y*c/gcd<<endl;            
   }
   return 0;
}
