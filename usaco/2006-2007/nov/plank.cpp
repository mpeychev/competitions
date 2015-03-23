/*
  Source: usaco - 2006/2007 - nov
  Task: plank
  KeyW: huffman code
*/
#include <cstdio>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int n, a;
priority_queue<long long> pq;

void init()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a);
        pq.push(-a);
    }
}

void solve()
{
    long long ans = 0;
    while(pq.size() >= 2)
    {
        long long x = -pq.top(); pq.pop();
        long long y = -pq.top(); pq.pop();

        ans += x + y;
        pq.push(-x-y);
    }
    cout << ans << endl;
}

int main()
{
    init();
    solve();

    return 0;
}
