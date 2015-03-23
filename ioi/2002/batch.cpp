/*
  Source: ioi-2002
  Task: Batch Scheduling
  KeyW: dp - cut the inner cycle
*/
#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 10010;
const int MAXX = (int)2e9;

int n,s;
int x,y,t[MAXN],f[MAXN];
int dp[MAXN],cost,prev[MAXN];

inline int sumt(int l,int r) { return t[r]-t[l-1]; }
inline int sumf(int l,int r) { return f[r]-f[l-1]; }

void init()
{
    scanf("%d %d",&n,&s);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&x,&y);
        t[i]=t[i-1]+x;
        f[i]=f[i-1]+y;
    }
}

void solve()
{
    for(int i=1;i<=n;i++)
    {
        dp[i]=MAXX;
        for(int j=prev[i-1];j<=i;j++)
        {
            cost=dp[j-1]+(s+sumt(j,i))*sumf(j,n);
            if(dp[i]>cost)
            {
                dp[i]=cost;
                prev[i]=j;
            }
        }
    }

    printf("%d\n",dp[n]);
}

int main()
{
    init();
    solve();

    return 0;
}
