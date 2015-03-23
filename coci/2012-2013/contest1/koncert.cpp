#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 100100;

int m, a;
int x[MAXN];
int n, b;
int y[MAXN];

void read() {
    scanf("%d %d", &m, &a);
    for(int i = 0; i < a; i ++)
        scanf("%d", &x[i]);

    scanf("%d %d", &n, &b);
    for(int i = 0; i < b; i ++)
        scanf("%d", &y[i]);
}

void solve() {
    for(int i = 0; i < a; i ++)
        if(x[i] != i + 1)
            printf("GIVE GUY %d GUY %d\n", x[i], i + 1);

    int idx = a + 1;
    for(int i = 0; i < b && idx <= m; i ++) {
        printf("GIVE GIRL %d GUY %d\n", y[i], idx);
        idx ++;
    }

    if(idx > m) {
        for(int i = 1; i <= m; i ++)
            printf("ENTER GUY %d\n", i);
        return;
    }

    int le = 1, ri = idx - 1;
    int br = a + b;
    int in = 0, out = m;
    for( ; ; ) {
        for(int i = le; i <= ri; i ++) {
            printf("ENTER GUY %d\n", i);
            in ++;
            out --;
        }

        if(!out) break;

        for(int i = le; i < ri; i ++)
            printf("GIVE GUY %d GUY %d\n", i, ri);

        printf("EXIT GUY %d\n", ri);
        in --; out ++;

        for(int i = ri + 1; i <= ri + br - 1 && i <= m; i ++)
            printf("GIVE GUY %d GUY %d\n", ri, i);
        le = ri;
        ri = min(le + br - 1, m);
    }
}

int main()
{
    read();
    solve();

    return 0;
}
