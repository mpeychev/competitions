#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>

#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 40100;
const int MAXM = 100100;
const LL MOD = 1000000007;

struct edge {
    int a, b;
    LL c;
};

int n, m;
edge g[MAXM];
int rt[MAXN];
LL mst, ans;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++)
        scanf("%d %d %lld", &g[i].a, &g[i].b, &g[i].c);
}

bool cmp(edge x, edge y) {
    return x.c < y.c;
}

inline int findRoot(int ver) {
    int ret = ver, up;
    while(rt[ret] != ret)
        ret = rt[ret];
    while(ver != ret) {
        up = rt[ver];
        rt[ver] = ret;
        ver = up;
    }
    return ret;
}

void findMst() {
    sort(g, g + m, cmp);

    for(int i = 1; i <= n; i ++)
        rt[i] = i;

    for(int i = 0; i < m; i ++) {
        int r1 = findRoot(g[i].a);
        int r2 = findRoot(g[i].b);
        if(r1 != r2) {
            mst += g[i].c;
            rt[r1] = r2;
        }
    }

    cout << mst << " ";
}

void mergeRoots(set< PII >& st) {
    int r1, r2;
    for(set< PII > :: iterator it = st.begin(); it != st.end(); it ++) {
        r1 = findRoot(it->first);
        r2 = findRoot(it->second);
        if(r1 != r2) rt[r1] = r2;
    }
}

void findCnt() {
    ans = 1;

    for(int i = 1; i <= n; i ++)
        rt[i] = i;

    int idx = 0;
    int r1, r2;

    while(idx < m) {
        set< PII > stPairs;
        set< int > stRoots;

        LL tmpC = g[idx].c;
        int cnt = 0;
        while(idx < m && g[idx].c == tmpC) {
            r1 = findRoot(g[idx].a);
            r2 = findRoot(g[idx].b);
            if(r1 != r2) {
                if(r1 > r2) r1 ^= r2 ^= r1 ^= r2;
                stPairs.insert(mp(r1, r2));
                stRoots.insert(r1);
                stRoots.insert(r2);
                cnt ++;
            }
            idx ++;
        }

        if(cnt <= 1) {
            mergeRoots(stPairs);
            continue;
        }

        if(cnt == 2 && stPairs.size() == 1) ans = (ans * 2LL) % MOD;

        if(cnt == 3) {
            if(stPairs.size() == 1) ans = (ans * 3LL) % MOD;
            else if(stPairs.size() == 2) ans = (ans * 2LL) % MOD;
            else if(stPairs.size() == 3 && stRoots.size() == 3) ans = (ans * 3LL) % MOD;
        }

        mergeRoots(stPairs);
    }

    cout << ans << "\n";
}

int main()
{
    read();
    findMst();
    findCnt();

    return 0;
}
