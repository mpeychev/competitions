#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXM = 100100;
const int MAXN = 200200;
const int INF = 1 << 20;

struct cmp {
    bool operator()(PII a, PII b) {
        if(a.first != b.first) return !(a.first < b.first);
        return !(a.second > b.second);
    }
};

struct cmp2 {
    bool operator()(PII a, PII b) {
        if(a.first != b.first) return !(a.first > b.first);
        return !(a.second > b.second);
    }
};

int n, m;
int a[MAXM], b[MAXM];
int ri[MAXN], le[MAXN], dp[MAXN];
priority_queue< PII , vector< PII > , cmp > pq;
priority_queue< PII , vector< PII > , cmp2 > pq2;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++)
        scanf("%d %d", &a[i], &b[i]);
}

void init() {
    PII tmp;

    for(int i = 0; i < m; i ++) {
        pq.push(mp(a[i], b[i]));
        pq2.push(mp(a[i], b[i]));
    }

    for(int i = 1; i <= n + 1; i ++) {
        ri[i] = i;
        while(!pq.empty()) {
            tmp = pq.top();
            if(tmp.second < i) pq.pop();
            else break;
        }
        if(pq.empty()) continue;
        tmp = pq.top();
        if(tmp.first <= i) ri[i] = tmp.first;
    }

    for(int i = n + 1; i >= 1; i --) {
        le[i] = 0;
        while(!pq2.empty()) {
            tmp = pq2.top();
            if(tmp.second >= i) pq2.pop();
            else break;
        }
        if(pq2.empty()) continue;
        tmp = pq2.top();
        le[i] = tmp.first;
    }
}

void solve() {
    for(int i = 1; i <= n + 1; i ++) {
        dp[i] = -INF;
        for(int j = ri[i] - 1; j >= le[i]; j --)
            if(dp[j] != -INF && dp[i] < 1 + dp[j])
                dp[i] = 1 + dp[j];
    }

    if(dp[n + 1] == -INF) printf("-1\n");
    else printf("%d\n", dp[n + 1] - 1);
}

int main()
{
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);

    read();
    init();
    solve();

    return 0;
}
