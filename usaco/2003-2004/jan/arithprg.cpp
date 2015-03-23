/*
  Source: usaco - 2003/2004 - jan
  Task: arithprg
  KeyW: dp + bs
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

int n;
int a[2048];
int dp[2048][2048];
PII data[2048];
int ans = 1;

bool cmp(PII t1, PII t2)
{
    if(t1.first < t2.first) return true;
    if(t1.first > t2.first) return false;
    return t1.second < t2.second;
}

void init()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);
        data[i] = mp(a[i], i);
    }

    sort(data + 1, data + n + 1, cmp);
}

int find(int idx, int key)
{
    int l = 1, r = n, mid;
    int ret = -1;
    while(l <= r)
    {
        mid = (l + r) / 2;
        if(data[mid].first < key) l = mid + 1;
        else if(data[mid].first > key) r = mid - 1;
        else if(data[mid].second >= idx) r = mid - 1;
        else
        {
            ret = data[mid].second;
            l = mid + 1;
        }
    }
    return ret;
}

void solve()
{
    for(int i = 0; i <= n; i ++)
        for(int j = 0; j <= n; j ++)
            dp[i][j] = 1;

    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j < i; j ++)
        {
            int nxt = 2 * a[j] - a[i];
            int idx = find(j, nxt);
            if(idx == -1) dp[i][j] = 2;
            else dp[i][j] = 1 + dp[j][idx];
            if(ans < dp[i][j]) ans = dp[i][j];
        }
    }

    printf("%d\n", ans);
}

int main()
{
    init();
    solve();

    return 0;
}
