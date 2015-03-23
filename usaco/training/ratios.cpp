/*
PROG: ratios
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int x,y,z;
int x1,y1,z1;
int x2,y2,z2;
int x3,y3,z3;

int sol1=101,sol2=101,sol3=101,solm;

int main()
{
    freopen("ratios.in","r",stdin);
    freopen("ratios.out","w",stdout);
    
    scanf("%d %d %d",&x,&y,&z);
    scanf("%d %d %d",&x1,&y1,&z1);
    scanf("%d %d %d",&x2,&y2,&z2);
    scanf("%d %d %d",&x3,&y3,&z3);
    
    if(!x && !y && !z) { printf("NONE\n"); return 0; }
    
    for(int a=0;a<=100;a++)
     for(int b=0;b<=100;b++)
      for(int c=0;c<=100;c++)
       if(a+b+c<sol1+sol2+sol3)
       {
            int sum1=a*x1 + b*x2 + c*x3;
            if(x && sum1%x) continue;
            if(!x && sum1)  continue;
            
            int sum2=a*y1 + b*y2 + c*y3;
            if(y && sum2%y) continue;
            if(!y && sum2)  continue;
            
            int sum3=a*z1 + b*z2 + c*z3;
            if(z && sum3%z) continue;
            if(!z && sum3)  continue;
            
            int m;
            if(x) m=sum1/x;
            else if(y) m=sum2/y;
            else if(z) m=sum3/z;
            
            if(!m) continue;
            
            if(m*x!=sum1) continue;
            if(m*y!=sum2) continue;
            if(m*z!=sum3) continue;
            
            sol1=a; sol2=b; sol3=c; solm=m;
       }
    
    if(sol1!=101) printf("%d %d %d %d\n",sol1,sol2,sol3,solm);
    else printf("NONE\n");
    
    return 0;
}
