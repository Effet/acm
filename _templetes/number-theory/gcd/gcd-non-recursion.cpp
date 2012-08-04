typedef long long ll;

ll gcd(ll a,ll b){
    if (a == 0) return 1;
    if (a < 0) return gcd(-a,b);
    while (b) {
        ll t=a%b; a=b; b=t;
    }
    return a;
}


//据说是运行次数最少的
int gcd( int a, int b )
{
   if (a == 0) return 1;
   if (a < 0) return gcd(-a,b);
   int r, e;
   while (b != 0)
   {
      r = a%b;
      e = b-r;
      if (r > e) //需要改成 |r| > |e|
         r = e;

      a = b;
      b = r;
   }
   return a;
}
