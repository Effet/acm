/*
 * Problem name: Phone List
 *  Solved when: 2011-7-6
 *       Author: nesua
 *  Description: ��һ���绰�б����û��һ���绰��������һ����ǰ׺��
 *  ��ô������绰�б��ÿ�����붼�ǿɲ��ĵġ�
 *  ����һ���绰�б�:
 *  	Emergency 911
 *  	Alice 97625999
 *  	Bob 91125426
 *  ���������£��Ͳ����ܸ�Bob��绰����Ϊ��������911ʱ��ֱ�ӽ�ͨEmergency�ˡ�
 *  �ʣ�����һ���绰�б�ȷ�����Ƿ�ÿ�����붼�ɲ��ġ�
 *
 *      ����˼·: �����ֵ�����⡣
 *      ���ڵ绰���밴�ֵ������е�ǰ���£����Ƶã�
 *      ���һ����������������ǰ׺����ô���ǰ׺��Ȼ�����ڴ˺���֮ǰ���������ڣ�
 *      Ҳ������һ�������ǰһ�����벻�Ǵ˺����ǰ׺����ô�绰�б��в����ڴ˺����ǰ׺��
 *      �ʽ��绰�����ֵ������к󣬱Ƚ������ڵ绰���뼴�ɡ�
 *
 *      ���׳̶�: �����
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#define MAXN 10
#define MAXM 10000
using namespace std;

struct phon{
   char str[MAXN+1];
} p[MAXM+1];

int cmp(const void *a, const void *b){
   return strcmp((*(phon *) a).str, (*(phon *) b).str);
}

int compe(char *a, char *b){
   for(int i = 0; i<strlen(a); i++)
      if(a[i]!=b[i])
         return 0;
   return 1;
}

int cons(phon *p, int n){
   int i;
   for(i = 0; i<n-1; i++){
      if(compe(p[i].str, p[i+1].str))
         return 0;
   }
   return 1;
}

int main(){
   int t, n, i;
   while(scanf("%d", &t)!=EOF){
      while(t--){
         scanf("%d", &n);
         for(i = 0; i<n; i++){
            scanf("%s", p[i].str);
         }
         qsort(p, n, sizeof(p[0]), cmp);
         printf(cons(p, n) ? "YES\n" : "NO\n");
      }
   }
   return 0;
}

//��̬Trie
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define HAS true
#define NOT false

const int L = 10000 + 10;
const int N = 1<<16;

struct Node {
   bool    val, rod;
   int     son[10];
};

Node q[N];
int top;
char s[L];
bool flag;

void clear() {
   memset(q, 0, sizeof(q));
   top = 1; flag = NOT;
}

void insert() {
   int n = 0;
   for( int i = 0; s[i]; ++i ) {
      if(!q[n].son[s[i] - '0']){
         q[n].son[s[i] - '0'] = top;
         n = top;
         ++ top;
      }else{
         n = q[n].son[s[i] - '0'];
      }
      if(s[i+1]) q[n].rod = true;
      if(q[n].val) flag = HAS;
   }
   if(q[n].rod) flag = HAS;
   q[n].val = true;
}


int main(){
   freopen("POJ.in", "r", stdin);
   int t, n;
   scanf("%d", &t);
   while(t--){
      clear();

      scanf("%d", &n);
      for(int i=0;i<n;i++){
         scanf("%s", s);
         if(flag == NOT) insert();
      }
      if(flag == HAS)
         printf("NO\n");
      else
         printf("YES\n");
   }
   return 0;
}
