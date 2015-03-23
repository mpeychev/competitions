#include <stdio.h>
#include <iostream>
using namespace std;

typedef unsigned long long LL;

int n,c,d;
LL a,b,nok,sol;
int m[500010];
int used[500010];
int size[500010];

LL lcd(LL a, LL b)
{
    return (a*b)/__gcd(a,b);
}

int main()
{
    scanf("%d %lld %lld %d %d",&n,&a,&b,&c,&d);
    for(int i=1;i<=n;i++) scanf("%d",&m[i]);
    
    int ind=1;
    for(int i=1;i<=n;i++)
     if(!used[i])
     {
            int tmpsz=0;
            int wtf=i;
            while(!used[wtf])
            {
                used[wtf]=ind;
                wtf=m[wtf];
                tmpsz++;
            }
            size[ind]=tmpsz;
            ind++;
     }
    nok=1;
    for(int i=c+1;i<=n-d;i++)
    {
//        cout << i << " " << nok << " " << size[ used[i] ] << " " << lcd(nok,size[ used[i] ]) << endl;
        nok=lcd(nok,size[ used[i] ]);
        if(nok+1>b)
        {
            if(a==0) printf("1\n");
            else printf("0\n");
            return 0;
        }
    }
//    cout << nok << endl;
    for(int i=0;i*nok+1<=b;i++) if(i*nok+1>=a) sol++;
    
    printf("%lld\n",sol);
    
    return 0;
}
