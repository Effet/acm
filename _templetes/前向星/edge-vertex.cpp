// edge-vertex.cpp --- 数组模拟链表
// 
// Author: n4k0master
// Mail: nesuadark@gmail.com
// 
// Created: Wed Jul 25 09:53:00 2012 (+0800)
// Last-Updated: Wed Jul 25 09:53:36 2012 (+0800)
// 
// 

// Code:


const int MAX_VETX = 100 + 10;
const int MAX_EDGE = 300 + 10;


struct edge {int to, next;} E[MAX_EDGE];
// must initialize head to -1
int n, m, head[MAX_VETX];

// Insert the i-th edge from `u' to `v'.
//              head[u] == next1 -> next2 -> ...
//  E[i].next = head[u] ...
//                 E[i] -> next1 -> next2 -> ...
//   head[u] = i = E[i] ...
//       head[u] = E[i] -> next1 -> next2 -> ...
//                  |
//                  V
//             (E[i].to = v)
void insert_direct_edge(int i, int u, int v)
{
    E[i].to   = v;
    E[i].next = head[u];
    head[u]   = i;
}

void Usage(int u)
{
    for (int i = head[u]; i != -1; i = E[i].next)
    {
        // E[i].to is u's son
        // do some thing
    }
}

// 
// edge-vertex.cpp ends here
