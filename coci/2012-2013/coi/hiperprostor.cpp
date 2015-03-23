/*
d1 + b1 * x
d2 + b2 * x
...
dk + bk * x

=> Upper Envelope idea !!!
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 1 << 30;
const int MAXP = 1 << 9;

typedef long long LL;
typedef pair<int, int> PII;

struct el {
    int node, dist, x;

    el() {}
    el(int _node, int _dist, int _x): node(_node), dist(_dist), x(_x) {}
};

struct cmpEl {
    bool operator()(el a, el b) {
        if(a.dist == b.dist) return !(a.x < b.x);
        return !(a.dist < b.dist);
    }
};

int p, r;
vector< PII > g[MAXP];
priority_queue< el , vector< el > , cmpEl > pq;
int d[MAXP][MAXP], bit[MAXP][MAXP];
bool used[MAXP][MAXP];
bool fl;

void read() {
    int c, d, t;
    char s[16];

    scanf("%d %d", &p, &r);
    for(int i = 0; i < r; i ++) {
        scanf("%d %d %s", &c, &d, &s);
        if(s[0] == 'x') t = -1;
        else {
            int len = strlen(s);
            t = 0;
            for(int j = 0; j < len; j ++)
                t = t * 10 + (s[j] - '0');
        }
        g[c].pb(mp(d, t));
    }
}

void init() {
    memset(used, 0, sizeof(used));
    for(int i = 0; i <= p; i ++)
        for(int j = 0; j <= p; j ++) {
            d[i][j] = INF;
            bit[i][j] = INF;
        }
}

inline int getMin(int ver, int idx) {
    int ret = bit[ver][0];
    while(idx) {
        ret = min(ret, bit[ver][idx]);
        idx -= (idx & -idx);
    }
    return ret;
}

inline void update(int ver, int idx, int val) {
    if(!idx) {
        bit[ver][idx] = min(bit[ver][idx], val);
        return;
    }

    while(idx <= p) {
        bit[ver][idx] = min(bit[ver][idx], val);
        idx += (idx & -idx);
    }
}

void add(int ver, int curDist, int xedges) {
    int mn = getMin(ver, xedges);
    if(mn <= curDist) return;
    d[ver][xedges] = curDist;
    update(ver, xedges, curDist);
    pq.push(el(ver, curDist, xedges));
}

void dijkstra(int a, int b) {
    el tmp, nxt;
    fl = false;

    add(a, 0, 0);
    while(!pq.empty()) {
        tmp = pq.top();
        pq.pop();

        if(used[tmp.node][tmp.x]) continue;

        used[tmp.node][tmp.x] = true;
        d[tmp.node][tmp.x] = tmp.dist;

        if(tmp.node == b) fl = true;

        for(int i = 0; i < g[tmp.node].size(); i ++) {
            int fst = g[tmp.node][i].first;
            int snd = g[tmp.node][i].second;

            nxt.node = fst;
            if(snd == -1) {
                nxt.dist = tmp.dist;
                nxt.x = tmp.x + 1;
            }
            else {
                nxt.dist = tmp.dist + snd;
                nxt.x = tmp.x;
            }

            if(!used[nxt.node][nxt.x])
                add(nxt.node, nxt.dist, nxt.x);
        }
    }
}

void solve(int b) {
    if(!fl) {
        printf("0 0\n");
        return;
    }

    if(d[b][0] == INF) {
        printf("inf\n");
        return;
    }

    vector< PII > vec;
    LL mn = INF;

    for(int i = 0; i <= p; i ++)
        if(d[b][i] != INF && d[b][i] < mn) {
            vec.pb(mp(d[b][i], i));
            mn = d[b][i];
        }

    if(vec.size() == 1) {
        printf("1 %d\n", vec[0].first);
        return;
    }

    vector<int> nxt;
    nxt.resize( vec.size() );

    LL maxX, nxtIdx, t;

    for(int i = 0; i < vec.size(); i ++) {
        maxX = -1, nxtIdx = -1;
        for(int j = i + 1; j < vec.size(); j ++) {
            t = (vec[i].first - vec[j].first) / (vec[j].second - vec[i].second);
            if((vec[i].first - vec[j].first) % (vec[j].second - vec[i].second) == 0) t --;
            if(maxX < t) maxX = t;
        }

        /// Pay attention in calculating nxtIdx !!

        t = INF;
        for(int j = i + 1; j < vec.size(); j ++) {
            LL cur = (LL)vec[j].first + (LL)vec[j].second * maxX;
            if(cur < t) {
                t = cur;
                nxtIdx = j;
            }
        }
        nxt[i] = nxtIdx;
    }

    /* cnt */
    nxtIdx = nxt[0];
    t = (vec[0].first - vec[nxtIdx].first) / (vec[nxtIdx].second - vec[0].second);
    if((vec[0].first - vec[nxtIdx].first) % (vec[nxtIdx].second - vec[0].second) == 0) t --;

    cout << t + 1 << " ";

    /* sum */
    int curIdx = 0;
    LL sum = 0;
    maxX = INF;
    for( ; ; ) {
        if(nxt[curIdx] == -1) {
            sum += maxX * vec[curIdx].first + vec[curIdx].second * (((1 + maxX) * maxX) / 2);
            break;
        }
        else {
            nxtIdx = nxt[curIdx];
            t = (vec[curIdx].first - vec[nxtIdx].first) / (vec[nxtIdx].second - vec[curIdx].second);
            if((vec[curIdx].first - vec[nxtIdx].first) % (vec[nxtIdx].second - vec[curIdx].second) == 0) t --;
            t ++;

            if(maxX == INF) maxX = t;
            sum = sum + (maxX - t + 1) * vec[curIdx].first + vec[curIdx].second * (((maxX + t) * (maxX - t + 1)) / 2);

            curIdx = nxtIdx;
            maxX = t - 1;
        }
    }

    cout << sum << endl;
}

void solve() {
    int q, a, b;
    scanf("%d", &q);
    for( ; q; q --) {
        scanf("%d %d", &a, &b);
        init();
        dijkstra(a, b);
        solve(b);
    }
}

int main()
{
    read();
    solve();

    return 0;
}
