/*
 * Problem name: Phone List
 *  Solved when: 2011-7-6
 *       Author: nesua
 *  Description: 给一个电话列表，如果没有一个电话号码是另一个的前缀，
 *  那么称这个电话列表的每个号码都是可拨的的。
 *  比如一个电话列表:
 *  	Emergency 911
 *  	Alice 97625999
 *  	Bob 91125426
 *  在这个情况下，就不可能给Bob打电话，因为，当按到911时就直接接通Emergency了。
 *  问，给你一个电话列表，确定它是否每个号码都可拨的。
 *
 *      解题思路: 可用字典树求解。
 *      而在电话号码按字典序排列的前提下，可推得：
 *      如果一个号码是另个号码的前缀，那么这个前缀必然出现在此号码之前且他们相邻，
 *      也即是若一个号码的前一个号码不是此号码的前缀，那么电话列表中不存在此号码的前缀。
 *      故将电话号码字典序排列后，比较两相邻电话号码即可。
 *
 *      难易程度: ★★★☆
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

//静态Trie
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
