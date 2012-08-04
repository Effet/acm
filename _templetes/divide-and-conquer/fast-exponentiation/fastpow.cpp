typedef long long ll;
int fastpow(ll a, int b, int c)
{
    ll r = 1 % c;
    while(b)
    {
        if (b & 1)
            r = r * a % c;
        b >>= 1;
        a = a * a % c;
    }
    return (int)r;
}
