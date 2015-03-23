#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define pb push_back

using namespace std;

const int INF = 1000000000;

struct el {
    int to, rd, nxt;

    el() {}
    el(int _to, int _rd, int _nxt): to(_to), rd(_rd), nxt(_nxt) {}
};

int c, l;
pair<int, int> range[2525];
int num[1024];
int idx[4000], cpy[4000];
int source, sink;
vector<el> g;
int level[4000];

void add(int a, int b, int c) {
    g.pb(el(b, c, idx[a]));
    idx[a] = g.size() - 1;
    g.pb(el(a, 0, idx[b]));
    idx[b] = g.size() - 1;
}

void init() {
    scanf("%d %d", &c, &l);
    source = 0;
    sink = c + 1000 + 1;

    for(int i = 1; i <= c; i ++)
        add(source, i, 1);

    for(int i = 1; i <= c; i ++)
        scanf("%d %d", &range[i].first, &range[i].second);

    for(int i = 1; i <= l; i ++) {
        int x, y;
        scanf("%d %d", &x, &y);
        num[x] += y;
    }

    for(int i = 1; i <= c; i ++)
        for(int j = range[i].first; j <= range[i].second; j ++)
            if(num[j])
                add(i, c + j, 1);

    for(int i = 1; i <= 1000; i ++)
        if(num[i])
            add(c + i, sink, num[i]);
}

bool bfs(int cur) {
    memset(level, -1, sizeof(level));
    queue<int> q;

    q.push(cur);
    level[cur] = 0;
    while(!q.empty()) {
        cur = q.front();
        q.pop();

        if(cur == source) return true;

        for(int i = idx[cur]; i != -1; i = g[i].nxt)
            if(level[ g[i].to ] == -1 && g[i ^ 1].rd) {
                level[ g[i].to ] = level[cur] + 1;
                q.push(g[i].to);
            }
    }

    return (level[source] != -1);
}

int dfs(int cur, int flow) {
    if(cur == sink)
        return flow;

    for(int &i = cpy[cur]; i != -1; i = g[i].nxt)
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
    int ret = 0, curFlow;
    while(bfs(sink)) {
        memcpy(cpy, idx, sizeof(idx));
        while((curFlow = dfs(source, INF)))
            ret += curFlow;
    }
    return ret;
}

int main()
{
    memset(idx, -1, sizeof(idx));
    init();
    printf("%d\n", dinitz());

    return 0;
}
