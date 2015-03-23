#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int MAXN = 1 << 8;
const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct el {
    int to, rd, prv;

    el() {}
    el(int _to, int _rd, int _prv): to(_to), rd(_rd), prv(_prv) {}
};

int n, m, cur;
int ma3x[MAXN][MAXN];

int source, sink;
int idx[40100], cpy[40100];
int level[40100];
el g[1 << 20];
int sz;

void read() {
    int x, y;

    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &x, &y);
        ma3x[x][y] = -1;
    }
}

void add(int a, int b) {
    g[sz] = el(b, 1, idx[a]);
    idx[a] = sz ++;

    g[sz] = el(a, 0, idx[b]);
    idx[b] = sz ++;
}

void build() {
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(ma3x[i][j] != -1)
                ma3x[i][j] = ++cur;

    source = 0;
    sink = cur + 1;

    memset(idx, -1, sizeof(idx));
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(ma3x[i][j] != -1) {
                if((i + j) & 1) add(ma3x[i][j], sink);
                else add(source, ma3x[i][j]);
            }

    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(ma3x[i][j] != -1 && (i + j) % 2 == 0)
                for(int k = 0; k < 8; k ++) {
                    int i2, j2;
                    i2 = i + dx[k];
                    j2 = j + dy[k];
                    if(i2 >= 1 && i2 <= n && j2 >= 1 && j2 <= n && ma3x[i2][j2] != -1)
                        add(ma3x[i][j], ma3x[i2][j2]);
                }
}

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;

    q.push(sink);
    level[sink] = 0;
    while(!q.empty()) {
        int tmp = q.front();
        q.pop();

        if(tmp == source) return true;

        for(int i = idx[tmp]; i != -1; i = g[i].prv) {
            int nxt = g[i].to;
            if(level[nxt] == -1 && g[i ^ 1].rd) {
                level[nxt] = level[tmp] + 1;
                q.push(nxt);
            }
        }
    }

    return false;
}

bool dfs(int tmp) {
    if(tmp == sink)
        return true;

    for(int &i = cpy[tmp]; i != -1; i = g[i].prv) {
        int nxt = g[i].to;
        if(level[tmp] - 1 == level[nxt] && g[i].rd && dfs(nxt)) {
            g[i].rd --;
            g[i ^ 1].rd ++;
            return true;
        }
    }

    level[tmp] = -42;
    return false;
}

void solve() {
    int maxFlow = 0;
    while(bfs()) {
        memcpy(cpy, idx, sizeof(idx));
        while(dfs(source))
            maxFlow ++;
    }

    cout << n * n - m - maxFlow << endl;
}

int main()
{
    read();
    build();
    solve();

    return 0;
}
