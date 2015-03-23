#include <iostream>
#include <stdio.h>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 7;
const LL INF = 1LL << 60;

int n, m;
int x[MAXN], y[MAXN], sm[MAXN], pm[MAXN], sv[MAXN], pv[MAXN];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++)
        scanf("%d %d %d %d %d %d", &x[i], &y[i], &sm[i], &pm[i], &sv[i], &pv[i]);
}

LL buy(int t, LL a) {
    if(a <= 0) return 0;
    
    LL ret = INF;
    for(int i = 0; i * pm[t] <= m; i ++) {
        LL tmp = i * pm[t];
        int b = a - i * sm[t];
        if(b > 0) {
            LL br = b / sv[t] + (b % sv[t] != 0);
            tmp += br * pv[t];
        }
        ret = min(ret, tmp);
    }
    return ret;
}

bool check(LL k) {
    LL cost = 0;
    for(int i = 0; i < n; i ++) {
        cost += buy(i, k * (LL)x[i] - y[i]);
        if(cost > m) return false;
    }
    return true;
}

void solve() {
    int le = 1, ri = 1 << 20, mid;
    int ans = 0;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(check(mid)) {
            ans = mid;
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    cout << ans << endl;
}

int main()
{
    read();
    solve();
    
    return 0;
}
