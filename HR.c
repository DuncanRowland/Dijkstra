#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INF 9999

typedef enum bool {false,true} bool;

typedef struct edge {
   int node1;
   int node2;
} edge;

typedef struct path {
   int  cost;
   int  prev;
   bool done;
} path;

int main() {

   int q; //number of queries
   scanf("%d",&q);

   for(int iq=0;iq<q;iq++) {
      int n; //Number of nodes
      int m; //Number of edges
      scanf("%d%d",&n,&m);

      edge edges[m];
      for(int im=0;im<m;im++) {
         scanf("%d%d",&(edges[im].node1), &(edges[im].node2));
         edges[im].node1--; //Off by one user space
         edges[im].node2--; //Off by one user space
      }

      int s; //Starting node
      scanf("%d",&s);
      s--; //Off by one user space

      //Do Dijkstra
      path paths[n];
      for(int in=0;in<n;in++) paths[in]=(path){INF,-1,false};
      int curr=s;
      paths[s]=(path){0,s,true};
      //Find cost of path from each node to curr
      for(int in=0;in<n;in++) {
         for(int im=0;im<m;im++) {
            if(edges[im].node1==curr) {
               int cost=paths[curr].cost+6;
               if(cost<paths[edges[im].node2].cost) {
                  paths[edges[im].node2]=(path){cost,curr,false};
               }
            } else if(edges[im].node2==curr) {
               int cost=paths[curr].cost+6;
               if(cost<paths[edges[im].node1].cost) {
                  paths[edges[im].node1]=(path){cost,curr,false};
               }
            }
         }
         //Find next lowest path
         int low_cost=INF;
         for(int in=0;in<n;in++) {
            if(paths[in].done) continue;
            if(paths[in].cost<low_cost) {
                low_cost=paths[in].cost;
                curr=in;
            }
         }
         paths[curr].done=true;
      }
      for(int in=0;in<n;in++) {
         if(in!=s)printf("%d ",paths[in].cost==INF?-1:paths[in].cost);
      }
      printf("\n");
   }

   return 0;
}
