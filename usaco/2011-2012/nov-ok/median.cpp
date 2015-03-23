#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long LL;

const int ADD = 100001;

int n, x, h, a, b;
LL tree[1 << 18];
LL ans;

void update(int idx) {
    while(idx <= 2 * ADD + 5) {
        tree[idx] ++;
        idx += (idx & -idx);
    }
}

LL get(int idx) {
    LL ret = 0;
    while(idx) {
        ret += tree[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

int main()
{
    scanf("%d %d", &n, &x);
    update(ADD);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &h);

        if(h >= x) a ++;
        else b ++;

        ans += get(a - b + ADD);

        update(a - b + ADD);
    }

    cout << ans << endl;

    return 0;
}
