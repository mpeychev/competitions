#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 10000 + 10;
const int MAXK = 22;
const LL INF = 1LL << 60;

struct el {
    int curNode;
    LL curTime;
    int leftK;
    
    el() {}
    el(int _curNode, LL _curTime, int _leftK): curNode(_curNode), curTime(_curTime), leftK(_leftK) {}
};

struct cmp {
    bool operator()(el a, el b) {
        return !(a.curTime < b.curTime);
    }
};

int n, m, k;
vector< PII > g[MAXN];
priority_queue< el , vector< el > , cmp > pq;
LL d[MAXN][MAXK];
bool used[MAXN][MAXK];

void read() {
    int a, b, c;
    
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0; i < m; i ++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].pb(mp(b, c));
        g[b].pb(mp(a, c));
    }
}

void solve() {
    for(int i = 0; i <= n; i ++)
        for(int j = 0; j <= k; j ++)
            d[i][j] = INF;
    
    pq.push(el(1, 0, k));
    while(!pq.empty()) {
        el tmp = pq.top();
        pq.pop();
        
        if(used[tmp.curNode][tmp.leftK]) continue;
        
        used[tmp.curNode][tmp.leftK] = true;
        d[tmp.curNode][tmp.leftK] = tmp.curTime;
        
        if(tmp.curNode == n) {
            cout << tmp.curTime << endl;
            return;
        }
        
        for(int i = 0; i < g[tmp.curNode].size(); i ++) {
            int nxtNode = g[tmp.curNode][i].first;
            LL nxtTime = tmp.curTime + (LL)g[tmp.curNode][i].second;
            if(!used[nxtNode][tmp.leftK] && d[nxtNode][tmp.leftK] > nxtTime) {
                d[nxtNode][tmp.leftK] = nxtTime;
                pq.push(el(nxtNode, nxtTime, tmp.leftK));
            }
            if(tmp.leftK) {
                nxtTime = tmp.curTime;
                if(!used[nxtNode][tmp.leftK - 1] && d[nxtNode][tmp.leftK - 1] > nxtTime) {
                    d[nxtNode][tmp.leftK - 1] = nxtTime;
                    pq.push(el(nxtNode, nxtTime, tmp.leftK - 1));
                }
            }
        }
    }
}

int main()
{
    read();
    solve();
    
    return 0;
}
