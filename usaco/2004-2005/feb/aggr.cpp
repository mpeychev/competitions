/*
  Source: usaco - 2004/2005 - feb
  Task: aggr
  KeyW: bs
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 100000 + 10;

int n, c;
int x[MAXN];
int idx;

bool check(int dist)
{
    int br = 1, idx = 1;
    for(int i = 2; i <= n; i ++)
        if(x[idx] + dist <= x[i])
        {
            idx = i;
            br ++;
        }
    return br >= c;
}

void solve()
{
    int l = 1, r = x[n], mid;

    while(l < r)
    {
        mid = (l + r + 1) / 2;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }

    printf("%d\n", l);
}

void init()
{
    scanf("%d %d", &n, &c);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &x[i]);
    sort(x + 1, x + n + 1);
}

int main()
{
    init();
    solve();

    return 0;
}
