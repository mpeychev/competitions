/*
  Source: usaco - 2004/2005 - qual
  Task: cowhome
  KeyW: dijkstra
*/
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

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

int t, n;
int a, b, c;
vector< PII > g[1024];
priority_queue< PII , vector< PII > , cmp > pq;
bool used[1024];

void init()
{
    scanf("%d %d",&t,&n);
    for(int i = 0; i < t; i ++)
    {
        scanf("%d %d %d",&a,&b,&c);
        g[a].pb(mp(b, c));
        g[b].pb(mp(a, c));
    }
}

int dijkstra()
{
    pq.push(mp(1, 0));
    while(!pq.empty())
    {
        PII tmp = pq.top();
        pq.pop();

        if(tmp.first == n) return tmp.second;
        if(used[tmp.first]) continue;
        used[tmp.first] = 1;

        for(int i = 0; i < g[tmp.first].size(); i ++)
            if(!used[ g[tmp.first][i].first ])
                pq.push(mp(g[tmp.first][i].first, tmp.second + g[tmp.first][i].second));
    }
}

int main()
{
    init();
    printf("%d\n",dijkstra());

    return 0;
}
