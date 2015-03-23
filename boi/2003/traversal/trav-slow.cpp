/*
  Source: boi - 2003
  Task: traversal
  KeyW: dp - slow
*/
#include <stdio.h>
#include <iostream>

using namespace std;

const int mod = 9901;

int n,h;
int m[100010];
int dp[100010];
int sol,tmp;

int main()
{
    scanf("%d %d",&n,&h);
    for(int i=0;i<n;i++) scanf("%d",&m[i]);

    dp[0]=1;
    for(int i=1;i<n;i++)
    {
        tmp=0;
        for(int j=0;j<i;j++)
            if(m[i]-h<=m[j] && m[j]<=m[i]+h)
                tmp+=dp[j];
        dp[i]=(tmp+1)%mod;
        sol=(sol+tmp)%mod;
    }

    printf("%d\n",sol);

    return 0;
}
