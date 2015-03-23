#include <iostream>
#include <stdio.h>
#include <deque>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 1 << 20;

struct line {
    LL k, m;
    long double sx;

    line() {}
    line(LL _k, LL _m, long double _sx): k(_k), m(_m), sx(_sx) {}
};

int n;
LL a, b, c, ps[MAXN], dp[MAXN];
deque< line > vec;

void read() {
    int x;

    scanf("%d", &n);
    cin >> a >> b >> c;
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &x);
        ps[i] = ps[i - 1] + x;
    }
}

inline LL calc(line l, LL x) {
    return l.k * x + l.m;
}

void solve() {
    int sz;

    vec.pb(line(0, 0, 0.0));
    for(int i = 1; i <= n; i ++) {
        while(vec.size() > 1) {
            if(calc(vec[0], ps[i]) > calc(vec[1], ps[i])) break;
            vec.pop_front();
        }

        dp[i] = calc(vec[0], ps[i]) + a * ps[i] * ps[i] + b * ps[i] + c;

        line tmp = line(-2 * a * ps[i], a * ps[i] * ps[i] - b * ps[i] + dp[i], -1.0);
        sz = vec.size();
        while(sz) {
            long double X = (long double)(vec[sz - 1].m - tmp.m) / (long double)(tmp.k - vec[sz - 1].k);
            if(X > vec[sz - 1].sx) {
                tmp.sx = X;
                break;
            }
            sz --;
            vec.pop_back();
        }

        if(!sz) tmp.sx = 0.0;
        vec.pb(tmp);
    }

    cout << dp[n] << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
