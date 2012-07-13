
当gcd(a,b)=1时 S(a*b)=S(a)*S(b);   S(n) 为n的所有因子和（包括1和他本身）
如果 p为素数  S(p^n)=1+p+p^2+...+p^n= (p^(n+1)-1) /(p-1) 


%运算法则 1. (a*b) %p= ( a%p) *(b%p)
%运算法则 2. (a/b) %p= ( a *b^(-1)%p)

b^(-1)是 b的逆元素 （%p）
2的逆元素是15 （%29） ，因为2*15=30=1 %29
21的逆元素是18 （%29） ，因为21*18=378%29=1 %29


__int64 ex_gcd(__int64 a,__int64 b,__int64 &x,__int64 &y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	__int64 g,t;
	g=ex_gcd(b,a%b,x,y);
	t=x;
	x=y;
	y=t-a/b*y;
	return g;
}
//(a/b)%p    a=a%p, (b%p!=0)!!!
__int64 mod(__int64 a,__int64 b,__int64 k){
	__int64 x,y,ans;
	__int64 gcd=ex_gcd(b,k,x,y);
	return ans=(x*(a/gcd)%k+k)%k;
}
