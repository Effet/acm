#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define _max(a,b) ((a)>(b)?(a):(b))

const int MAX_V = 200000;

int f[MAX_V+10], V;
void ZeroOnePack( int cost, int weight )
{
   for ( int v=V; v >= cost; -- v )
      f[v] = _max( f[v], f[v-cost] + weight );
}
void CompletePack( int cost, int weight )
{
   for ( int v=cost; v <= V; ++ v )
      f[v] = _max( f[v], f[v-cost] + weight );
}
void MultiplePack( int cost, int weight, int amount )
{
   if ( cost*amount >= V )
      CompletePack( cost, weight );
   else
   {
      int k = 1;
      while ( k < amount )
      {
         ZeroOnePack( k*cost, k*weight );
         amount = amount - k;
         k = k * 2;
      }
      ZeroOnePack( amount*cost, amount*weight );
   }
}

