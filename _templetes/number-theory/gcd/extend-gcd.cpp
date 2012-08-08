typedef long long ll;

ll ex_gcd(ll a, ll b, ll& x, ll& y)
{
   ll d;
   if (b == 0) {
       x = 1; y = 0;
       return a;
   }
   d  = ex_gcd(b, a%b, y, x);
   y -= a/b * x;
   return d;
}
