/*
  Source: usaco - 2003/2004 - dec
  Task: cover
  KeyW: index tree; coordinates hashing
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define le first
#define ri second
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

int n;
PII m[25010];
vector<int> endPoints;
map<int, int> idx;
int tree[50010];
int mx, ans = 1;

void init()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d %d",&m[i].le,&m[i].ri);
        endPoints.pb(m[i].le);
        endPoints.pb(m[i].ri);
    }
    sort(endPoints.begin(), endPoints.end());

    for(int i = 0; i < endPoints.size(); i ++)
        idx[ endPoints[i] ] = i + 1;
    mx = idx[ endPoints[ 2 * n - 2 ] ];
}

bool cmp(PII a, PII b)
{
    return a.ri < b.ri;
}

void update(int ind)
{
    while(ind <= mx)
    {
        tree[ind] ++;
        ind += (ind & -ind);
    }
}

int sum(int ind)
{
    int ret = 0;
    while(ind)
    {
        ret += tree[ind];
        ind -= (ind & -ind);
    }
    return ret;
}

void solve()
{
    sort(m, m + n, cmp);

    for(int i = 0; i < n; i ++)
    {
        ans = max(ans, sum(idx[ m[i].ri ]) - sum(idx[ m[i].le ]));
        update(idx[ m[i].le ]);
    }
    printf("%d\n",ans);
}

int main()
{
    init();
    solve();

    return 0;
}
