#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

int n, m;
int ma3x[64][64];
int sum[64][64];
LL dp[53][53][53][53];

void read() {
  scanf("%d %d", &n, &m);
  for(int i = 1; i <= n; i ++)
    for(int j = 1; j <= m; j ++)
      scanf("%d", &ma3x[i][j]);
}

inline int get(int x1, int y1, int x2, int y2) {
  return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
}

inline LL min(LL a, LL b) {
  if(a < b) return a;
  return b;
}

LL f(int x1, int y1, int x2, int y2) {
    if(x1 > x2) return 0;
    if(y1 > y2) return 0;

  if(dp[x1][y1][x2][y2] != -1)
    return dp[x1][y1][x2][y2];

  if(x1 == x2 && y1 == y2)
    return dp[x1][y1][x2][y2] = 0;

  LL ret = 1LL << 62;
  for(int i = x1; i < x2; i ++)
    ret = min(ret, f(x1, y1, i, y2) + f(i + 1, y1, x2, y2));
  for(int i = y1; i < y2; i ++)
    ret = min(ret, f(x1, y1, x2, i) + f(x1, i + 1, x2, y2));

  return dp[x1][y1][x2][y2] = ret + get(x1, y1, x2, y2);
}

void solve() {
  for(int i = 1; i <= n; i ++)
    for(int j = 1; j <= m; j ++)
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + ma3x[i][j];

  memset(dp, -1, sizeof(dp));
  cout << f(1, 1, n, m) << endl;
}

int main()
{
  read();
  solve();

  return 0;
}
