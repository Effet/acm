//http://whitedeath.is-programmer.com/posts/18404.html
//这个是网上最一般的最小表示法代码：
int MinimumRepresentation(char *s, int len){
	int i = 0, j = 1, count = 0, t;
	while(i<len&&j<len&&count<len){
		if(s[(i+count)%len]==s[(j+count)%len])
			count++;
		else{
			if(s[(i+count)%len]>s[(j+count)%len])
				i = i+count+1;
			else
				j = j+count+1;
			if(i==j)
				++j;
			count = 0;
		}
	}
	return min(i, j);
}

//首先，求余过程很费时间，尤其是字符串比较长的时候。而且本题中最多是len的2倍，所有变求余为作差；
//其次，最后的return min(i,j)可以改成直接return i，因为i <= j是肯定的....因为用通俗的说法，每次i都会把j拉到i+1的位置，所以最后，可以在改变i的时候，将j也拖过去....
//最终代码：
int MinimumRepresentation(char *s, int len){
	int i = 0, j = 1, count = 0, t;
	while(i<len&&j<len&&count<len){
		int x = i+count;
		int y = j+count;

		if(x>=len)
			x -= len; //用减法代替求余 
		if(y>=len)
			y -= len; //用减法代替求余

		if(s[x]==s[y])
			count++;
		else{
			if(s[x]>s[y]){
				i = i+count+1;
				j = i+1; /*将 j 拖至 i + 1 的地方*/
			}else
				j = j+count+1;

			if(i==j)
				j++;
			count = 0;
		}
	}

	return i; //直接return i即可 
}
