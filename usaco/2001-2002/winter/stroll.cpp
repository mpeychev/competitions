/*
  Source: usaco - 2001/2002 - winter
  Task: stroll
  KeyW: maximal cycle in special graph
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int nxt[30010];
int prenum[30010];
int c[30010], w;
int num, ans;

void read()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++)
        scanf("%d",&nxt[i]);
}

void dfs(int cur)
{
    prenum[cur] = num;
    c[cur] = w;
    num ++;

    if(!prenum[ nxt[cur] ]) dfs(nxt[cur]);
    else if(c[cur] == c[ nxt[cur] ]) ans = max(ans, prenum[ cur ] - prenum[ nxt[cur] ] + 1);
}

void solve()
{
    for(int i = 1; i <= n; i ++)
        if(!prenum[i])
        {
            w ++;
            c[i] = w;
            num = 1;
            dfs(i);
        }
    printf("%d\n",ans);
}

int main()
{
    read();
    solve();

    return 0;
}
