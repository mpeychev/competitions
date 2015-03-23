#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <queue>

#define pb push_back

using namespace std;

struct segment {
    int x1, y1;
    int x2, y2;
};

struct el {
    int to, rd, prv;

    el() {}
    el(int _to, int _rd, int _prv): to(_to), rd(_rd), prv(_prv) {}
};

const int INF = 1 << 30;

int n;
segment s;
vector< segment > hor, ver;

int source, sink;
int idx[1 << 8], cpy[1 << 8];
el g[1 << 17];
int sz;
int level[1 << 8];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d %d %d %d", &s.x1, &s.y1, &s.x2, &s.y2);
        if(s.x1 == s.x2) {
            if(s.y1 > s.y2) swap(s.y1, s.y2);
            ver.pb(s);
        }
        else {
            if(s.x1 > s.x2) swap(s.x1, s.x2);
            hor.pb(s);
        }
    }
}

void add(int a, int b, int c) {
    //cout << a << " " << b << " " << c << endl;
    g[sz] = el(b, c, idx[a]);
    idx[a] = sz ++;
    g[sz] = el(a, 0, idx[b]);
    idx[b] = sz ++;
}

void build() {
    memset(idx, -1, sizeof(idx));
    source = n;
    sink = n + 1;

    for(int i = 0; i < hor.size(); i ++)
        add(source, i, 1);

    for(int i = 0; i < hor.size(); i ++)
        for(int j = 0; j < ver.size(); j ++)
            if(hor[i].y1 >= ver[j].y1 && hor[i].y1 <= ver[j].y2 &&
               ver[j].x1 >= hor[i].x1 && ver[j].x1 <= hor[i].x2)
                    add(i, j + hor.size(), 1);

    for(int i = 0; i < ver.size(); i ++)
        add(i + hor.size(), sink, 1);
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

        for(int i = idx[tmp]; i != -1; i = g[i].prv)
            if(level[ g[i].to ] == -1 && g[i ^ 1].rd) {
                level[ g[i].to ] = level[tmp] + 1;
                q.push(g[i].to);
            }
    }

    return level[source] != -1;
}

int dfs(int cur, int flow) {
    if(cur == sink)
        return flow;

    for(int &i = cpy[cur]; i != -1; i = g[i].prv)
        if(level[cur] - 1 == level[ g[i].to ] && g[i].rd) {
            int fl = dfs(g[i].to, min(flow, g[i].rd));
            if(fl) {
                g[i].rd -= fl;
                g[i ^ 1].rd += fl;
                return fl;
            }
        }

    level[cur] = -42;
    return 0;
}

int dinitz() {
    int maxFlow = 0, curFlow;
    while(bfs()) {
        memcpy(cpy, idx, sizeof(idx));
        while(curFlow = dfs(source, INF))
            maxFlow += curFlow;
    }
    //cout << maxFlow << endl;
    return maxFlow;
}

int main()
{
    read();

    if(hor.empty() || ver.empty()) {
        printf("%d\n", n);
        return 0;
    }

    build();
    printf("%d\n", n - dinitz());

    return 0;
}
