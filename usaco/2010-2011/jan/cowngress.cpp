/*
  Source: usaco - 2010/2011 - jan
  Task: cowngress
  KeyW: 2-SAT
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXV = 2048;

int n, m;
int b, c;
char vb, vc;
vector<int> g[MAXV];
int source;
bool ma3x[MAXV][MAXV];

void init()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++)
    {
        scanf("%d %c %d %c", &b, &vb, &c, &vc);
        b --; c --;

        if(vb == 'Y') b = 2 * b;
        else b = 2 * b + 1;

        if(vc == 'Y') c = 2 * c;
        else c = 2 * c + 1;

        g[b ^ 1].pb(c);
        g[c ^ 1].pb(b);
    }
}

void dfs(int cur)
{
    if(cur != source) ma3x[source][cur] = 1;

    for(int i = 0; i < g[cur].size(); i ++)
        if(g[cur][i] != source && !ma3x[source][ g[cur][i] ])
            dfs(g[cur][i]);
}

void solve()
{
    for(int i = 0; i < 2 * n; i ++)
    {
        source = i;
        dfs(i);
    }

    for(int i = 0; i < 2 * n; i += 2)
        if(ma3x[i][i + 1] && ma3x[i + 1][i])
        {
            printf("IMPOSSIBLE\n");
            return;
        }

    for(int i = 0; i < 2 * n; i += 2)
        if(ma3x[i + 1][i]) printf("Y");
        else if(ma3x[i][i + 1]) printf("N");
        else printf("?");

    printf("\n");
}

int main()
{
    init();
    solve();

    return 0;
}
