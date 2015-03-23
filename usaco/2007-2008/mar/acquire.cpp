#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <deque>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PII;

const int MAXN = 1 << 16;
const LL INF = 1LL << 60;

struct line {
    LL a, b;

    line() {}
    line(LL _a, LL _b): a(_a), b(_b) {}
};

int n;
PII p[MAXN];
PII data[MAXN];
int sz;
LL dp[MAXN];
deque< line > hull;

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%lld %lld", &p[i].x, &p[i].y);
}

inline LL min(LL a, LL b) {
    if(a < b) return a;
    return b;
}

inline LL calc(LL X, line f) {
    return f.a * X + f.b;
}

bool check(line l1, line l2, line l3) {
    return ((l3.b - l1.b) * (l1.a - l2.a) <= (l2.b - l1.b) * (l1.a - l3.a));
}

void solve() {
    sort(p, p + n);

    data[sz ++] = p[0];
    for(int i = 1; i < n; i ++) {
        while(sz >= 1 && data[sz - 1].y <= p[i].y)
            sz --;
        data[sz ++] = p[i];
    }

    for(int i = sz; i >= 1; i --)
        data[i] = data[i - 1];

    dp[0] = 0;
    hull.push_back(line(data[1].y, dp[0]));
    for(int i = 1; i <= sz; i ++) {
        while(hull.size() > 1 && calc(data[i].x, hull[0]) >= calc(data[i].x, hull[1]))
            hull.pop_front();

        dp[i] = calc(data[i].x, hull[0]);

        line addLine = line(data[i + 1].y, dp[i]);
        int hullSize = hull.size();
        while(hull.size() > 1 && check(hull[hullSize - 2], hull[hullSize - 1], addLine)) {
            hull.pop_back();
            hullSize --;
        }

        hull.push_back(addLine);
    }

    printf("%lld\n", dp[sz]);
}

int main()
{
    read();
    solve();

    return 0;
}
