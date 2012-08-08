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

ll Chinese_Remainder(ll* a, ll* n, int k) {
    ll N = 1, r = 0;
    for (int i = 0; i < k; ++ i)
        N *= n[i];
    for (int i = 0; i < k; ++ i)
    {
        ll m = N / n[i], x, y;
        ex_gcd(m, n[i], x, y);
        x = (x % n[i] + n[i]) % n[i];
        r = (r + a[i]*m*x) % N;
    }
    return r;
}
