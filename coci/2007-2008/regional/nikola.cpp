#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 10;
const LL INF = 1LL << 50;

struct el {
    int currentPos;
    int lastJump;
    LL cost;
    
    el() {}
    el(int _currentPos, int _lastJump, LL _cost): currentPos(_currentPos), lastJump(_lastJump), cost(_cost) {}
};

struct cmp {
    bool operator()(el a, el b) {
        return !(a.cost < b.cost);
    }
};

int n;
LL p[MAXN];
LL dist[MAXN][MAXN];
bool used[MAXN][MAXN];
priority_queue< el , vector< el > , cmp > pq;

void read() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%lld", &p[i]);
}

void solve() {
    for(int i = 0; i <= n; i ++)
        for(int j = 0; j <= n; j ++)
            dist[i][j] = INF;
    
    pq.push(el(2, 1, p[2]));
    while(!pq.empty()) {
        el tmp = pq.top();
        pq.pop();
        
        if(used[tmp.currentPos][tmp.lastJump]) continue;
        
        dist[tmp.currentPos][tmp.lastJump] = tmp.cost;
        used[tmp.currentPos][tmp.lastJump] = true;
        
        if(tmp.currentPos == n) {
            cout << tmp.cost << endl;
            return;
        }
        
        el nxt;
        
        if(tmp.currentPos + tmp.lastJump + 1 <= n) {
            nxt.currentPos = tmp.currentPos + tmp.lastJump + 1;
            nxt.lastJump = tmp.lastJump + 1;
            nxt.cost = tmp.cost + p[ nxt.currentPos ];
            if(!used[nxt.currentPos][nxt.lastJump] && dist[nxt.currentPos][nxt.lastJump] > nxt.cost) {
                dist[nxt.currentPos][nxt.lastJump] = nxt.cost;
                pq.push(nxt);
            }
        }
        
        if(tmp.currentPos - tmp.lastJump >= 1) {
            nxt.currentPos = tmp.currentPos - tmp.lastJump;
            nxt.lastJump = tmp.lastJump;
            nxt.cost = tmp.cost + p[ nxt.currentPos ];
            if(!used[nxt.currentPos][nxt.lastJump] && dist[nxt.currentPos][nxt.lastJump] > nxt.cost) {
                dist[nxt.currentPos][nxt.lastJump] = nxt.cost;
                pq.push(nxt);
            }
        }
    }
    cout << -1 << endl;
}

int main()
{
    read();
    solve();
    
    return 0;
}
