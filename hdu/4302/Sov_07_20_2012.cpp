#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 100;

int a[MAX_N];

int lowbit(int i){
	return i&(-i);
}

void add(int i, int v){
	while(i < MAX_N){
		a[i]+=v;
		i+=lowbit(i);
	}
}

int sum(int i){
	int s=0;
	while(i>0){
		s+=a[i];
		i-=lowbit(i);
	}
	return s;
}

int r_bisearch(int l, int r)
{
    while (l < r) {
        int m = (l + r) >> 1;
        if (sum(m) > sum(l - 1))
            r = m;
        else
        {
            if (l == m)
                return r;
            l = m;
        }
    }
    return l;
}

int l_bisearch(int l, int r)
{
    while (l < r) {
        int m = (l + r) >> 1;
        if (sum(r) > sum(m - 1))
        {
            if (l == m)
            {
                if (sum(r) > sum(r-1))
                    return r;
                else
                    return l;
            }
            l = m;
        }
        else
            r = m;
    }
    return l;
}


int L, n;

int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    // cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        // cin >> L >> n;
        scanf("%d%d", &L, &n);
        memset(a, 0, sizeof(a));

        ll cos_dis = 0;
        int pos = 1, di = 1;
        while (n--)
        {
            int op;
            scanf("%d", &op);
            // cin >> op;
            if (op == 0)
            {
                int x;
                // cin >> x;
                scanf("%d", &x);
                ++ x;
                add(x, 1);
            }
            else
            {
                int l_pos = - 1, r_pos = -1;
                if (sum(pos) > 0)
                    l_pos = l_bisearch(1, pos);
                if (sum(L + 1) > sum(pos - 1))
                    r_pos = r_bisearch(pos, L + 1);

                // cout << "l, r pos : " << l_pos << " "<< r_pos << endl;

                int l_opt_dis = INT_MAX, r_opt_dis = INT_MAX;
                if (l_pos != -1)
                    l_opt_dis = pos - l_pos;
                if (r_pos != -1)
                    r_opt_dis = r_pos - pos;

                if (l_opt_dis < r_opt_dis)
                {
                    cos_dis += (ll)l_opt_dis;
                    di = -1;
                    pos = l_pos;
                    add(pos, -1);
                }
                else if (r_opt_dis < l_opt_dis)
                {
                    cos_dis += (ll)r_opt_dis;
                    di = 1;
                    pos = r_pos;
                    add(pos, -1);
                }
                else if (di == 1 && r_opt_dis != INT_MAX)
                {
                    cos_dis += (ll)r_opt_dis;
                    pos = r_pos;
                    add(pos, -1);
                }
                else if (di == -1 && l_opt_dis != INT_MAX)
                {
                    cos_dis += (ll)l_opt_dis;
                    pos = l_pos;
                    add(pos, -1);
                }

                // cout << pos << " " << di << endl;
            }
        }
        printf("Case %d: %lld\n", cas, cos_dis);
        // cout << "Case " << cas << ": " << cos_dis << endl;
    }
    return 0;
}
