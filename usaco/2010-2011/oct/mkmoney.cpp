/*
PROG: mkmoney
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>

using namespace std;

typedef pair<int,int> Curio;

const int MAXN = (1<<7);
const int MAXM = 100010;

int n,m;
Curio g[MAXN];
int dp[MAXM],ans;

void init()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
        scanf("%d %d",&g[i].first,&g[i].second);
}

void solve()
{
    for(int i=1;i<=m;i++)
	{
		dp[i]=i;
        for(int j=0;j<n;j++)
            if(i-g[j].first>=0 && dp[i]<dp[i-g[j].first]+g[j].second-g[j].first)
                dp[i]=dp[i-g[j].first]+g[j].second-g[j].first;
	}
    for(int i=0;i<=m;i++)
        if(ans<dp[i])
            ans=dp[i];
    
    printf("%d\n",ans);
}

int main()
{
    freopen("mkmoney.in","r",stdin);
    freopen("mkmoney.out","w",stdout);
    
    init();
    solve();
    
    return 0;
}
