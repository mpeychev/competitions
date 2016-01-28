/*
  Source: usaco - 2001/2002 - winter
  Task: party
  KeyW: matching; max flow
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

struct el
{
    int to, rd, next;

    el() {}
    el(int _to, int _rd, int _next): to(_to), rd(_rd), next(_next) {}
};

const int INF = 1000000;

int n, k, d;
int lim, br, type;
int source, sink;
int ind[512], sz;
el g[50000];

int level[512], now[512];
int curFlow, maxFlow;

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

    scanf("%d %d %d",&n,&k,&d);
    source = 0; sink = n + d + 1;
    for(int i = 1; i <= n; i ++)
        add(source, i, k);
    for(int i = 1; i <= d; i ++)
    {
        scanf("%d",&lim);
        add(n + i, sink, lim);
    }
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d",&br);
        for(int j = 0; j < br; j ++)
        {
            scanf("%d",&type);
            add(i, n + type, 1);
        }
    }
}

bool bfs(int cur)
{
    memset(level, -1, sizeof(level));
    queue<int> q;

    q.push(cur);
    level[cur] = 0;

    while(!q.empty())
    {
        cur = q.front();
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
        if(level[cur] - 1 == level[ g[i].to ] && g[i].rd)
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
    while(bfs(sink))
    {
        memcpy(now, ind, sizeof(ind));
        while((curFlow = dfs(source, INF)))
            maxFlow += curFlow;
    }

    printf("%d\n",maxFlow);
}

int main()
{
    init();
    dinitz();

    return 0;
}
