#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int Limit = 1000000;

bool sieve[Limit + 1];
struct Num {
    int n;
    vector<int> v;
} num[Limit + 1];

int lena, lenb;

bool cmp(const Num &a, const Num &b)
{
    lena = a.v.size();
    lenb = b.v.size();
    if (lena != lenb)
        return lena < lenb;

    for (int i = 0; i < lena; ++ i)
        if (a.v[i] != b.v[i])
            return a.v[i] < b.v[i];
}

void Sieve_of_Eratosthenes()
{
    for (int i = 1; i <= Limit; ++ i)
        num[i].n = i;
    
    for (int i = 2; i <= Limit; ++ i)
        if (!sieve[i])
        {
            num[i].v.push_back(i);
            for (int j = i * 2; j <= Limit; j += i)
            {
                int t = j;
                while (t % i == 0) {num[j].v.push_back(i); t /= i;}
                sieve[j] = 1;
            }
        }
}


const int MAX_LEN  = Limit + 5; // 10^5
const int MAX_DEEP = 25;         // The deep of segment tree.

int sorted           [MAX_LEN]; // The sorted array.
int toLeft [MAX_DEEP][MAX_LEN]; // Counts to the left in [l, i]. (i determine l)
int values [MAX_DEEP][MAX_LEN]; // Values stored in each segment tree's node.


// Building segment tree T(l, r).
void build(int l, int r, int d = 0)
{
    if(l == r) return ;
    int mid = (l + r) >> 1;
    
    int lsame = mid - l + 1;    // Count of numbers equal to sorted[mid].
    for(int i = l; i <= r; ++ i)
        if(values[d][i] < sorted[mid])
            -- lsame;
    
    int lpos = l;
    int rpos = mid + 1;
    int cnt  = 0;
    for(int i = l; i <= r; ++ i)
    {
        if(values[d][i] < sorted[mid])
        {
            values[d+1][lpos++] = values[d][i];
            ++ cnt;
		}
        else if (values[d][i] == sorted[mid] && lsame)
        {
            values[d+1][lpos++] = values[d][i];
            ++ cnt;
            -- lsame;
        }
        else
			values[d+1][rpos++] = values[d][i];
        
        toLeft[d][i] = cnt;
	}
    
	build(l,     mid, d+1);
	build(mid+1, r,   d+1);
}


// Query for Kth-number in [L,R] on the segment tree T(l, r).
int query(int L, int R, int k, int l, int r, int d = 0)
{
	if(L == R)
		return values[d][L];

    int mid = (l + r) >> 1;
    
    int left1 = (L > l ? toLeft[d][L-1] : 0); // Count to the left in [l, L-1].
    int left2 = toLeft[d][R] - left1;         // Count to the left in [L, R].
    
	if(left2 >= k)              // K-th number in left-son of [L, R].
    {
		int newl = l + left1;
		int newr = l + left1 + left2 - 1;
		return query(newl, newr, k, l, mid, d+1);
	}
    else
    {
		int right1 = L - l - left1;     // Count to the right in [l, L-1].
		int right2 = R - L + 1 - left2; // Count to the right in [L, R].
		int newl = mid + right1 + 1;
		int newr = mid + right1 + right2;
		return query(newl, newr, k-left2, mid+1, r, d+1);
	}
}


int main(int argc, char *argv[])
{
    Sieve_of_Eratosthenes();

    for (int i = 1; i <= Limit; ++ i)
        sorted[i] = i;

    int n = Limit;
    sort(num + 1, num + n + 1, cmp);
    
    for (int i = 1; i <= n; ++ i)
        values[0][num[i].n] = i;

    build(1, n);

    int m;
    scanf("%d", &m);
    for (int cas = 1; cas <= m; ++ cas)
    {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        int ans = query(a, b, k, 1, n);
        printf("Case %d: ", cas);
        for (int i = 0; i < num[ans].v.size(); ++ i)
        {
            printf("%d", num[ans].v[i]);
            if (i + 1 < num[ans].v.size())
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
