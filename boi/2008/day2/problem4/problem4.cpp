#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 5;
const int MAXM = 1 << 7;
const LL INF = 1LL << 60;

struct state {
    int mask;
    LL dist;

    state() {}
    state(int _mask, LL _dist): mask(_mask), dist(_dist) {}
};

struct cmp {
    bool operator()(state a, state b) {
        return !(a.dist < b.dist);
    }
};

int n, m;
int t[MAXM];
char s1[MAXM][MAXN], s2[MAXM][MAXN];
bool used[1 << 20];
LL d[1 << 20];
priority_queue< state , vector< state > , cmp > pq;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++)
        scanf("%d %s %s", &t[i], &s1[i], &s2[i]);
}

void solve() {
    for(int i = 0; i < (1 << n); i ++)
        d[i] = INF;

    pq.push(state((1 << n) - 1, 0));
    while(!pq.empty()) {
        state tmp = pq.top();
        pq.pop();

        if(used[tmp.mask]) continue;

        used[tmp.mask] = true;
        d[tmp.mask] = tmp.dist;

        if(!tmp.mask) {
            cout << tmp.dist << endl;
            return;
        }

        for(int i = 0; i < m; i ++) {
            int cpy = tmp.mask;
            bool fl = true;
            for(int j = 0; j < n; j ++) {
                if(s1[i][j] == '+' && !((tmp.mask >> j) & 1)) {
                    fl = false;
                    break;
                }
                if(s1[i][j] == '-' && ((tmp.mask >> j) & 1)) {
                    fl = false;
                    break;
                }

                if(s2[i][j] == '+' && !((tmp.mask >> j) & 1)) cpy ^= (1 << j);
                if(s2[i][j] == '-' && ((tmp.mask >> j) & 1)) cpy ^= (1 << j);
            }

            if(fl && !used[cpy] && d[cpy] > tmp.dist + t[i]) {
                d[cpy] = tmp.dist + t[i];
                pq.push(state(cpy, d[cpy]));
            }
        }
    }

    cout << "-1\n";
}

int main()
{
    read();
    solve();

    return 0;
}
