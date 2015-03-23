#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 1 << 19;

int n, m;
int w[MAXN];
int prenum[MAXN], last[MAXN], cnt;
vector<int> nxt[MAXN];
int t[2 * MAXN], lvs;

void read() {
    scanf("%d %d", &n, &m);
    scanf("%d", &w[1]);
    for(int i = 2; i <= n; i ++) {
        int prv;
        scanf("%d %d", &w[i], &prv);
        nxt[prv].pb(i);
    }
}

void dfs(int cur) {
    prenum[cur] = cnt;
    for(int i = 0; i < nxt[cur].size(); i ++) {
        cnt ++;
        dfs(nxt[cur][i]);
    }
    last[cur] = cnt;
}

void update(int idx, int le, int ri, int a, int b, int val) {
    if(ri < a || b < le)
        return;
    if(a <= le && ri <= b) {
        t[idx] += val;
        return;
    }

    int mid = (le + ri) >> 1;
    update(idx << 1, le, mid, a, b, val);
    update((idx << 1) + 1, mid + 1, ri, a, b, val);
}

int get(int idx) {
    int ret = 0;
    while(idx) {
        ret += t[idx];
        idx >>= 1;
    }
    return ret;
}

void solve() {
    lvs = 1;
    while(lvs < n) lvs <<= 1;

    scanf("\n");
    for( ; m; m --) {
        char cmd;
        int a, x;
        scanf("%c", &cmd);
        if(cmd == 'p') {
            scanf("%d %d\n", &a, &x);
            if(prenum[a] + 1 <= last[a])
                update(1, 0, lvs - 1, prenum[a] + 1, last[a], x);
        }
        else {
            scanf("%d\n", &a);
            printf("%d\n", w[a] + get(prenum[a] + lvs));
        }
    }
}

int main()
{
    read();
    dfs(1);
    solve();

    return 0;
}
