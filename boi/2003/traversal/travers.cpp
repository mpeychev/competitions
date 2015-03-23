/*
  Source: boi - 2003
  Task: traversal
  KeyW: bit
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <set>

#define mp make_pair
#define height first
#define index second

using namespace std;

typedef pair<int,int> pii;

const int mod = 9901;
const int MAXN = 100000 + 10;

int n,h;
int tree[MAXN];
int a[MAXN];
pii s[MAXN];
set<int> data;
set<int>:: iterator lb,ub,it;
int sol;

bool cmp(pii x,pii y) { return (x.height<y.height); }

void update(int ind,int val)
{
    while(ind<=n)
    {
        tree[ind]=(tree[ind]+val)%mod;
        ind+=(ind & -ind);
    }
}

int sum(int ind)
{
    int ret=0;
    while(ind)
    {
        ret=(ret+tree[ind])%mod;
        ind-=(ind & -ind);
    }
    return ret;
}

int get_idx(int v)
{
    int l=1,r=n,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(s[mid].height==v) return s[mid].index;
        else if(s[mid].height>v) r=mid-1;
        else l=mid+1;
    }
}

void init()
{
    scanf("%d %d",&n,&h);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=mp(a[i],0);
    }
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++) s[i].index=i;
}

void solve()
{
    update(get_idx(a[1]),1);
    data.insert(a[1]);

    for(int i=2;i<=n;i++)
    {
        int tmp=0;

        lb=data.lower_bound(a[i]-h);
        ub=data.lower_bound(a[i]+h);

        if(ub==data.begin())
            if(*ub<a[i]+h) goto go1;
            else goto go2;

        if(ub==data.end() || *ub>a[i]+h)ub--;

        go2:
        if(lb!=data.end() && *ub<=a[i]+h)
        {
            //cout << a[i] << " " << *lb << " " << *ub << endl;
            tmp=sum( get_idx(*ub) )-sum( get_idx(*lb)-1 )+mod;
        }

        go1:
        sol=(sol+tmp)%mod;

        update(get_idx(a[i]),tmp+1);
        data.insert(a[i]);
    }

    printf("%d\n",sol);
}

int main()
{
    init();
    solve();

    return 0;
}
