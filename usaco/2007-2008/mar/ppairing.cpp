#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 100100;

int n, c;
PII p[MAXN];
queue<int> q;
int idx, end;

void read() {
  scanf("%d %d", &n, &c);
  for(int i = 1; i <= c; i ++) {
    scanf("%d", &p[i].first);
    p[i].second = i;
  }
  sort(p + 1, p + c + 1);
}

void solve() {
  int sum = 0;
  for(int i = c; i >= 1; i --) {
    idx = i;
    sum += p[i].first;
    for(int j = 0; j < p[i].first; j ++)
      q.push(p[i].second);

    if(sum + p[i - 1].first > n / 2) break;
  }

  if(sum == n / 2) {
    for(int i = 1; i < idx; i ++)
      for(int j = 0; j < p[i].first; j ++) {
	printf("%d %d\n", p[i].second, q.front());
	q.pop();
      }
    return;
  }

  end = idx;

  for(int i = 1; i < idx; i ++)
    if(sum + p[i].first >= n / 2) {
      idx = i;
      break;
    }

  for(int i = 0; i < p[idx].first - n / 2 + sum; i ++) {
    printf("%d %d\n", p[idx].second, q.front());
    q.pop();
  }

  for(int i = 0; i < n / 2 - sum; i ++)
    q.push(p[idx].second);

  for(int i = 1; i < end; i ++)
    if(i != idx)
      for(int j = 0; j < p[i].first; j ++) {
	printf("%d %d\n", p[i].second, q.front());
	q.pop();
      }
}

int main()
{
  read();
  solve();

  return 0;
}
