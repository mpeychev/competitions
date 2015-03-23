#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 10100;
const LL MOD = (LL)1e9;

int n, m;
map< PII , int> br;
set<int> g[MAXN];
set<int> back[MAXN];
vector<int> vec;
bool cycle;
short int col[MAXN];
LL dp[MAXN];
bool fl[MAXN];
bool used[MAXN];

void read() {
    int a, b;

    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &a, &b);
        br[ mp(a, b) ] ++;
        g[a].insert(b);
        back[b].insert(a);
    }
}

void dfsBack(int cur) {
    used[cur] = true;
    for(set<int> :: iterator it = back[cur].begin(); it != back[cur].end(); it ++)
        if(!used[ *it ])
            dfsBack(*it);
}

void dfs(int cur) {
    col[cur] = 1;
    if(cur != 2) {
        for(set<int> :: iterator it = g[cur].begin(); it != g[cur].end(); it ++) {
            int nxt = *it;
            if(!used[nxt]) continue;
            if(!col[nxt]) dfs(nxt);
            else if(col[nxt] == 1) cycle = true;
        }
    }
    col[cur] = 2;
    vec.pb(cur);
}

void print(int x) {
    vector<int> ans;
    while(x) {
        ans.pb(x % 10);
        x /= 10;
    }

    while(ans.size() < 9) ans.pb(0);

    reverse(ans.begin(), ans.end());

    for(int i = 0; i < ans.size(); i ++)
        printf("%d", ans[i]);
    printf("\n");
}

void solve() {
    dfsBack(2);

    if(!used[1]) {
        printf("0\n");
        return;
    }

    dfs(1);

    if(cycle) {
        printf("inf\n");
        return;
    }

    reverse(vec.begin(), vec.end());

    for(int i = 0; i < vec.size(); i ++) {
        if(vec[i] == 1) {
            dp[1] = 1;
            continue;
        }

        for(set<int> :: iterator it = back[ vec[i] ].begin(); it != back[ vec[i] ].end(); it ++) {
            int prv = *it;
            LL coef = br[ mp(prv, vec[i]) ];
            if(coef != 0) {
                if(fl[prv]) fl[ vec[i] ] = true;
                dp[ vec[i] ] = dp[ vec[i] ] + coef * dp[prv];
                if(dp[ vec[i] ] >= MOD) {
                    fl[ vec[i] ] = true;
                    dp[ vec[i] ] %= MOD;
                }
            }
        }

        if(vec[i] == 2) break;
    }

    if(!fl[2]) {
        cout << dp[2] << endl;
        return;
    }

    print(dp[2]);
}

int main()
{
    read();
    solve();

    return 0;
}
