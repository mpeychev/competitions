#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 10;

const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};

int n, s;
char ma3x[MAXN][MAXN];
int bees[MAXN][MAXN], mecho[MAXN][MAXN];
queue< PII > q;
PII tmp, mpos;
int nxtX, nxtY;

bool valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

void read() {
    scanf("%d %d", &n, &s);
    for(int i = 0; i < n; i ++)
        scanf("%s", &ma3x[i]);
}

void bfsBees() {
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            if(ma3x[i][j] == 'H') {
                bees[i][j] = 0;
                q.push(mp(i, j));
            }

    while(!q.empty()) {
        tmp = q.front();
        q.pop();

        for(int k = 0; k < 4; k ++) {
            nxtX = tmp.first + dx[k];
            nxtY = tmp.second + dy[k];

            if(valid(nxtX, nxtY) && (ma3x[nxtX][nxtY] == 'G' || ma3x[nxtX][nxtY] == 'M') && bees[nxtX][nxtY] == -1) {
                bees[nxtX][nxtY] = bees[tmp.first][tmp.second] + 1;
                q.push(mp(nxtX, nxtY));
            }
        }
    }
}

bool check(int t) {
    memset(mecho, -1, sizeof(mecho));
    while(!q.empty())
        q.pop();

    if(1 + t <= bees[mpos.first][mpos.second]) {
        mecho[mpos.first][mpos.second] = 0;
        q.push(mpos);
    }

    while(!q.empty()) {
        tmp = q.front();
        q.pop();

        if(ma3x[tmp.first][tmp.second] == 'D') return true;

        for(int k = 0; k < 4; k ++) {
            nxtX = tmp.first + dx[k];
            nxtY = tmp.second + dy[k];

            if(valid(nxtX, nxtY) && (ma3x[nxtX][nxtY] == 'G' || ma3x[nxtX][nxtY] == 'D') && mecho[nxtX][nxtY] == -1 &&
               (bees[nxtX][nxtY] == -1 || (mecho[tmp.first][tmp.second] + 1) / s + 1 + t <= bees[nxtX][nxtY] )) {
                    mecho[nxtX][nxtY] = mecho[tmp.first][tmp.second] + 1;
                    q.push(mp(nxtX, nxtY));
            }
        }
    }

    return false;
}

void solve() {
    memset(bees, -1, sizeof(bees));
    bfsBees();

    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            if(ma3x[i][j] == 'M')
                mpos = mp(i, j);

    int le = 0, ri = 700000, mid;
    int ans = -1;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(check(mid)) {
            ans = mid;
            le = mid + 1;
        }
        else ri = mid - 1;
    }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
