/*
PROB: ditch
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <cstring>

const int INF = 1 << 30;

struct Edge {
    int to, cap, prv;

    Edge() {}
    Edge(int _to, int _cap, int _prv): to(_to), cap(_cap), prv(_prv) {}
};

int n, m;
Edge g[512];
int idx;
int prv[256];
bool used[256];

void addEdge(int a, int b, int c) {
    g[idx] = Edge(b, c, prv[a]);
    prv[a] = idx++;

    g[idx] = Edge(a, 0, prv[b]);
    prv[b] = idx++;
}

void read() {
    int a, b, c;
    memset(prv, -1, sizeof(prv));

    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b >> c;
        addEdge(a, b, c);
    }
}

long dfs(int node, int maxFlow) {
    used[node] = true;
    if (node == m) {
        return maxFlow;
    }
    for (int i = prv[node]; i != -1; i = g[i].prv) {
        if (!used[g[i].to] && g[i].cap > 0) {
            int curFlow = dfs(g[i].to, std::min(maxFlow, g[i].cap));
            if (curFlow) {
                g[i].cap -= curFlow;
                g[i ^ 1].cap += curFlow;
                return curFlow;
            }
        }
    }
    return 0;
}

void solve() {
    long flow = 0;
    while (true) {
        memset(used, 0, sizeof(used));
        long curFlow = dfs(1, INF);
        if (curFlow) {
            flow += curFlow;
        } else {
            break;
        }
    }
    std::cout << flow << std::endl;
}

int main()
{
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);

    read();
    solve();

    return 0;
}
