// Refers to:
//   http://www.notonlysuccess.com/index.php/divide-tree/
//   http://acm.bjtu.edu.cn:8080/wiki/?tag=%E5%88%92%E5%88%86%E6%A0%91

#include <cstdio>
#include <algorithm>
using namespace std;


const int MAX_LEN  = 100000 + 5; // 10^5
const int MAX_DEEP = 20;         // The deep of segment tree.


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


int main()
{
    int n, m;
    // `n' is length of sequence, `m' is count of querys.
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &values[0][i]);
        sorted[i] = values[0][i];
    }
    sort(sorted + 1, sorted + n + 1);
    build(1, n);
    while (m--)
    {
        int l, r, k;
        // Query the K-th number of [l, r].
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", query(l, r, k, 1, n));
    }
    return 0;
}
