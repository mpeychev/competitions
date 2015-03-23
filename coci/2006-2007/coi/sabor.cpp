#include <stdio.h>
#include <iostream>
#include <queue>
#include <string.h>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int MAXN = 1 << 11;
const int ADD = 1001;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int b, s;
LL even, odd;
bool closed[MAXN][MAXN];
queue< PII > q;
int level[MAXN][MAXN];
PII tmp;

void read() {
    scanf("%d %d", &b, &s);
    int x, y;
    for(int i = 0; i < b; i ++) {
        scanf("%d %d", &x, &y);
        closed[y + ADD][x + ADD] = true;
    }
}

bool check(int x, int y) {
    if(x < 0 || x > 2 * ADD || y < 0 || y > 2 * ADD) return false;
    if(closed[x][y]) return false;
    return true;
}

void bfs() {
    memset(level, -1, sizeof(level));

    q.push(mp(ADD, ADD));
    level[ADD][ADD] = 0;
    while(!q.empty()) {
        PII tmp = q.front();
        q.pop();

        if(level[tmp.first][tmp.second] == s) continue;

        for(int i = 0; i < 4; i ++) {
            PII nxt = mp(tmp.first + dx[i], tmp.second + dy[i]);
            if(check(nxt.first, nxt.second) && level[nxt.first][nxt.second] == -1) {
                level[nxt.first][nxt.second] = level[tmp.first][tmp.second] + 1;
                q.push(nxt);
            }
        }
    }
}

// kolko sa chetnite chisla v intervala [x, s]
//         nechetnite
PII calc(int low, int high) {
    PII ret = mp(0, 0);
    int le, ri;

    // chetni:
    le = low;
    ri = high;
    if(le & 1) le ++;
    if(ri & 1) ri --;
    if(le <= ri) ret.first = (ri - le) / 2 + 1;

    // nechetni:
    le = low;
    ri = high;
    if(!(le & 1)) le ++;
    if(!(ri & 1)) ri --;
    if(le <= ri) ret.second = (ri - le) / 2 + 1;

    return ret;
}

void calc2(int x) {
    for(int i = 2; i + x < s; i ++) {
        tmp = calc(x + i + 1, min(s, x + 2 * i - 1));
        even += 2 * tmp.first;
        odd += 2 * tmp.second;
    }

    if(x + 2 > s) return;

    int add = (s - x) >> 1;
    if(x & 1) odd += add;
    else even += add;
}

void solve() {
    for(int i = 0; i <= 2 * ADD; i ++)
        for(int j = 0; j <= 2 * ADD; j ++)
            if(level[i][j] != -1) {
                if(level[i][j] & 1) odd ++;
                else even ++;
            }

    for(int i = 0; i <= 2 * ADD; i ++) {
        if(level[0][i] != -1) {
            tmp = calc(level[0][i] + 1, s);
            even += tmp.first;
            odd += tmp.second;
        }
        if(level[2 * ADD][i] != -1) {
            tmp = calc(level[2 * ADD][i] + 1, s);
            even += tmp.first;
            odd += tmp.second;
        }
        if(level[i][0] != -1) {
            tmp = calc(level[i][0] + 1, s);
            even += tmp.first;
            odd += tmp.second;
        }
        if(level[i][2 * ADD] != -1) {
            tmp = calc(level[i][2 * ADD] + 1, s);
            even += tmp.first;
            odd += tmp.second;
        }
    }

    if(level[0][0] != -1) calc2(level[0][0]);
    if(level[0][2 * ADD] != -1) calc2(level[0][2 * ADD]);
    if(level[2 * ADD][0] != -1) calc2(level[2 * ADD][0]);
    if(level[2 * ADD][2 * ADD] != -1) calc2(level[2 * ADD][2 * ADD]);
}

void write() {
    cout << even << " " << odd << endl;
}

int main()
{
    read();
    bfs();
    solve();
    write();

    return 0;
}
