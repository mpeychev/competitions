#include <iostream>
#include <stdio.h>

using namespace std;

typedef long long LL;

const int MAXR = 100100;

int r, l;
LL b, x[MAXR], sum[MAXR];
int ans;

void read() {
    scanf("%d %d %lld", &r, &l, &b);
    for(int i = 1; i <= r; i ++) {
        scanf("%lld", &x[i]);
        sum[i] = sum[i - 1] + x[i];
    }
}

inline LL getSum(int le, int ri) {
    return sum[ri] - sum[le - 1];
}

inline LL calc(int le, int ri) {
    int mid = (le + ri) >> 1;
    LL br1 = mid - le + 1;
    LL br2 = ri - mid + 1;
    return (br1 * x[mid] - getSum(le, mid)) + (getSum(mid, ri) - br2 * x[mid]);
}

void solve() {
    int le = 1;
    ans = 1;
    for(int ri = 2; ri <= r; ri ++) {
        while(calc(le, ri) > b)
            le ++;
        ans = max(ans, ri - le + 1);
    }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
