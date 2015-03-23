#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int d[100100];
int w[100100];
int t[1 << 17];
int mxLen = 0;
int lvs;

void read() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &d[i]);
}

void update2(int le, int ri) {
    for(int i = le; i <= ri; i ++)
        t[i] = 1;
}

int query2(int le, int ri) {
    int ret = 0;
    for(int i = le; i <= ri; i ++)
        ret += (t[i] == 0);
    return ret;
}

void solve() {
    for(int i = 1; i <= n; i ++)
        if(d[i] < 0)
            w[i] = w[i - 1] + 1;

    for(int i = n; i >= 1; i --)
        if(d[i] < 0) {
            w[i] = max(w[i], w[i + 1]);
            mxLen = max(mxLen, w[i]);
        }

    for(int i = 1; i <= n; i ++)
        if(w[i] && !w[i - 1] && i != 1)
            update2(max(0, i - 1 - 2 * w[i]), i - 2);

    int ans = n - query2(0, n - 1);

    int add = 0;
    for(int i = 1; i <= n; i ++)
        if(w[i] && !w[i - 1] && i != 1 && w[i] == mxLen && i - 2 * w[i] > 1)
            add = max(add, query2(max(0, i - 1 - 3 * w[i]), i - 2 * w[i] - 2));

    printf("%d\n", ans + add);
}

int main()
{
    read();
    solve();

    return 0;
}
