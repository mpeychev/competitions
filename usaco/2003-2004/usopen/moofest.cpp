/*
  Source: usaco - 2004 - usopen
  Task: moofest
  KeyW: bit
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>

#define v first
#define x second

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;

const int MAXA = 20000;

int n;
pii m[MAXA + 10];
// 0 - sum
// 1 - num
ll tree[2][MAXA + 10];

void update(int code,int index,int val)
{
    while(index<=MAXA)
    {
        tree[code][index]+=val;
        index+=(index & -index);
    }
}

ll sum(int code,int index)
{
    ll ret=0;
    while(index)
    {
        ret+=tree[code][index];
        index-=(index & -index);
    }
    return ret;
}

bool cmp(pii p1,pii p2)
{
    return p1.v<p2.v;
}

void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d %d",&m[i].v,&m[i].x);
    sort(m+1,m+n+1,cmp);
}

void solve()
{
    ll sol=0;
    update(0,m[1].x,m[1].x);
    update(1,m[1].x,1);
    for(int i=2;i<=n;i++)
    {
        ll l=sum(1,m[i].x);
        ll r=sum(1,MAXA)-l;
        ll sl=sum(0,m[i].x);
        ll sr=sum(0,MAXA)-sl;

        sol+=m[i].v*(l*m[i].x-sl+sr-r*m[i].x);

        update(0,m[i].x,m[i].x);
        update(1,m[i].x,1);
    }
    cout << sol << endl;
}

int main()
{
    //freopen("moofest.in","r",stdin);
    //freopen("moofest.out","w",stdout);

    init();
    solve();

    return 0;
}
