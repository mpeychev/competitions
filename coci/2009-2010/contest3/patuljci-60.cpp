#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

int n, c;
vector<int> v[10010];
int m;

void init()
{
    scanf("%d %d",&n,&c);
    for(int i = 1; i <= n; i ++)
    {
        int x;
        scanf("%d",&x);
        v[x].pb(i);
    }
}

int ubound(int ind, int key) // the last <= key
{
    int l = 0, r = v[ind].size() - 1, mid;
    while(l < r)
    {
        mid = (l + r + 1) / 2;
        if(v[ind][mid] > key) r = mid - 1;
        else l = mid;
    }
    if(v[ind][l] <= key) return l;
    return -1;
}

int lbound(int ind, int key) // the first >= key
{
    int l = 0, r = v[ind].size() - 1, mid;
    while(l < r)
    {
        mid = (l + r) / 2;
        if(v[ind][mid] < key) l = mid + 1;
        else r = mid;
    }
    if(v[ind][l] >= key) return l;
    return -1;
}

int bs(int ind, int le, int ri)
{
    int up = ubound(ind, ri);
    int low = lbound(ind, le);
    if(up == -1 || low == -1) return 0;
    return up - low + 1;
}

void doit(int le, int ri)
{
    for(int i = 1; i <= c; i ++)
        if(v[i].size() != 0 && bs(i, le, ri) > (ri - le + 1) / 2)
        {
            printf("yes %d\n",i);
            return;
        }
    printf("no\n");
}

void solve()
{
    scanf("%d",&m);
    for(int i = 0; i < m; i ++)
    {
        int a, b;
        scanf("%d %d",&a,&b);
        doit(a, b);
    }
}

int main()
{
    init();
    solve();

    return 0;
}
