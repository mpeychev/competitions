/*
  Source: boi - 2003
  Task: Tribe council
  KeyW: Dvufazni dinamichni po dyrveta.
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 1 << 17;

struct el {
    int to, prv;

    el() {}
    el(int _to, int _prv): to(_to), prv(_prv) {}
};

int n, a, b;
el g[MAXN];
int idx[MAXN], sz;
int father[MAXN], cnt[MAXN];
int prenum[MAXN];
bool critical[MAXN];

void read() {
    memset(idx, -1, sizeof(idx));

    scanf("%d", &n);
    for(int i = 1; i < n; i ++) {
        scanf("%d %d", &a, &b);
        cnt[a] ++;
        cnt[b] ++;
        father[b] = a;
        g[sz] = el(b, idx[a]);
        idx[a] = sz ++;
    }
}

void bfs1() {
    queue<int> q;

    for(int i = 2; i <= n; i ++)
        if(cnt[i] == 1)
            q.push(i);

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        vector<int> children;
        for(int i = idx[u]; i != -1; i = g[i].prv)
            children.pb(prenum[ g[i].to ]);

        sort(children.begin(), children.end());

        prenum[u] = 1;
        for(int i = 0; i < children.size(); i ++)
            if(prenum[u] <= children[i])
                prenum[u] ++;

        cnt[ father[u] ] --;
        if(father[u] == 1) {
            if(cnt[ father[u] ] == 0) q.push(father[u]);
        }
        else {
            if(cnt[ father[u] ] == 1) q.push(father[u]);
        }
    }
}

void bfs2() {
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int u = q.front();
        q.pop();

        // find critical vertices
        vector<int> children;
        for(int i = idx[u]; i != -1; i = g[i].prv) {
            children.pb(prenum[ g[i].to ]);
            q.push(g[i].to);
        }

        sort(children.begin(), children.end());

        int l = -1;
        for(int i = 1; i < prenum[u]; i ++) {
            int pos = children.size() - i - 1;
            if(pos >= 0) {
                if(children[pos] < prenum[u] - i)
                    l = i;
            }
            else l = i;
        }

        for(int i = idx[u]; i != -1; i = g[i].prv)
            if(prenum[ g[i].to ] >= prenum[u] - l)
                critical[ g[i].to ] = true;

        // update prenum[u]
        if(father[u]) {
            vector<int> vec;

            if(critical[u]) vec.pb(prenum[ father[u] ] - 1);
            else vec.pb(prenum[ father[u] ]);

            for(int i = idx[u]; i != -1; i = g[i].prv)
                vec.pb(prenum[ g[i].to ]);

            sort(vec.begin(), vec.end());

            prenum[u] = 1;
            for(int i = 0; i < vec.size(); i ++)
                if(prenum[u] <= vec[i])
                    prenum[u] ++;
        }
    }
}

void answer() {
    int ans = -1;
    for(int i = 1; i <= n; i ++)
        if(ans < prenum[i])
            ans = prenum[i];
    printf("%d\n", ans);
}

int main()
{
    read();
    bfs1();
    bfs2();
    answer();

    return 0;
}
