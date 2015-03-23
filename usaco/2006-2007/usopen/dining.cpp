/*
  Source: usaco - 2006/2007 - open
  Task: dinig
  KeyW: matching - max flow
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

const int INF = 100100;

struct el
{
    int to, rd, next;

    el() {}
    el(int _to, int _rd, int _next): to(_to), rd(_rd), next(_next) {}
};

int n, f, d;
int fsz, dsz;
int food, drink;

int source, sink;
int ind[512], now[512];
el g[50000];
int sz;
int curFlow, maxFlow;
int level[512];

void add(int a, int b, int c)
{
    g[sz] = el(b, c, ind[a]);
    ind[a] = sz ++;

    g[sz] = el(a, 0, ind[b]);
    ind[b] = sz ++;
}

void init()
{
    memset(ind, -1, sizeof(ind));

    scanf("%d %d %d",&n,&f,&d);

    source = 0;
    sink = n + 2 * f + d + 1;

    for(int i = 1; i <= f; i ++)
        add(source, i, 1);

    for(int i = 1; i <= n; i ++)
        add(f + i, f + n + i, 1);

    for(int i = 1; i <= n; i ++)
    {
        scanf("%d %d",&fsz,&dsz);

        for(int j = 0; j < fsz; j ++)
        {
            scanf("%d",&food);
            add(food, f + i, 1);
        }

        for(int j = 0; j < dsz; j ++)
        {
            scanf("%d",&drink);
            add(f + n + i, f + 2 * n + drink, 1);
        }
    }

    for(int i = 1; i <= d; i ++)
        add(f + 2 * n + i, sink, 1);
}

bool bfs()
{
    memset(level, -1, sizeof(level));
    queue<int> q;

    q.push(sink);
    level[sink] = 0;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        if(cur == source) break;

        for(int i = ind[cur]; i != -1; i = g[i].next)
            if(level[ g[i].to ] == -1 && g[i ^ 1].rd)
            {
                level[ g[i].to ] = level[cur] + 1;
                q.push(g[i].to);
            }
    }

    return (level[source] != -1);
}

int dfs(int cur, int flow)
{
    if(cur == sink) return flow;

    for(int &i = now[cur]; i != -1; i = g[i].next)
        if(level[ g[i].to ] + 1 == level[cur] && g[i].rd)
        {
            int fl = dfs(g[i].to, min(flow, g[i].rd));
            if(fl)
            {
                g[i].rd -= fl;
                g[i ^ 1].rd += fl;
                return fl;
            }
        }

    level[cur] = -42;
    return 0;
}

void dinitz()
{
    while(bfs())
    {
        memcpy(now, ind, sizeof(ind));
        while((curFlow = dfs(source, INF)))
            maxFlow += curFlow;
    }
}

int main()
{
    init();
    dinitz();
    printf("%d\n",maxFlow);

    return 0;
}
