#include <iostream>
#include <cstdio>
#include <climits>
#include <cmath>
using namespace std;

typedef unsigned long long ll;

const int MAX_N = 100000 + 100;

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

int PHI[MAX_N];

void euler()
{
    int i, j; 
    for( i=1 ; i < MAX_N ; ++i ) PHI[i]=i;
    for( i=2 ; i < MAX_N ; i+=2 ) PHI[i]/=2;
    for( i=3 ; i < MAX_N ; i+=2 )
        if( PHI[i] == i ) {
            for( j=i ; j < MAX_N ; j+=i )
                PHI[j] = PHI[j]/i*(i-1);
        }
}

int main()
{
    euler();

    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        int b, P;
        ll M;
        cin >> b >> P >> M;
        
        ll cnt = 0;
        if (P > 2)
        {
            cnt = 0;
            if (b == 0)
                cnt = 1;

            ll n = 1;
            ll ppw = 1;
            ll n_pw = 1;
            for ( ; n <= P && n <= M; ++ n)
            {
                ppw = ppw * n % PHI[P];
                if (ppw == 0)
                    break;

                if (n_pw * n < PHI[P])
                {
                    n_pw = n_pw * n % PHI[P];
                    if (fastpow(n, (int)n_pw, P) == b)
                        ++ cnt;
                }
                else
                    if (fastpow(n, (int)ppw+PHI[P], P) == b)
                        ++ cnt;
            }

            if (n <= M)
            {
                ll len = M - n + 1;
                ll num = len / P;
                ll new_M = n + len % P - 1;

                if (new_M >= n)
                    for (ll i = n; i <= new_M; ++ i)
                        if (fastpow(i, PHI[P], P) == b)
                            ++ cnt;

                if (num > 0)
                    for (ll i = 0; i < P; ++ i)
                        if (fastpow(i, PHI[P], P) == b)
                            cnt += num;
            }
        }
        else if (P == 2)
        {
            cnt = (ll)ceil((M+0.0)/2);
            if (b == 0)
                cnt = M - cnt + 1;
            else if (b == 1)
                ;
            else
                cnt = 0;
        }
        else
            cnt = M + 1;

        
        // if(M == 18446744073709551615LL && P == 1 && b == 0)
        //     printf("Case #%d: 18446744073709551616\n", cas);
        // else
        //     printf("Case #%d: %I64u\n", cas, cnt);

        if(M == 18446744073709551615LL && P == 1 && b == 0)
            cout << "Case #" << cas << ": " << "18446744073709551616" << endl;
        else
            cout << "Case #" << cas << ": " << cnt << endl;
    }
    return 0;
}
