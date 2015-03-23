#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXH = 1 << 10;
const int MAXC = 1 << 10;
const int INF = 1 << 30;

int c, h, b, mx;
int tmax[MAXH];
int dp[MAXC][MAXC][2];
vector< PII > vec;
int sz;

void read() {
    int x, t;

    scanf("%d %d %d", &c, &h, &b);
    memset(tmax, -1, sizeof(tmax));
    for(int i = 0; i < c; i ++) {
        scanf("%d %d", &x, &t);
        mx = max(mx, t);
        tmax[x] = max(tmax[x], t);
    }
    tmax[b] = mx;
}

int calc(int le, int ri, bool fl) {
    if(dp[le][ri][fl] != -1)
        return dp[le][ri][fl];

    if(le == 0 && ri == sz - 1) {
        if(!fl) return dp[le][ri][fl] = 0;
        return dp[le][ri][fl] = vec[sz - 1].first;
    }

    int ret = INF;
    int dist;

    if(!fl) {
        if(le > 0) {
            dist = vec[le].first - vec[le - 1].first;
            ret = min(ret, max(calc(le - 1, ri, false), vec[le - 1].second) + dist);
            ret = min(ret, max(calc(le - 1, ri, true) + vec[ri].first - vec[le - 1].first, vec[le - 1].second) + dist);
        }
        if(ri < sz - 1) {
            dist = vec[ri + 1].first - vec[le].first;
            ret = min(ret, max(calc(le, ri + 1, true), vec[ri + 1].second) + dist);
            ret = min(ret, max(calc(le, ri + 1, false) + vec[ri + 1].first - vec[le].first, vec[ri + 1].second) + dist);
        }
    }
    else {
        if(le > 0) {
            dist = vec[ri].first - vec[le - 1].first;
            ret = min(ret, max(calc(le - 1, ri, false), vec[le - 1].second) + dist);
            ret = min(ret, max(calc(le - 1, ri, true) + vec[ri].first - vec[le - 1].first, vec[le - 1].second) + dist);
        }
        if(ri < sz - 1) {
            dist = vec[ri + 1].first - vec[ri].first;
            ret = min(ret, max(calc(le, ri + 1, true), vec[ri + 1].second) + dist);
            ret = min(ret, max(calc(le, ri + 1, false) + vec[ri + 1].first - vec[le].first, vec[ri + 1].second) + dist);
        }
    }

    dp[le][ri][fl] = ret;
    return dp[le][ri][fl];
}

void solve() {
    tmax[0] = max(tmax[0], 0);
    for(int i = 0; i <= h; i ++)
        if(tmax[i] != -1)
            vec.pb(mp(i, tmax[i]));

    sz = vec.size();

    int idx;

    for(int i = 0; i < sz; i ++)
        if(vec[i].first == b) idx = i;

    if(sz == 1) {
        cout << tmax[0] << endl;
        return;
    }

    memset(dp, -1, sizeof(dp));

    cout << max(calc(idx, idx, false), tmax[b]) << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
