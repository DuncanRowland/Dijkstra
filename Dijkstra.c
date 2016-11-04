#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 99

typedef struct edge {
   int from;
   int to;
   int value;
} edge;

typedef enum node {A,B,C,D,E,F,G,NaN} node;
int NUMNODES=NaN;
char N(i) {
   static char N[]={'A','B','C','D','E','F','G'};
   return N[i];
}

int NUMEDGES=24;
edge e[]={
   {A,B,3},
   {A,C,5},
   {A,D,6},
   {B,A,3},
   {B,D,2},
   {C,A,5},
   {C,D,2},
   {C,E,6},
   {C,F,3},
   {C,G,7},
   {D,B,2},
   {D,A,6},
   {D,C,2},
   {D,F,9},
   {E,C,6},
   {E,F,5},
   {E,G,2},
   {F,C,3},
   {F,D,9},
   {F,E,5},
   {F,G,1},
   {G,C,7},
   {G,E,2},
   {G,F,1}
};

typedef struct path {
   bool finished; //Node Finished (already optimal)
   int value;     //Total Value for Current Best Path
   node prev;     //Previous Node in Path
} path;

int main() {

   path *p=(path*)malloc(sizeof(path)*NUMNODES);
   for(int n=0;n<NUMNODES;n++) {
      p[n]=(path){false,INF,NaN};
   }

   p[A].finished=true;p[A].value=0;p[A].prev=A;
   node curr=A;

   for(int n=0;n<NUMNODES;n++) {
      for(int m=0;m<NUMEDGES;m++) {
         if(e[m].from==curr) {
            int value=p[curr].value+e[m].value;
            if(value < p[e[m].to].value){
               p[e[m].to].value=value;
               p[e[m].to].prev=curr;
            }
         }
      }
      curr=NaN;
      for(int m=0;m<NUMNODES;m++) {
         if(!p[m].finished && (curr==NaN || p[m].value<p[curr].value)) {
            curr=m;
         }
      }
      p[curr].finished=true;
   }

   for(int n=0;n<NUMNODES;n++) {
      printf("A->%c\t=\t%d\t(%c)\n",N(n),p[n].value,N(p[n].prev));
   }

   free(p);
}
