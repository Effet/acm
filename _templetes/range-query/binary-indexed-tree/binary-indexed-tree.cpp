#define MAXN 10000

int lowbit(int i){
	return i&(-i);
}

void add(int i, int v){
	while(i<=MAXN){
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
