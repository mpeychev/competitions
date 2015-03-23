/*
PROG: hamming
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int n,b,d;
int m[64],ind;
int e;

int dist(int x,int y)
{
    int b1[8],b2[8];
    for(int i=0;i<b;i++) b1[i]=(x>>i)&1;
    for(int i=0;i<b;i++) b2[i]=(y>>i)&1;
    int sol=0;
    for(int i=0;i<b;i++) if(b1[i]!=b2[i]) sol++;
    return sol;
}

void rec()
{
     if(ind==n)
     {
               for(int i=0;i<n;i++)
               {
                       printf("%d",m[i]);
                       if(i==n-1 || (i+1)%10==0) printf("\n");
                       else printf(" ");
               }
               exit(0);
     }
     for(int i=m[ind-1]+1;;i++)
     {
             bool fl=true;
             for(int j=0;j<ind;j++) if(dist(m[j],i)<d) { fl=false; break; }
             if(fl) { m[ind]=i; ind++; rec(); ind--; }
     }
}

int main()
{
    freopen("hamming.in","r",stdin);
    freopen("hamming.out","w",stdout);
    
    scanf("%d %d %d",&n,&b,&d);
    e=1<<(b+1)-1;
    
    m[0]=0; ind=1;
    rec();
    
    return 0;
}
