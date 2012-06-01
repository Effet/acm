#include <iostream>
#include <stdio.h>
#define MAXN 40+5
using namespace std;

int main(){
	//freopen("in.txt", "r", stdin);
	char str[MAXN];
	int nu[MAXN];
	int p, cas, i;
	int ans[9];
	while(cin>>p){
		while(p--){
			cin>>cas;
			cin>>str;
			for(i=0; i<40; i++){
				if(str[i] == 'T') nu[i] = 0;
				else nu[i] = 1;
			}
			for(i=0; i<8; i++) ans[i] = 0;
			for(i=0; i<38; i++){
				ans[nu[i]*4+nu[i+1]*2+nu[i+2]]++;
			}
			cout<<cas;
			for(i=0; i<8; i++)
				cout<<' '<<ans[i];
			cout<<endl;
		}
	}
	return 0;
}
