/*
  Source: usaco-usopen-green-2002
  Task: Planinski velichiq
  KeyW: Obrabotka na elementite siakash vseki e posleden.
        Obrabotka na ravninata po lenti.
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

#define l first
#define r second

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;

const int MAXN = 100010;

int n,ind;
pii m[MAXN];
ll sol;

ll SQU(ll a) { return a*a; }

bool cmp(pii a,pii b)
{
    if(a.l<b.l) return true;
    if(a.l>b.l) return false;
    if(a.r>b.r) return true;
    return false;
}

void init()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d %d",&m[i].l,&m[i].r);

    sort(m,m+n,cmp);
}

void solve()
{
    sol+=SQU(m[0].r-m[0].l);
    ind=0;
    for(int i=1;i<n;i++)
    {
        if(m[i].r<=m[ind].r) continue;
        sol+=SQU(m[i].r-m[i].l);
        if(m[i].l<m[ind].r) sol-=SQU(m[ind].r-m[i].l);
        ind=i;
    }

    cout << sol << endl;
}

int main()
{
    init();
    solve();

    return 0;
}
