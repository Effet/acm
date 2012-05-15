#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define Max 30

char str[Max];

long long num[Max][Max];
int x;
long long  a[Max];
int ans;
long long sum;
void solve(int n, int cnt) {
	if (cnt == 1) {
        a[1] = num[1][n];
        if ( 
			(cnt != x && a[1] > a[2])
			)
            return ;

        int r = 1;
        int cc = 1;
        for (int i = 2; i <= x; ++ i)
        {
            if (a[i] == a[i-1])
            {
                ++ cc;
                if (i == x)
                {
                    for (int j = 2; j <= cc; ++ j)
                        r *= j;
                }
            }
            else
            {
                for (int j = 2; j <= cc; ++ j)
                    r *= j;
                cc = 1;
            }
        }
        // cout << "a[i] :";
        // for (int i = 1; i <= x; ++ i)
        //     cout << a[i] << " ";
        // cout << endl;
        sum += (long long) ans / r;
        
        return;
	}
	int limit_d = n/cnt;
	int limit_u = n - (cnt - 1);
    // cout << "n, cnt : " << n << " " << cnt << endl;
	// cout << "limit(" << limit_d << "," << limit_u<< ")" << endl;
	for (int l = limit_d; l <= limit_u; ++ l) {
        a[cnt] = num[n-l+1][n];
        if (
			(cnt == x || a[cnt] <= a[cnt+1])
			&& str[n - l + 1] != '0'
		)
            solve(n-l, cnt-1);
	}
}

int main ()
{
	int t;
	scanf ("%d", &t);
	while (t --)
	{
        scanf ("%s", str);
        x = str[0] - '0';
        int n = strlen(str) - 1;

		if (x == 0) {
			printf ("1\n");
			continue;
		}
		if (x == 1) {
		printf ("9\n");
		continue;
		}
        for (int i = 1; i <= n; ++ i) {
            for (int j = i; j <= n; ++ j) {
                num[i][j] = 0;
                for (int k = i; k <= j; ++ k) {
                    num[i][j] = num[i][j]*10 + str[k]-'0';
                }
                //cout << i << " " << j << " "
                	//<< num[i][j] << endl;
            }
        }

        ans = 1;
        int temp = 9;
        for (int i = 1;i <= x;i ++) {
            ans = ans * temp;
            temp --;
        }
        // cout << "ans: "
        //      << ans << endl;

        // cout << "x :" << x << endl;
        sum = 0;
        solve(n,x);

        printf ("%lld\n", sum);
	}
}
