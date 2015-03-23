#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>

#define pb push_back

using namespace std;

const int MAXC = 512;

int n, x, y;
vector< int > g[MAXC];
set< int > stX, stY;
bool used[MAXC];
int pr[MAXC];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d %d", &x, &y);
        g[y].pb(x);
        stX.insert(x);
        stY.insert(y);
    }
}

bool dfs(int cur) {
    used[cur] = true;
    for(int i = 0; i < g[cur].size(); i ++) {
        int nxt = g[cur][i];
        if(pr[nxt] == -1 || (!used[ pr[nxt] ] && dfs(pr[nxt]))) {
            pr[nxt] = cur;
            return true;
        }
    }
    return false;
}

void solve() {
    if(stX.size() != stY.size()) {
        cout << "Mirko\n";
        return;
    }

    memset(pr, -1, sizeof(pr));

    int l = 0;
    for(set<int> :: iterator it = stY.begin(); it != stY.end(); it ++) {
        memset(used, 0, sizeof(used));
        l += dfs(*it);
    }

    if(l == stY.size()) cout << "Slavko\n";
    else cout << "Mirko\n";
}

int main()
{
    read();
    solve();

    return 0;
}
