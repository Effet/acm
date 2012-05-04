#define MAXN 1000+10

int a[MAXN][MAXN];

int Lowbit(int m){
	return m&(-m);
}

int Getsum(int x,int y){
	int tempy,sum=0;
	while(x>0){
		tempy = y;
		while(tempy>0){
			sum += a[x][tempy];
			tempy -= Lowbit(tempy);
		}
		x -= Lowbit(x);
	}
	return sum;
}

void Inc(int x,int y,int Delta,int MaxNum){
	int tempy;
	while(x<=MaxNum){
		tempy = y;
		while(tempy<=MaxNum){
			a[x][tempy] += Delta;
			tempy += Lowbit(tempy);
		}
		x += Lowbit(x);
	}
}