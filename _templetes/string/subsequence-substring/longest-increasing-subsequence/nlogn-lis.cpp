#define _cp(a,b) ((a)<(b))

const int MAX_N = 100000 + 10;

int f[MAX_N];

int lis(int s[], int n)//单调不降子序列nlogn算法
{
	int l, r, mid, len = 1;
	f[1] = s[1];
	for(int i = 2; i<=n; i++){
		l = 1, r = len;
		if(_cp(f[len],s[i])){
			f[++len] = s[i];
			continue;
		}
		while(l<=r){
			mid = (l+r)>>1;
			if(_cp(f[mid],s[i]))
				l = mid+1;//不降
			else
				r = mid-1;//二分查找
		}
		f[l] = s[i];//插入
		if(l>len)
			len++;//增加长度
	}
	return len;
}
