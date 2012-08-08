int Longest_Increasing(int num[], int n){
	int lis[n], i, j;
	for(i = 0; i<n; i++){
		lis[i] = 1;
		for(j = 0; j<i; j++)
			if(num[i]>num[j]&&lis[j]+1>lis[i])
				lis[i] = lis[j]+1;
	}
	int maxn = 0;
	for(i = 0; i<n; i++)
		if(maxn<lis[i])
			maxn = lis[i];
	return maxn;
}
