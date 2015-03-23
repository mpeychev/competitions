#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1 << 9;

int n, m;
char ma3x[MAXN][MAXN];
int s[MAXN][MAXN];

void read() {
    scanf("%d %d\n", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%s", &ma3x[i]);
}

void solve() {
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            s[i][j] = s[i][j - 1] + (ma3x[i][j - 1] == 'X');

    int ans = 1;
    for(int le = 1; le <= m; le ++)
        for(int ri = le; ri <= m; ri ++) {
            int cnt = 0;
            for(int i = 1; i <= n; i ++)
                if(s[i][ri] - s[i][le - 1] == 0) {
                    cnt ++;
                    ans = max(ans, 2 * (cnt + ri - le + 1));
                }
                else cnt = 0;
        }

    printf("%d\n", ans - 1);
}

int main()
{
    read();
    solve();

    return 0;
}
