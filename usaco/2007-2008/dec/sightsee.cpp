#include <stdio.h>
#include <iostream>
#include <vector>

#define mp make_pair
#define pb push_back

using namespace std;

const int MAXL = 1 << 10;
const double eps = 1e-6;
const double INF = 100;

typedef pair<int, int> PII;
typedef pair<int, double> PID;

int l, p, a, b, c;
int f[MAXL];
vector< PII > inp[MAXL];
vector< PID > g[MAXL];
double dist[MAXL];

void read() {
    scanf("%d %d", &l, &p);
    for(int i = 1; i <= l; i ++)
        scanf("%d", &f[i]);
    for(int i = 0; i < p; i ++) {
        scanf("%d %d %d", &a, &b, &c);
        inp[a].pb(mp(b, c));
    }

    for(int i = 1; i <= l; i ++) {
        g[i].resize(inp[i].size());
        for(int j = 0; j < inp[i].size(); j ++)
            g[i][j].first = inp[i][j].first;
    }
}

void build(double x) {
    for(int i = 1; i <= l; i ++)
        for(int j = 0; j < inp[i].size(); j ++)
            g[i][j].second = (double)inp[i][j].second - x * (double)f[i];
}

bool check() {
    for(int i = 1; i <= l; i ++)
        dist[i] = 0.0;

    for(int i = 0; i <= l; i ++)
        for(int u = 1; u <= l; u ++)
            for(int j = 0; j < g[u].size(); j ++) {
                int v = g[u][j].first;
                dist[v] = min(dist[v], dist[u] + g[u][j].second);
            }

    for(int u = 1; u <= l; u ++)
        for(int i = 0; i < g[u].size(); i ++) {
            int v = g[u][i].first;
            if(dist[u] + g[u][i].second < dist[v])
                return true;
        }

    return false;
}

void solve() {
    double le = 0.0, ri = INF, mid;
    for(int iter = 0; iter < 30 && ri - le > eps; iter ++) {
        mid = (le + ri) / 2.0;
        build(mid);
        if(check()) ri = mid;
        else le = mid;
    }

    if(le < eps) printf("0\n");
    else printf("%.2lf\n", 1/le);
}

int main()
{
    read();
    solve();

    return 0;
}
