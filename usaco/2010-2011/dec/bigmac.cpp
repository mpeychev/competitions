#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#define pb push_back

using namespace std;

const int MAXN = 1 << 11;
const long double INF = 1e50;

struct edge {
    int to;
    double rate;

    edge() {}
    edge(int _to, double _rate): to(_to), rate(_rate) {}
};

int n, m, a, b, x, y;
long double v;
double r;
vector< edge > g[MAXN];
long double dist[MAXN];

void read() {
    cin >> n >> m >> v >> a >> b;
    for(int i = 0; i < m; i ++) {
        cin >> x >> y >> r;
        g[x].pb(edge(y, log(r)));
    }
}

void solve() {
    for(int i = 1; i <= n; i ++)
        dist[i] = INF;
    dist[a] = 0.0;

    for(int k = 1; k <= n; k ++)
        for(int i = 1; i <= n; i ++)
            for(int h = 0; h < g[i].size(); h ++) {
                int j = g[i][h].to;
                double e = g[i][h].rate;

                if(dist[j] > dist[i] + e)
                    dist[j] = dist[i] + e;
            }

    for(int i = 1; i <= n; i ++)
        for(int h = 0; h < g[i].size(); h ++) {
            int j = g[i][h].to;
            double e = g[i][h].rate;

            if(dist[j] > dist[i] + e) {
                printf("0\n");
                return;
            }
        }

    long double ans = exp(dist[b]) * v;
    printf("%.8Lf\n", ans);
}

int main()
{
    read();
    solve();

    return 0;
}
