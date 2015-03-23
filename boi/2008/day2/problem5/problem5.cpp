#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1 << 14;

int n, m, s[MAXN];
int cnt[1 << 20];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &s[i]);
        cnt[ s[i] ] ++;
        if(m < cnt[ s[i] ]) m = cnt[ s[i] ];
    }
}

void solve() {
    sort(s, s + n);

    printf("%d\n", m);
    for(int i = 0; i < m; i ++) {
        printf("%d", s[i]);
        for(int j = i + m; j < n; j += m)
            printf(" %d", s[j]);
        printf("\n");
    }
}

int main()
{
    read();
    solve();

    return 0;
}
