#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAXN 20+5

int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1},
		{1,1},{-1,1},{1,-1},{-1,-1}};
int r, c, n, ans;

int f[MAXN][MAXN];

void swap(int &a, int &b){
	int t = a;
	a = b;
	b = t;
}

int judge(int x, int y){
	if(x<0||x>=r||y<0||y>=c) return 0;
	return 1;
}

void flood(int x, int y, int num){
	f[x][y] = -1;
	for(int i=0; i<8; i++){
		int xx = x + dir[i][0];
		int yy = y + dir[i][1];
		if(judge(xx,yy)&&f[xx][yy]==num)
			flood(xx, yy, num);
	}
}

int main(){
	//freopen("in.txt", "r", stdin);
	while(cin>>r>>c, r||c){
		memset(f, 0, sizeof(f));
		cin>>n;
		int w, x, y, z;
		for(int k=0; k<n; k++){
			cin>>w>>x>>y>>z;
			if(w>y) swap(w,y);
			if(x>z) swap(x,z);
			for(int i=x; i<z; i++)
				for(int j=w; j<y; j++)
					f[i][j]|=(1<<k);
		}
		int ans = 0;
		for(int i=0; i<r; i++)
			for(int j=0; j<c; j++){
				if(f[i][j]>=0){
					ans++;
					flood(i, j, f[i][j]);
				}
			}
		cout<<ans<<endl;
	}
	return 0;
}
