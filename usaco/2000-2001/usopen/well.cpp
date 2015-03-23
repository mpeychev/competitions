/*
  Source: usaco - 2000/2001 - usopen
  Task: well
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

struct rubbish
{
    int t, f, h;
};

int d, g;
rubbish m[128];
int totalH;
int dp[3000];

bool cmp(rubbish a, rubbish b)
{
    return a.t < b.t;
}

void init()
{
    scanf("%d %d",&d,&g);
    for(int i = 0; i < g; i ++)
        scanf("%d %d %d",&m[i].t,&m[i].f,&m[i].h);
    sort(m, m + g, cmp);
}

void solve()
{
    dp[0] = 10;
    for(int i = 0; i < g; i ++)
    {
        for(int j = totalH + m[i].h; j >= 0; j --)
        {
            if(dp[j] >= m[i].t)
            {
                if(dp[j]) dp[j] += m[i].f;
            }
            if(j - m[i].h >= 0 && dp[ j - m[i].h ] >= m[i].t)
            {
                if(dp[ j - m[i].h ])
                {
                    dp[j] = max(dp[j], dp[ j - m[i].h ]);
                    if(j >= d)
                    {
                        printf("%d\n",m[i].t);
                        return;
                    }
                }
            }
        }
        totalH += m[i].h;
    }
    printf("%d\n",dp[0]);
}

int main()
{
    init();
    solve();

    return 0;
}
