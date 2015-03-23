/*
PROG: frac1
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

struct fract
{
       int a,b;
};

fract x;
vector<fract> v;

int gcd(int a,int b)
{
    while(b!=0)
    {
               int r=a%b;
               a=b;
               b=r;
    }
    return a;
}

bool cmp(fract x,fract y)
{
     if(x.a*y.b<y.a*x.b) return true;
     return false;
}

int main()
{
    freopen("frac1.in","r",stdin);
    freopen("frac1.out","w",stdout);
    
    int n;
    scanf("%d",&n);
    
    x.a=0; x.b=1;
    v.push_back(x);
    
    for(int i=1;i<=n;i++)
     for(int j=i;j<=n;j++)
      if(gcd(i,j)==1) { x.a=i; x.b=j; v.push_back(x); }
    sort(v.begin(),v.end(),cmp);
    
    for(int i=0;i<v.size();i++) printf("%d/%d\n",v[i].a,v[i].b);
    
    return 0;
}
