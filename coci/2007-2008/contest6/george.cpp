#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define mp make_pair
#define pb push_back

using namespace std;

const int MAXN = (1 << 10);

typedef pair<int, int> PII;

struct cmp
{
    bool operator()(PII a, PII b)
    {
        return !(a.second < b.second);
    }
};

int n, m;
int a, b, k, g;
int t1, t2, l;
int list[MAXN];
int ma3x[MAXN][MAXN];
int closed[MAXN][MAXN];
vector< PII > adj[MAXN];
bool used[MAXN];

priority_queue< PII , vector< PII > , cmp > pq;

void init()
{
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &a, &b, &k, &g);
    for(int i = 0; i < g; i ++)
        scanf("%d", &list[i]);
    for(int i = 0; i < m; i ++)
    {
        scanf("%d %d %d", &t1, &t2, &l);
        ma3x[t1][t2] = ma3x[t2][t1] = l;
        adj[t1].pb(mp(t2, l));
        adj[t2].pb(mp(t1, l));
    }

    memset(closed, -1, sizeof(closed));

    int t = 0;
    for(int i = 0; i < g - 1; i ++)
    {
        closed[ list[i] ][ list[i + 1] ] = closed[ list[i + 1] ][ list[i] ] = t;
        t += ma3x[ list[i] ][ list[i + 1] ];
    }
}

int dijkstra()
{
    pq.push(mp(a, k));

    while(!pq.empty())
    {
        PII tmp = pq.top();
        pq.pop();

        if(used[tmp.first]) continue;
        used[tmp.first] = 1;

        if(tmp.first == b) return tmp.second;

        for(int i = 0; i < adj[tmp.first].size(); i ++)
        {
            int u = tmp.first;
            int v = adj[tmp.first][i].first;

            if(!used[v])
            {
                if(closed[u][v] == -1)
                {
                    pq.push(mp(v, tmp.second + adj[tmp.first][i].second));
                    continue;
                }

                if(tmp.second < closed[u][v] || tmp.second >= closed[u][v] + ma3x[u][v])
                {
                    pq.push(mp(v, tmp.second + adj[tmp.first][i].second));
                    continue;
                }

                pq.push(mp(v, closed[u][v] + 2 * ma3x[u][v]));
            }
        }
    }
}

int main()
{
    init();
    printf("%d\n", dijkstra() - k);

    return 0;
}
