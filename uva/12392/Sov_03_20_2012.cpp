#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <deque>
#include <stack>
#include <math.h>
using namespace std;

enum POS {
	FIRST,
	LAST,
	MIDDLE
};
typedef struct _OPERATOR {
	char OP;
	int unit;
	POS pos;
} OPERATOR;
typedef deque<char> CHAR_DEQUE;
typedef deque<double> DOUBLE_DEQUE;

typedef stack<char, CHAR_DEQUE> CHAR_STACK;
typedef stack<double, DOUBLE_DEQUE> DOUBLE_STACK;

bool isvalid(char* expr) {
	char* p;
	int count = 0;
	for(p=expr;*p;p++) {
		if(*p == '(')	count++;
		else if(*p == ')') count--;
	}
	return (count==0);
}
int alpha2int(char c) {	return c + 1 - '1';}

int isp(char c) {
	switch(c) {
	case '#':	return 0;
	case '(':	return 1;
	case ')':	return 8;
	case '^':	return 7;
	case '*':	case '/':	case '%':	return 5;
	case '+':	case '-':	return 3;
	}
	return -1;
}

int icp(char c) {
	switch(c) {
	case '#':	return 0;
	case '(':	return 8;
	case ')':	return 1;
	case '*':	case '/':	case '%':	return 4;
	case '+':	case '-':	return 2;
	}
	return -1;
}

double expr(double l, double r, char o) {
	double result = 0;
	switch(o) {
	case '+':	result = l+r;			break;
	case '-':	result = l-r;			break;
	case '*':	result = l*r;			break;
	case '/':	result = l/r;			break;
	case '%':	result = (int)l%(int)r;	break;
	case '^':	result = pow(l, r);		break;
	}
	return result;
}
double cal(char *pstr, int *a)
{
	CHAR_STACK operator_stack;
	DOUBLE_STACK operand_stack;
	
	// 将操作数和操作符入栈
	//char* pstr = argv[1];
	int len = strlen(pstr);
	int i;
	char operater;
	char last_operater;
	double left_operand;
	double right_operand;
	double cal_result;
	operator_stack.push('#');
	int j = 0;
	for(i=0;i<len;i++) {
		while(isalpha(pstr[i])) {
			operand_stack.push(a[j++]);
			i++;
		}
		
		if(i >= len)
			break;
		// 操作符边入栈边处理
		last_operater = operator_stack.top();
		operater = pstr[i];
		while(isp(last_operater) > icp(operater)) {	//出栈
			operator_stack.pop();	//	弹出上一个操作符
			
			// 弹出上两个操作数
			right_operand = operand_stack.top();		operand_stack.pop();
			left_operand = operand_stack.top();		operand_stack.pop();
			cal_result = expr(left_operand, right_operand, last_operater);
			operand_stack.push(cal_result);	// 压入计算结果（抵消上一个操作符和上两个操作数）

			last_operater = operator_stack.top();		

		}
		if(isp(last_operater) == icp(operater))
			operator_stack.pop();
		// 入栈
		else
			operator_stack.push(operater);
	
	}

	// 处理操作符栈
	while(!operator_stack.empty()) {
		last_operater = operator_stack.top();
		if(last_operater == '#') {
			operator_stack.pop();
			break;
		}
		right_operand = operand_stack.top();	operand_stack.pop();
		left_operand = operand_stack.top();	operand_stack.pop();
		cal_result = expr(left_operand, right_operand, last_operater);
		operator_stack.pop();	//	弹出上一个操作符
		operand_stack.push(cal_result);	// 压入计算结果（抵消上一个操作符和上两个操作数）
	}
	return operand_stack.top();
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	int n, ans, a[11];
	char str[111];
	int flag;
	while (scanf("%d", &n))
	{
		for (int i = 0; i < n; i ++)
			scanf("%d", &a[i]);
		scanf("%d", &ans);
		if (!n && !ans)
			break;

		cin >> str;

		sort(a, a+n);
		flag = 0;
		do {
			if (cal(str,a) == ans)
			{
				flag = 1;
				break;
			}
		} while(next_permutation(a,a+n));
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
}
