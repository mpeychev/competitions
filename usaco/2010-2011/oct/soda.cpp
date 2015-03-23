/*
PROG: soda
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

#define mp make_pair

using namespace std;

typedef pair<int,int> pii;

const int MAXN = 50010;

int n,a,b;
int tmp,ans=-1;
pii m[2*MAXN];

bool cmp(pii a,pii b) { return a.first<b.first; }

void init()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&a,&b);
        m[2*i]=mp(a,1);
        m[2*i+1]=mp(b+1,-1);
    }
    sort(m,m+2*n,cmp);
}

void solve()
{
    tmp=1;
    for(int i=1;i<2*n;i++)
    {
        if(m[i].first!=m[i-1].first)
        {
            if(tmp>ans) ans=tmp;
        }
        tmp+=m[i].second;
    }
    printf("%d\n",ans);
}

int main()
{
    freopen("soda.in","r",stdin);
    freopen("soda.out","w",stdout);
    
    init();
    solve();
    
    return 0;
}
