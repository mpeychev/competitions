#include <iostream>
#include <stdio.h>

using namespace std;

typedef long long LL;

const int MAXM = 300300;

int n, m;
int k[MAXM];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++)
        scanf("%d", &k[i]);
}

LL calc(int x) {
    LL br = 0;
    for(int i = 0; i < m; i ++)
        br = br + k[i] / x + (k[i] % x != 0);
    return br;
}

void solve() {
    int le = 1, ri = (int)1e9, mid;
    int ans = -1;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        LL cnt = calc(mid);
        if(cnt <= n) {
            ans = mid;
            ri = mid - 1;
        }
        else le = mid + 1;
    }
    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
