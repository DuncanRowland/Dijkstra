#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INF 9999

typedef enum bool {false,true} bool;

typedef struct edge {
   long long int node1;
   long long int node2;
   long long int weight;
} edge;

typedef struct path {
   long long int  cost;
   long long int  prev;
   bool done;
} path;

int main() {

   long long int q; //number of queries
   scanf("%lld",&q);

   for(long long int iq=0;iq<q;iq++) {
      long long int n; //Number of nodes
      long long int m; //Number of edges
      scanf("%lld%lld",&n,&m);
      edge *edges=(edge*)malloc(sizeof(edge)*m);
      for(long long int im=0;im<m;im++) {
         scanf("%lld%lld%lld",&(edges[im].node1), &(edges[im].node2), &(edges[im].weight));
         edges[im].node1=edges[im].node1-1; //Off by one user space
         edges[im].node2=edges[im].node2-1; //Off by one user space
      }
      long long int s; //Starting node
      scanf("%lld",&s);
      s--; //Off by one user space
      //Do Dijkstra
      path *paths=(path*)malloc(sizeof(path)*n);
      for(long long int in=0;in<n;in++) paths[in]=(path){INF,-1,false};
      long long int curr=s;
      paths[s]=(path){0,s,true};
      //Find cost of path from each node to curr
      for(long long int in=0;in<n;in++) {
         for(long long int im=0;im<m;im++) {
            if(edges[im].node1==curr) {
               long long int cost=paths[curr].cost+edges[im].weight;
               if(cost<paths[edges[im].node2].cost) {
                  paths[edges[im].node2]=(path){cost,curr,false};
               }
            } else if(edges[im].node2==curr) {
               long long int cost=paths[curr].cost+edges[im].weight;
               if(cost<paths[edges[im].node1].cost) {
                  paths[edges[im].node1]=(path){cost,curr,false};
               }
            }
         }
         //Find next lowest path
         long long int low_cost=INF;
         for(long long int in=0;in<n;in++) {
            if(paths[in].done) continue;
            if(paths[in].cost<low_cost) {
                low_cost=paths[in].cost;
                curr=in;
            }
         }
         paths[curr].done=true;
      }
      for(long long int in=0;in<n;in++) {
         if(in!=s)printf("%lld ",paths[in].cost==INF?-1:paths[in].cost);
      }
      printf("\n");
   }

   return 0;
}

