/*
PROG: range
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int n;
char s[256][256];

int sumr[256][256],sumc[256][256];
bool dp0[256][256],dp1[256][256];

int sol[256];

void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        char c;
        scanf("%c",&c);
        for(int j=1;j<=n;j++)
        {
            scanf("%c",&s[i][j]);
            if(s[i][j]=='1') dp0[i][j]=1;
            sumr[i][j]=sumr[i][j-1]+(s[i][j]-'0');
            sumc[j][i]=sumc[j][i-1]+(s[i][j]-'0');
        }
    }
}

void solve()
{
    for(int i=2;i<=n;i++)
    {
        memset(dp1,0,sizeof(dp1));
        for(int x=1;x+i-1<=n;x++)
         for(int y=1;y+i-1<=n;y++)
          if(dp0[x][y] && sumr[x+i-1][y+i-1]-sumr[x+i-1][y-1]==i && sumc[y+i-1][x+i-1]-sumc[y+i-1][x-1]==i)
          {
                dp1[x][y]=1;
                sol[i]++;
          }
        for(int x=1;x<=n;x++)
         for(int y=1;y<=n;y++)
          dp0[x][y]=dp1[x][y];
    }
}

void ans()
{
    for(int i=2;i<=n;i++)
    {
        if(!sol[i]) break;
        printf("%d %d\n",i,sol[i]);
    }
}

int main()
{
    freopen("range.in","r",stdin);
    freopen("range.out","w",stdout);
    
    init();
    solve();
    ans();
    
    return 0;
}
