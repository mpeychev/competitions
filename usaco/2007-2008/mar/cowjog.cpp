#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 10010;
const int MAXK = 128;
const int INF = 1 << 30;

struct cmp {
  bool operator()(PII a, PII b) {
    return !(a.second < b.second);
  }
};

int n, m, k;
int x, y, d;
vector< PII > g[MAXN];
int dist[MAXN][MAXK];
int cnt[MAXN];
priority_queue< PII , vector< PII > , cmp > pq;

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for(int i = 0; i < m; i ++) {
    scanf("%d %d %d", &x, &y, &d);
    g[x].pb(mp(y, d));
  }
}

void solve() {
  for(int i = 0; i <= n; i ++)
    for(int j = 0; j <= k; j ++)
      dist[i][j] = INF;
  
  pq.push(mp(n, 0));
  while(!pq.empty()) {
    PII tmp = pq.top();
    pq.pop();
    
    cnt[tmp.first] ++;
    dist[tmp.first][ cnt[tmp.first] ] = tmp.second;
    
    if(cnt[tmp.first] >= k) {
      if(tmp.first == n) break;
      continue;
    }
    
    for(int i = 0; i < g[tmp.first].size(); i ++) {
      int nxt = g[tmp.first][i].first;
      int len = tmp.second + g[tmp.first][i].second;
      if(cnt[nxt] < k) pq.push(mp(nxt, len));
    }
  }
}

void write() {
  for(int i = 1; i <= k; i ++)
    if(dist[1][i] != INF) printf("%d\n", dist[1][i]);
    else printf("-1\n");
}

int main()
{
  read();
  solve();
  write();
  
  return 0;
}
