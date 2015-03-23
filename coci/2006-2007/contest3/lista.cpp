#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 19;

int n, m;
PII l[MAXN];
int vec[MAXN];
PII tree[MAXN];
int dp[MAXN];
int prv[MAXN];
vector<int> seq;

void init() {
    scanf("%d %d\n", &n, &m);

    l[0].second = 1;
    l[n + 1].first = n;
    for(int i = 1; i <= n; i ++)
        l[i] = mp(i - 1, i + 1);
}

void removeNode(int x) {
    int a = l[x].first;
    int b = l[x].second;
    l[a].second = b;
    l[b].first = a;
}

void addXAfterY(int x, int y) {
    l[x] = mp(y, l[y].second);
    l[ l[x].first ].second = x;
    l[ l[x].second ].first = x;
}

void read() {
    char cmd;
    int x, y;

    for(int i = 0; i < m; i ++) {
        scanf("%c %d %d\n", &cmd, &x, &y);

///        A) Move node X in front of node Y.
///        B) Move node X after node Y.

        if(cmd == 'A' && l[y].first == x) continue;
        if(cmd == 'B' && l[y].second == x) continue;

        removeNode(x);

        if(cmd == 'A') addXAfterY(x, l[y].first);
        else addXAfterY(x, y);
    }
}

void add(int idx, int val) {
    PII tmp = mp(val, idx);
    while(idx <= n) {
        if(tree[idx].first < tmp.first) tree[idx] = tmp;
        idx += (idx & -idx);
    }
}

PII getMax(int idx) {
    PII ret = mp(0, -1);
    while(idx) {
        if(tree[idx].first > ret.first) ret = tree[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

void solve() {
    int idx = 1;
    int cur = 0;
    while(l[cur].second != n + 1) {
        vec[idx ++] = l[cur].second;
        cur = l[cur].second;
    }

    for(int i = 1; i <= n; i ++)
        tree[i] = mp(0, -1);

    for(int i = 1; i <= n; i ++) {
        PII tmp = getMax(vec[i]);
        dp[ vec[i] ] = tmp.first + 1;
        prv[ vec[i] ] = tmp.second;
        add(vec[i], dp[ vec[i] ]);
    }

    int pos = 0;
    for(int i = 1; i <= n; i ++)
        if(dp[i] > dp[pos])
            pos = i;

    while(pos != -1) {
        seq.pb(pos);
        pos = prv[pos];
    }
    reverse(seq.begin(), seq.end());

    cout << (int)(n - seq.size()) << endl;
    for(int i = seq[0] - 1; i >= 1; i --)
        printf("A %d %d\n", i, i + 1);
    for(int i = seq.back() + 1; i <= n; i ++)
        printf("B %d %d\n", i, i - 1);
    for(int i = 0; i < seq.size() - 1; i ++)
        for(int j = seq[i] + 1; j < seq[i + 1]; j ++)
            printf("B %d %d\n", j, j - 1);
}

int main()
{
    init();
    read();
    solve();

    return 0;
}
