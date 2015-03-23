/*
PROG: holstein
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int v;
int m[32];
int n;
int a[16][32];

int sol=16;
int d[16];

int main()
{
    freopen("holstein.in","r",stdin);
    freopen("holstein.out","w",stdout);
    
    scanf("%d",&v);
    for(int i=0;i<v;i++) scanf("%d",&m[i]);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
     for(int j=0;j<v;j++)
      scanf("%d",&a[i][j]);
    
    for(int i=0;i<(1<<(n+1));i++)
    {
            int cnt=0;
            int tmp[16];
            for(int j=0;j<n;j++) { tmp[n-j-1]=(i>>(n-j-1))&1; cnt+=tmp[n-j-1]; }
            
            if(sol<=cnt) continue;
            
            int sum[32]={0};
            for(int j=0;j<n;j++)
             if(tmp[j])
              for(int k=0;k<v;k++) sum[k]+=a[j][k];
            
            bool fl=true;
            for(int j=0;j<v;j++) if(sum[j]<m[j]) { fl=false; break; }
            
            if(fl)
            {
                  sol=cnt;
                  for(int j=0;j<n;j++) d[j]=tmp[j];
            }
    }
    
    printf("%d",sol);
    for(int i=0;i<n;i++) if(d[i]) printf(" %d",i+1);
    
    printf("\n");
    
    return 0;
}
