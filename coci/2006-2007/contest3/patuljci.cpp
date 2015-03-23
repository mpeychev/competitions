#include <stdio.h>

#define n 9

int m[16],s;

int main()
{
    for(int i=0;i<n;i++) { scanf("%d",&m[i]); s+=m[i]; }
    
    for(int i=0;i<n;i++)
     for(int j=i+1;j<n;j++)
      if(s-m[i]-m[j]==100)
      {
            for(int k=0;k<n;k++) if(k!=i && k!=j) printf("%d\n",m[k]);
            return 0;
      }
}
