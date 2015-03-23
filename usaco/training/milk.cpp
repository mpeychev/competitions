/*
PROG: milk
LANG: C++
ID: mompej951
*/
#include <iostream>
#include <algorithm>
using namespace std;

struct milk
{
       int p;
       long a;
};

milk arr[4096*2];

bool cmp(milk x,milk y)
{
     if(x.p<y.p) return true;
     if(x.p==y.p && x.a>y.a) return true;
     return false;
}

int main()
{
    freopen("milk.in","r",stdin);
    freopen("milk.out","w",stdout);
    
    long n;
    int m;
    
    scanf("%ld %d",&n,&m);
    for(int i=0;i<m;i++) scanf("%d %ld",&arr[i].p,&arr[i].a);
    
    sort(arr,arr+m,cmp);
    
    long long sol=0;
    
    for(int i=0;i<m;i++)
    {
            long b;
            if(arr[i].a>n) b=n;
            else b=arr[i].a;
            sol+=b*arr[i].p;
            n-=b;
    }
    
    printf("%lld\n",sol);

    return 0;
}
