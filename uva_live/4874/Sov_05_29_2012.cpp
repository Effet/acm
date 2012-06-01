#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100+5
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

#define elem_t int
void reverse(elem_t* str,int n){
	if (n<=1) return;
	elem_t temp=str[n-1];
	str[n-1]=str[0];
	str[0]=temp;
	reverse(str+1,n-2);
}

int itoa(int div, int buff[MAXN], int x){
	int i, mod, len = 0;
	for(i=0; i<MAXN; i++) buff[i] = 0;
	do{
		mod = div%x;
		div = div/x;
		buff[len] = mod;
		len++;
	}while(div > 0);
	//reverse(buff, len);
	return len;
}

typedef long long NumberType;
NumberType pow_n(NumberType x, unsigned int n){
	NumberType pw = 1;
	while(n>0){
		if((pw%2)==1)
			pw *= x;
		x *= x;
		n /= 2;
	}
	return pw;
}

int NimSum(int b, int x, int y){
	int strx[MAXN], stry[MAXN], ans[MAXN], s, b_i;
	int lenx = itoa(x, strx, b);
	int leny = itoa(y, stry, b);
	int lena = max(lenx, leny);
	for(int i=0; i<lena; i++){
		ans[i] = (strx[i] + stry[i])%b;
	}
	s = ans[0], b_i = b;
	for(int i=1; i<lena; b_i*=b, i++){
		s += b_i*ans[i];
	}
	return s;
}

int main(){
	//freopen("in.txt", "r", stdin);
	int p, cas, i;
	int b, x, y;
	while(cin>>p){
		while(p--){
			cin>>cas>>b>>x>>y;
			cout<<cas<<' '<<NimSum(b, x, y)<<endl;
		}
	}
	return 0;
}
