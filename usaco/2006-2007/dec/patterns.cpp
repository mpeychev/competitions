#include <iostream>
#include <stdio.h>
#include <algorithm>

#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

const LL prime1 = 1365029;
const LL prime2 = 1365071;

const LL MOD1 = 2310972457;
const LL MOD2 = 2310972481;

const int MAXN = 20100;

int n, k;
int a[MAXN];
PLL h[MAXN], pw[MAXN], vec[MAXN];
int sz;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i ++)
        scanf("%d", &a[i]);
}

void init() {
    pw[0] = mp(1, 1);
    h[0] = mp(a[0], a[0]);

    for(int i = 1; i < n; i ++) {
        pw[i].first = (pw[i - 1].first * prime1) % MOD1;
        pw[i].second = (pw[i - 1].second * prime2) % MOD2;

        h[i].first = (h[i - 1].first * prime1 + a[i]) % MOD1;
        h[i].second = (h[i - 1].second * prime2 + a[i]) % MOD2;
    }
}

inline PLL getHash(int le, int ri) {
    if(!le) return h[ri];
    PLL ret;
    ret.first = (h[ri].first + MOD1 - (h[le - 1].first * pw[ri - le + 1].first) % MOD1) % MOD1;
    ret.second = (h[ri].second + MOD2 - (h[le - 1].second * pw[ri - le + 1].second) % MOD2) % MOD2;
    return ret;
}

bool check(int len) {
    sz = 0;
    for(int i = 0; i + len - 1 < n; i ++)
        vec[sz ++] = getHash(i, i + len - 1);

    sort(vec, vec + sz);

    int tmp = 1;
    for(int i = 1; i < sz; i ++)
        if(vec[i] != vec[i - 1]) tmp = 1;
        else {
            tmp ++;
            if(tmp >= k) return true;
        }
    return false;
}

void solve() {
    int ans = 0, le = 1, ri = n, mid;
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
    init();
    solve();

    return 0;
}
