#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int MinimumRepresentation(int *s, int len){
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

char str[333333];
int a[333333];

int main()
{
	while (cin >> str)
	{
		int len = strlen(str);
		for (int i = 0; i < len; ++ i)
			a[i] = (str[(i+1)%len]-str[i]+8)%8;

		int k = MinimumRepresentation(a,len);
		for (int i = k; i < len; ++ i)
			cout << a[i];
		for (int i = 0; i < k; ++ i)
			cout << a[i];
		cout << endl;
	}
}
