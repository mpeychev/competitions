#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 100100;

int n, k, m;
int level[MAXN];
vector<int> g[MAXN];
int t[1024][1024];
bool used[1024];
queue< PII > q;

void read() {
    scanf("%d %d %d", &n, &k, &m);
    for(int i = 0; i < m; i ++)
        for(int j = 0; j < k; j ++) {
            scanf("%d", &t[i][j]);
            g[ t[i][j] ].pb(i);
        }
}

void expand(int node, int val) {
    for(int i = 0; i < g[node].size(); i ++) {
        int tubeIdx = g[node][i];
        if(!used[tubeIdx]) {
            q.push(mp(tubeIdx, val));
            used[tubeIdx] = true;
        }
    }
}

void solve() {
    level[1] = 1;
    for(int i = 0; i < g[1].size(); i ++) {
        int tubeIdx = g[1][i];
        if(!used[tubeIdx]) {
            q.push(mp(tubeIdx, 1));
            used[tubeIdx] = true;
        }
    }

    while(!q.empty()) {
        PII tmp = q.front();
        q.pop();

        for(int i = 0; i < k; i ++)
            if(!level[ t[tmp.first][i] ]) {
                level[ t[tmp.first][i] ] = tmp.second + 1;
                expand(t[tmp.first][i], tmp.second + 1);
            }
    }

    if(!level[n]) cout << -1 << endl;
    else cout << level[n] << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
