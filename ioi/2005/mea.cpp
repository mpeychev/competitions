/*
  Source: ioi 2005, day1
  Task: mea
  KeyW: system of inequalities
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int n,m1,m2;
long long tmp,mn,mx;

int main()
{
    scanf("%d",&n);
    
    scanf("%d",&m1);
    tmp=m1;
    mn=tmp;
    
    scanf("%d",&m2);
    tmp=tmp+m1-m2;
    mx=tmp;
    m1=m2;
    for(int i=3;i<=n;i++)
    {
        scanf("%d",&m2);
        if(i&1)
        {
            tmp=tmp-m1+m2;
            if(mn>tmp) mn=tmp;
        }
        else
        {
            tmp=tmp+m1-m2;
            if(mx<tmp) mx=tmp;
        }
        m1=m2;
    }
    
    if(mn<mx) printf("0\n");
    else cout << mn-mx+1 << endl;

    return 0;
}
