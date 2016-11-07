#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXLEN 1024*1024 

typedef enum bool {false,true} bool;

void toascii(char s[]) {
   int i=MAXLEN-2;
   while(s[i]!='@')s[i--]+='0';
}

void fromascii(char s[]) {
   int i=MAXLEN-2;
   while(s[i]!='@')s[i--]-='0';
}

void print_ascii(char s[]) {
    int p=-1;while(s[++p]=='@');
    printf("%s\n",&s[p]);
}

void print_nums(char s[]) {
    for(int i=0;i<MAXLEN-1;i++)
       printf("%d ",s[i]);
    printf("\n");
}

void add(char sr[], char s1[], char s2[]){
   memcpy(sr,s1,MAXLEN);
   int i=MAXLEN-2;
   int c=0;
   while(s1[i]!='@'||s2[i]!='@'||c!=0) {
      int v1=s1[i]=='@'?0:s1[i];
      int v2=s2[i]=='@'?0:s2[i];
      int r=v1+v2+c;
      c=r>9;
      r=r%10;
      sr[i]=r;
      i--;
   }
}

void mul(char sr[], char s1[], char s, int o) {
   for(int i=0;i<MAXLEN-2-o;i++)sr[i]='@';
   for(int i=MAXLEN-2-o;i<MAXLEN-1;i++)sr[i]=0;// Leading 0's
   sr[MAXLEN-1]=0; //End of string
   int i=MAXLEN-2;
   int c=0;
   while(s1[i]!='@'||c!=0) {
      int v1=s1[i]=='@'?0:s1[i];
      int r=v1*s+c;
      c=r/10;
      r=r%10;
      sr[i-o]=r;
      i--;
   }
}

void mult(char sr[], char s1[], char s2[]) {
   char ac[MAXLEN];
   sprintf(ac,"0");
   int p=(int)strlen(ac);for(int i=MAXLEN-1;i>-1;i--)p<0?(ac[i]='@'):(ac[i]=ac[p--]);
   fromascii(ac);
   char sm[MAXLEN];
   char tp[MAXLEN];
   int i=MAXLEN-2;
   int o=0;
   while(s2[i]!='@') {
      int s=s2[i];
      mul(sm,s1,s,o);
      add(tp,ac,sm);
      memcpy(ac,tp,MAXLEN);
      i--;
      o++;
   }
   memcpy(sr,ac,MAXLEN);
}

int main() {
    int t0,t1,i,p;
    scanf("%d%d%d",&t0,&t1,&i);
    char s0[MAXLEN];
    char s1[MAXLEN];
    char s2[MAXLEN];
    char sq[MAXLEN];
    sprintf(s0,"%d",t0);
    sprintf(s1,"%d",t1);
    p=(int)strlen(s0);for(int i=MAXLEN-1;i>-1;i--)p<0?(s0[i]='@'):(s0[i]=s0[p--]); 
    p=(int)strlen(s1);for(int i=MAXLEN-1;i>-1;i--)p<0?(s1[i]='@'):(s1[i]=s1[p--]);
    fromascii(s0);fromascii(s1);
    for(int ii=0;ii<i-2;ii++) {
       mult(sq,s1,s1);
       add(s2,s0,sq);
       memcpy(s0,s1,MAXLEN);
       memcpy(s1,s2,MAXLEN);
    }
    toascii(s2);
    print_ascii(s2); 
    return 0;
}
