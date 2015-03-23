#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

#define cost first
#define score second
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAX_SZ = 100100;

struct cmp {
    bool operator()(PII a, PII b) {
        return !(a.score > b.score);
    }
};

struct cmpSet {
    bool operator()(PII a, PII b) {
        return (a.score >= b.score);
    }
};

int n, m;
PII c[MAX_SZ], g[MAX_SZ];
priority_queue< PII , vector< PII > , cmp > grass;
multiset< PII, cmpSet > active;
multiset< PII, cmpSet > :: iterator it;
long long ans;
int tmpCost, idx;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &c[i].cost, &c[i].score);
    for(int i = 0; i < m; i ++)
        scanf("%d %d", &g[i].cost, &g[i].score);
}

void calc(int mxCost) {
    if(!mxCost) return;

    while(idx < n && c[idx].cost <= mxCost) {
        active.insert(c[idx]);
        idx ++;
    }

    while(!grass.empty()) {
        PII gr = grass.top();
        grass.pop();
        it = active.upper_bound(gr);
        if(it != active.end()) {
            ans += mxCost;
            active.erase(it);
        }
        else break;
    }

    while(!grass.empty())
        grass.pop();
}

void solve() {
    sort(c, c + n);
    sort(g, g + m);

    for(int i = 0; i < m; i ++)
        if(tmpCost != g[i].cost) {
            calc(tmpCost);
            tmpCost = g[i].cost;
            grass.push(g[i]);
        }
        else grass.push(g[i]);

    calc(tmpCost);

    if(active.empty()) cout << ans << endl;
    else cout << "-1\n";
}

int main() {
    read();
    solve();

    return 0;
}
