/*
  Source: usaco - 2000 / 2001 - usopen
  Task: quake
  KeyW: bs on the answer , mst
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define pb push_back
#define mp make_pair

using namespace std;

const double eps = 1e-6;
const int MAXN = (1 << 9);

typedef pair<int, double> PID;

struct node
{
    int dest;
    double c, t;

    node() {}
    node(int _dest, double _c, double _t): dest(_dest), c(_c), t(_t) {}
};

struct cmp
{
    bool operator()(PID a, PID b)
    {
        return !(b.second - a.second > eps);
    }
};

int n, m;
double f;
vector< node > g[MAXN];
bool used[MAXN];

void read()
{
    scanf("%d %d %lf", &n, &m, &f);
    for(int i = 0; i < m; i ++)
    {
        int a, b;
        double c, t;

        scanf("%d %d %lf %lf", &a, &b, &c, &t);
        g[a].pb(node(b, c, t));
        g[b].pb(node(a, c, t));
    }
}

bool mst(double x)
{
    double cost = 0.0;

    priority_queue< PID , vector< PID > , cmp > pq;
    memset(used, 0, sizeof(used));

    pq.push(mp(1, 0));

    while(!pq.empty())
    {
        PID tmp = pq.top();
        pq.pop();

        if(used[tmp.first]) continue;
        cost += tmp.second;
        used[tmp.first] = true;

        if(cost - f > eps) return false;

        for(int i = 0; i < g[tmp.first].size(); i ++)
            if(!used[ g[tmp.first][i].dest ])
                pq.push(mp(g[tmp.first][i].dest, g[tmp.first][i].t * x + g[tmp.first][i].c));
    }

    return true;
}

void solve()
{
    if(!mst(0.0))
    {
        printf("0.0000\n");
        return;
    }

    double l = 0, r = f, mid;
    for(int i = 0; i < 100 && r - l > eps; i ++)
    {
        mid = (l + r) / 2.0;
        if(mst(mid)) l = mid;
        else r = mid - eps;
    }

    printf("%.4lf\n", l);
}

int main()
{
    read();
    solve();

    return 0;
}
