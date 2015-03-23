/*
  Source: usaco - 2001/2002 - fall
  Task: plumb
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

#define mp make_pair
#define len first
#define cap second

using namespace std;

typedef pair<int, int> PII;

int d, p;
PII pipes[512];
bool dp[100100];

bool cmp(PII a, PII b)
{
    return a.cap < b.cap;
}

void init()
{
    scanf("%d %d",&d,&p);
    for(int i = 0; i < p; i ++)
        scanf("%d %d",&pipes[i].len,&pipes[i].cap);
    sort(pipes, pipes + p, cmp);
}

void solve()
{
    dp[0] = 1;
    for(int i = p - 1; i >= 0; i --)
    {
        for(int j = d; j - pipes[i].len >= 0; j --)
            if(dp[j - pipes[i].len])
                dp[j] = 1;

        if(dp[d])
        {
            printf("%d\n",pipes[i].cap);
            return;
        }
    }
    printf("0\n");
}

int main()
{
    init();
    solve();

    return 0;
}
