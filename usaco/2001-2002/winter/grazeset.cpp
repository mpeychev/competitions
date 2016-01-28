/*
  Source: usaco - 2001/2002 - winter
  Task: grazeset
  KeyW: geometry - rotation
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int n, k;
double angle[10010], alpha;
int ans = 10010;
int cnt[1024];

void init()
{
    scanf("%d %d",&n,&k);
    alpha = 360.0 / (double)k;
    for(int i = 0; i < n; i ++)
        scanf("%lf",&angle[i]);
    sort(angle, angle + n);
}

void check(double betha)
{
    while(betha - alpha >= 0) betha -= alpha;

    memset(cnt, 0, sizeof(cnt));

    int j = 0;
    for(int i = 1; i < k; i ++)
    {
        while(j < n && angle[j] < betha + (double)(i - 1) * alpha) j ++;
        if(j < n)
        {
            int br = 0;
            while(j < n && angle[j] < betha + (double)i * alpha)
            {
                j ++;
                br ++;
            }
            cnt[i] = br;
        }
    }
    int mn = 10010, mx = -1;
    int s = 0;
    for(int i = 1; i < k; i ++)
    {
        if(mn > cnt[i]) mn = cnt[i];
        if(mx < cnt[i]) mx = cnt[i];
        s += cnt[i];
    }
    s = n - s;
    if(mn > s) mn = s;
    if(mx < s) mx = s;

    if(ans > mx - mn) ans = mx - mn;
}

void solve()
{
    check(0.0);
    for(int i = 0; i < n; i ++)
        check(angle[i]);
    printf("%d\n",ans);
}

int main()
{
    init();
    solve();

    return 0;
}
