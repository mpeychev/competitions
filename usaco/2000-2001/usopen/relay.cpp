/*
  Source: usaco - 2000/2001 - usopen
  Task: relay
  KeyW: finding the first k shortest paths; modified dijkstra
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

struct cmp
{
    bool operator()(PII a, PII b)
    {
        return !(a.second < b.second);
    }
};

int k, n, m;
int a, b, c;
vector< PII > g[808];
int used[808];
priority_queue< PII , vector< PII > , cmp > pq;

void init()
{
    scanf("%d %d %d", &k, &n, &m);
    for(int i = 0; i < m; i ++)
    {
        scanf("%d %d %d", &a, &b, &c);
        g[a].pb(mp(b, c));
        g[b].pb(mp(a, c));
    }
}

void dijkstra()
{
    int counter = 0;
    int ans = 0;

    pq.push(mp(1, 0));
    while(!pq.empty())
    {
        PII tmp = pq.top();
        pq.pop();

        if(used[tmp.first] >= k) continue;
        used[tmp.first] ++;

        if(tmp.first == n)
        {
            counter ++;
            ans += tmp.second;

            if(counter == k) break;
        }
        else
        {
            for(int i = 0; i < g[tmp.first].size(); i ++)
                if(used[ g[tmp.first][i].first ] < k)
                    pq.push(mp(g[tmp.first][i].first, tmp.second + g[tmp.first][i].second));
        }
    }

    printf("%d\n",ans);
}

int main()
{
    init();
    dijkstra();

    return 0;
}
