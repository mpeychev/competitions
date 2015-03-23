#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 100100;

int n, a[MAXN], b;
int pos, val[MAXN];
int br[3 * MAXN];
long long ans;

void read() {
    scanf("%d %d", &n, &b);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &a[i]);
        if(a[i] == b) pos = i;
    }
}

void solve() {
    ans = 1;
    for(int i = pos - 1; i >= 0; i --) {
        if(a[i] > b) val[i] = val[i + 1] + 1;
        else val[i] = val[i + 1] - 1;

        if(val[i] == 0) ans ++;
    }

    for(int i = pos + 1; i < n; i ++) {
        if(a[i] > b) val[i] = val[i - 1] + 1;
        else val[i] = val[i - 1] - 1;

        if(val[i] == 0) ans ++;
    }

    for(int i = 0; i < pos; i ++)
        br[ val[i] + MAXN ] ++;

    for(int i = pos + 1; i < n; i ++)
        ans += br[ - val[i] + MAXN ];

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
