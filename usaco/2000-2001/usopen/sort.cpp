/*
  Source: usaco - 2000 / 2001 - usopen
  Task: sort
*/
#include <stdio.h>
#include <iostream>
#include <deque>
#include <algorithm>
#include <vector>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = (1 << 9);
const int INF = (1 << 20);

int n;
int c[MAXN];
deque<int> s;

void init()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &c[i]);
        s.push_back(c[i]);
    }
    sort(s.begin(), s.end());
}

bool cmp(PII a, PII b)
{
    if(a.first < b.first) return true;
    if(a.first > b.first) return false;
    return a.second < b.second;
}

int check()
{
    vector< PII > tmp, target;

    for(int i = 0; i < n; i ++)
        if(c[i] != s[i])
        {
            tmp.push_back(mp(c[i], i));
            target.push_back(mp(s[i], i));
        }

    sort(tmp.begin(), tmp.end(), cmp);
    sort(target.begin(), target.end(), cmp);

    int left = tmp.size();
    int ret = left * 20;
    for(int i = 0; i < left; i ++)
        ret += abs(tmp[i].second - target[i].second);

    return ret;
}

void solve()
{
    int ans = INF;
    for(int i = 0; i < n; i ++)
    {
        int cost = check();
        if(cost < ans) ans = cost;

        int fs = s[0];
        s.pop_front();
        s.push_back(fs);
    }

    printf("%d\n", ans);
}

int main()
{
    init();
    solve();

    return 0;
}
