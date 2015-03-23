#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

#define pb push_back

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int INF = 1 << 27;

struct el {
    int x, y;

    el() {}
    el(int _x, int _y): x(_x), y(_y) {}
};

int r, c;
char s[64][64];

vector<el> vec[16];
int sz;

int num[64][64];
int g[16][16];
int dist[64][64];

int dp[1 << 15][16];

void read() {
    scanf("%d %d\n", &r, &c);
    for(int i = 0; i < r; i ++)
        scanf("%s", &s[i]);
}

inline bool inside(int x, int y) {
    return (0 <= x && x < r && 0 <= y && y < c);
}

void bfs1(int x, int y) {
    queue< el > q;

    q.push(el(x, y));
    num[x][y] = sz;
    vec[sz].pb(el(x, y));

    while(!q.empty()) {
        el tmp = q.front();
        q.pop();

        for(int i = 0; i < 4; i ++) {
            int nxtX = tmp.x + dx[i];
            int nxtY = tmp.y + dy[i];

            if(inside(nxtX, nxtY) && s[nxtX][nxtY] == 'X' && num[nxtX][nxtY] == -1) {
                q.push(el(nxtX, nxtY));
                num[nxtX][nxtY] = sz;
                vec[sz].pb(el(nxtX, nxtY));
            }
        }
    }
}

void bfs2(int idx) {
    memset(dist, -1, sizeof(dist));
    queue< el > q;

    for(int i = 0; i < vec[idx].size(); i ++) {
        q.push(vec[idx][i]);
        dist[ vec[idx][i].x ][ vec[idx][i].y ] = 0;
    }

    while(!q.empty()) {
        el tmp = q.front();
        q.pop();

        for(int i = 0; i < 4; i ++) {
            int nxtX = tmp.x + dx[i];
            int nxtY = tmp.y + dy[i];

            if(inside(nxtX, nxtY) && s[nxtX][nxtY] != '.') {
                if(s[nxtX][nxtY] == 'S') {
                    if(dist[nxtX][nxtY] == -1) {
                        q.push(el(nxtX, nxtY));
                        dist[nxtX][nxtY] = dist[tmp.x][tmp.y] + 1;
                    }
                }
                else {
                    if(dist[nxtX][nxtY] == -1)
                        dist[nxtX][nxtY] = dist[tmp.x][tmp.y];
                }
            }
        }
    }

    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(s[i][j] == 'X' && dist[i][j] != -1 && g[idx][ num[i][j] ] > dist[i][j])
                g[idx][ num[i][j] ] = dist[i][j];
}

void build() {
    memset(num, -1, sizeof(num));

    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(s[i][j] == 'X' && num[i][j] == -1) {
                bfs1(i, j);
                sz ++;
            }

    for(int i = 0; i < sz; i ++)
        for(int j = 0; j < sz; j ++)
            g[i][j] = INF;

    for(int i = 0; i < sz; i ++)
        bfs2(i);
}

void floyd() {
    for(int k = 0; k < sz; k ++)
        for(int i = 0; i < sz; i ++)
            for(int j = 0; j < sz; j ++)
                if(g[i][k] + g[k][j] < g[i][j])
                    g[i][j] = g[i][k] + g[k][j];
}

int calc(int mask, int last) {
    if(dp[mask][last] != -1)
        return dp[mask][last];

    if(mask == (1 << sz) - 1)
        return dp[mask][last] = 0;

    int ret = INF;
    for(int i = 0; i < sz; i ++)
        if(!((mask >> i) & 1)) {
            int tmp = calc(mask | (1 << i), i) + g[last][i];
            if(ret > tmp) ret = tmp;
        }

    return dp[mask][last] = ret;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    int ans = INF;
    for(int i = 0; i < sz; i ++) {
        int tmp = calc(1 << i, i);
        if(ans > tmp) ans = tmp;
    }

    cout << ans << endl;
}

int main()
{
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);

    read();
    build();
    floyd();
    solve();

    return 0;
}
