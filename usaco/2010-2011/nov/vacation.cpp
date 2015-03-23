/*
PROG: vacation
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 50010;

int n,a,b;
vector<int> g[MAXN];
int dp[MAXN][2];

void read()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%d %d",&a,&b);
        g[a].pb(b);
        g[b].pb(a);
    }
}

int dfs(int cur,int fl,int prev)
{
    if(dp[cur][fl]!=-1) return dp[cur][fl];

    int ret=0;
    if(fl)
    {
        for(int i=0;i<g[cur].size();i++)
            if(g[cur][i]!=prev)
                ret+=dfs(g[cur][i],0,cur);
        dp[cur][fl]=ret+1;
    }
    else
    {
        for(int i=0;i<g[cur].size();i++)
            if(g[cur][i]!=prev)
                ret+=max( dfs(g[cur][i],1,cur) , dfs(g[cur][i],0,cur) );
        dp[cur][fl]=ret;
    }

    return dp[cur][fl];
}

int main()
{
    read();
    memset(dp,-1,sizeof(dp));
    printf("%d\n",max(dfs(1,0,-1),dfs(1,1,-1)));

    return 0;
}
