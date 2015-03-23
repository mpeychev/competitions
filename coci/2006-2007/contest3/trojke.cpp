#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y): x(_x), y(_y) {}
};

int n;
char ma3x[128][128];
int x[32], y[32];
int ans;

void read() {
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++)
        scanf("%s", &ma3x[i]);
}

int det(point a, point b, point c) {
    return (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
}

void solve() {
    memset(x, -1, sizeof(x));
    memset(y, -1, sizeof(y));

    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            if(ma3x[i][j] != '.') {
                x[ ma3x[i][j] - 'A' ] = j;
                y[ ma3x[i][j] - 'A' ] = i;
            }

    for(int i = 0; i < 26; i ++)
        if(x[i] != -1)
            for(int j = i + 1; j < 26; j ++)
                if(x[j] != -1)
                    for(int k = j + 1; k < 26; k ++)
                        if(x[k] != -1 && !det(point(x[i], y[i]), point(x[j], y[j]), point(x[k], y[k])))
                            ans ++;

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
