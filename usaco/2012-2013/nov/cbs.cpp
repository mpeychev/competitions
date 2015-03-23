/*
ID: mompej951
TASK: cbs
LANG: C++
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 50050;

inline int max(int a, int b) {
    if(a < b) return b;
    return a;
}

int k, n;
int ans = 0;

struct Row {
    char s[MAXN];
    int cnt[MAXN];
    int tree[MAXN];
    vector<int> vec[MAXN];

    void updateRmq(int idx, int val) {  /// idx <- cnt[val]
        if(!idx) tree[idx] = val;
        else {
            while(idx <= n + 3) {
                tree[idx] = max(tree[idx], val);
                idx += (idx & -idx);
            }
        }
    }

    int query(int bound) {
        int ret = tree[0];
        while(bound > 0) {
            ret = max(ret, tree[bound]);
            bound -= (bound & -bound);
        }
        return ret;
    }

    void add(int idx) {
        char ch = s[idx - 1];
        if(ch == '(') {
            if(!cnt[idx - 1]) cnt[idx] = 2;
            else cnt[idx] = cnt[idx - 1] + 1;
            vec[ cnt[idx] ].pb(idx);
            updateRmq(cnt[idx], idx);
        }
        else {
            cnt[idx] = cnt[idx - 1] - 1;
            if(cnt[idx] < 0) cnt[idx] = 0;
            updateRmq(cnt[idx], idx);
        }
    }
};

Row r[10];

void read() {
    scanf("%d %d", &k, &n);
    for(int i = 0; i < k; i ++)
        scanf("%s", &r[i].s);
}

inline bool isPossible(int idx) {
    for(int i = 0; i < k; i ++) {
        if(r[i].s[idx - 1] == '(')
            return false;
        if(!r[i].cnt[idx])
            return false;
    }
    return true;
}

void solve() {
    for(int i = 0; i < k; i ++) {
        r[i].cnt[0] = 1;
        r[i].updateRmq(1, 0);
    }

    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j < k; j ++)
            r[j].add(i);

        if(isPossible(i)) {
            int mxLeft = -1;
            for(int j = 0; j < k; j ++)
                mxLeft = max(mxLeft, r[j].query( r[j].cnt[i] - 1 ));

            for(int j = r[0].vec[ r[0].cnt[i] + 1 ].size() - 1; j >= 0 && r[0].vec[ r[0].cnt[i] + 1 ][j] > mxLeft; j --) {
                bool fl = true;
                for(int h = 1; h < k; h ++)
                    if(!binary_search(r[h].vec[ r[h].cnt[i] + 1 ].begin(),
                                      r[h].vec[ r[h].cnt[i] + 1 ].end(),
                                      r[0].vec[ r[0].cnt[i] + 1 ][j])) {
                        fl = false;
                        break;
                    }
                ans += fl;
            }
        }
    }

    cout << ans << endl;
}

int main()
{
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);

    read();
    solve();

    return 0;
}
