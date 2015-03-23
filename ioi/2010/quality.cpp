#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 3005;

int r, c, h, w;
int ma3x[MAXN][MAXN];
int sum[MAXN][MAXN];

void read() {
    scanf("%d %d %d %d", &r, &c, &h, &w);
    for(int i = 1; i <= r; i ++)
        for(int j = 1; j <= c; j ++)
            scanf("%d", &ma3x[i][j]);
}

inline int getSum(int x1, int y1, int x2, int y2) {
    return sum[x1][y1] - sum[x1][y2 - 1] - sum[x2 - 1][y1] + sum[x2 - 1][y2 - 1];
}

int check(int x) {
    for(int i = 1; i <= r; i ++)
        for(int j = 1; j <= c; j ++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            if(ma3x[i][j] > x) sum[i][j] ++;
            if(ma3x[i][j] < x) sum[i][j] --;
        }

    int mn = 1 << 25, tmp;
    for(int i = 1; i + h - 1 <= r; i ++)
        for(int j = 1; j + w - 1 <= c; j ++) {
            tmp = getSum(i + h - 1, j + w - 1, i, j);
            if(tmp < mn) mn = tmp;
        }

    return mn;
}

void solve() {
    int le = 1, ri = r * c, mid, tmp;

    while(le <= ri) {
        mid = (le + ri) >> 1;
        tmp = check(mid);
        if(tmp == 0) {
            cout << mid << endl;
            return;
        }
        if(tmp < 0) ri = mid - 1;
        else le = mid + 1;
    }
}

int main()
{
    read();
    solve();

    return 0;
}
