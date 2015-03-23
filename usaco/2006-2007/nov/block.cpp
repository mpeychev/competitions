/*
  Source: usaco - 2006/2007 - nov
  Task: block
  KeyW: second shortest path; modified dijkstra
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

int n, r;
int a, b, d;
vector< PII > g[5010];
int dist = -1;
int used[5010];

priority_queue< PII , vector< PII > , cmp > pq;

void init()
{
    scanf("%d %d", &n, &r);
    for(int i = 0; i < r; i ++)
    {
        scanf("%d %d %d", &a, &b, &d);
        g[a].pb(mp(b, d));
        g[b].pb(mp(a, d));
    }
}

void dijkstra()
{
    pq.push(mp(1, 0));
    while(!pq.empty())
    {
        PII tmp = pq.top();
        pq.pop();

        if(tmp.first == n)
        {
            if(dist == -1) dist = tmp.second;
            else if(tmp.second > dist)
            {
                printf("%d\n", tmp.second);
                return;
            }
        }

        if(used[tmp.first] == 2) continue;
        used[tmp.first] ++;

        for(int i = 0; i < g[tmp.first].size(); i ++)
            if(used[ g[tmp.first][i].first ] < 2)
                pq.push(mp(g[tmp.first][i].first, tmp.second + g[tmp.first][i].second));
    }
}

int main()
{
    init();
    dijkstra();

    return 0;
}
