#include <stdio.h>
#include <string.h>

#define N 10001

int A[N];
int B[N];
int in[N];

int format;

int comp(const int* a, const int* b) {
    return (*a)-(*b);
}

char buf[1000],c[1000];

FILE *f, *fs;

int main(int argc, char **argv) {
   int cmax, n, max, i, j, per;

   f = fopen(argv[1],"r");
   fs = fopen(argv[2],"r");

   fscanf(f,"%d", &n);
      max = 0;
      memset(A,0,sizeof(A));
      memset(in,0,sizeof(in));
      for(i = 0; i < n; i++) {
          int d;
          fscanf(f,"%d", &d);
          A[d]++;
          in[i] = d;
          if(A[d]>max) max = A[d];
      }
      fscanf(fs, "%d",&cmax);
      if (max != cmax) {
        printf("0\nWrong Answer\n");
        return 0;
      }
      
      per = ((n+max-1)/max);
      for (i=0;i<n;i++) {  
         int d;
         fscanf(fs, "%[ \n]%d",c,&d);
         if (strlen(c) != 1) format = 1;
         if (c[strlen(c)-1] == '\n') {
            j = 0;
            memset(B,0,sizeof(B));
         }
         if (--A[d] < 0) {
            printf("0\nWrong number of pieces\n");
            return 0;
         }
         if (B[d]++) {
            printf("0\nDuplicate piece in one cake\n");
            return 0;
         }
         if (++j > per) {
            printf("0\nToo many pieces on one cake\n");
            return 0;
         }
      }
   if (format) {printf("0\nFormat error\n");return 0;}
   printf("10\nOK\n");
   return 0;
}
