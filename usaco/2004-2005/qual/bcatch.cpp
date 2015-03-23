/*
  Source: usaco - 2004/2005 - qual
  Task: bcatch
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int t, w;
int d[1024];
int dp[1024][32][2];

void read()
{
    scanf("%d %d",&t,&w);
    for(int i = 0; i < t; i ++)
    {
        scanf("%d",&d[i]);
        d[i] %= 2;
    }
}

int f(int k, int walks, int where)
{
    if(k == t) return 0;
    if(dp[k][walks][where] != -1)
        return dp[k][walks][where];

    int ret, go;

    if(d[k] == where) ret = 1 + f(k + 1, walks, where);
    else
    {
        ret = f(k + 1, walks, where);
        if(walks)
        {
            go = 1 + f(k + 1, walks - 1, where ^ 1);
            if(ret < go) ret = go;
        }
    }

    dp[k][walks][where] = ret;
    return ret;
}

int main()
{
    read();
    memset(dp, -1, sizeof(dp));
    printf("%d\n",f(0, w, 1));

    return 0;
}
