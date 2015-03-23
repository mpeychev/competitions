/*
PROG: treat
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int n;
int next[100010];
int dp[100010];
bool used[100010];

void f(int tmp)
{
    int beg=tmp;
    int br=0;
    int wtf;
    while(!used[tmp])
    {
        br++;
        used[tmp]=1;
        tmp=next[tmp];
        wtf=tmp;
        if(dp[tmp]) { br+=dp[tmp]; break; }
    }
    tmp=beg;
    dp[tmp]=br;
    
    bool fl=false;
    if(tmp==wtf) fl=true;
    int prev=dp[tmp];
    
    tmp=next[tmp];
    while(!dp[tmp])
    {
        if(fl) dp[tmp]=prev;
        else
        {
            dp[tmp]=prev-1;
            if(tmp==wtf) fl=true;
        }
        prev=dp[tmp];
        tmp=next[tmp];
    }
}

int main()
{
    freopen("treat.in","r",stdin);
    freopen("treat.out","w",stdout);
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&next[i]);
    
    for(int i=1;i<=n;i++)
     if(!dp[i])
      f(i);
    
    for(int i=1;i<=n;i++) printf("%d\n",dp[i]);
    
    return 0;
}
