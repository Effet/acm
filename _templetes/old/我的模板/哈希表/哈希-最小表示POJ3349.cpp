#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define PRI_NUM 149997
struct node{
	int length[12];
	int next;
} snow_hash[PRI_NUM+100000+50];
int hash_index;
int temp[12], temp2[12];
bool check(int a, int* snow)//基于最小表示法写的匹配函数
{
	int index1 = 0, index2 = 0, i;
	while(index1<6&&index2<6){
		i = 0;
		while(snow[index1+i]==snow_hash[a].length[index2+i])
			i++;
		if(i>=6)
			return true;
		if(snow[index1+i]>snow_hash[a].length[index2+i])
			index1 += i+1;
		else
			index2 += i+1;
	}
	return false;
}
bool insert(int num){
	int i = num;
	while(snow_hash[i].next){
		if(check(snow_hash[i].next, temp)||check(snow_hash[i].next, temp2))
			return true;
		i = snow_hash[i].next;
	}
	snow_hash[i].next = hash_index;
	for(int j = 0; j<12; j++){
		snow_hash[hash_index].length[j] = temp[j];
	}
	hash_index++;
	return false;
}
int main(){
	memset(snow_hash, 0, sizeof(snow_hash));
	hash_index = PRI_NUM;
	int n, sum;
	bool flag = false;
	scanf("%d", &n);
	for(int i = 0; i<n; i++){
		sum = 0;
		int x;
		for(int j = 0; j<6; j++){
			scanf("%d", &x);
			temp[6+j] = temp2[5-j] = temp2[11-j] = temp[j] = x;
			sum += temp[j];
		}
		if(flag = insert((sum)%PRI_NUM))
			break;
	}
	if(flag)
		printf("Twin snowflakes found.\n");
	else
		printf("No two snowflakes are alike.\n");
	return 0;
}
