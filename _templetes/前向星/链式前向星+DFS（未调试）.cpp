// 链式前向星+DFS（未调试）.cpp --- 数组模拟链表
// 
// Copyright (C) 2012 n4k0master <nesuadark@gmail.com>
// 
// Created: Sun Jul 22 19:44:13 2012 (+0800)
// Last-Updated: Sun Jul 22 19:44:27 2012 (+0800)
// 
// 

// Code:


#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

#define WHITE 0
#define GRAY -1
#define BLACK 1

const int MAX_VETX = 100;
const int MAX_EDGE = 100;

//有向图链式前向星即是数组模拟链表，需先初始化head和next
int n, head[MAX_VETX];
int m, E[MAX_EDGE], next[MAX_EDGE];
//第i条从u到v的边
void insertDirectEdge(int i, int u, int v){
   E[i] = v, next[i] = head[u], head[u] = i;
}

typedef struct vertax{int color, pre, d, f;}Vetx;
Vetx V[MAX_VETX];
int time;
void DFS_Visit(int u){
   V[u].d = ++time, V[u].color = GRAY;
   for(int i=head[u]; i!=-1; i=next[i])
      if(V[E[i]].color == WHITE)
         V[E[i]].pre = u, DFS_Visit(E[i]);
   V[u].color=BLACK, V[u].f = ++time;
}
void DFS(){
   for(int i=1;i<=n;i++)
      V[i].color = WHITE, V[i].pre = -1;
   time = 0;
   for(int i=1;i<=n;i++)
      if(V[i].color == WHITE)
         DFS_Visit(i);
}

// 
// 链式前向星+DFS（未调试）.cpp ends here
