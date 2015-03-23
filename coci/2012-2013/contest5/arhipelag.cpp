#include <iostream>
#include <stdio.h>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int r, c;
char s[16][16];
char ans[16][16];

void read() {
    scanf("%d %d\n", &r, &c);
    for(int i = 0; i < r; i ++)
        scanf("%s", &s[i]);
}

inline int check(int x, int y) {
    if(x < 0 || x >= r || y < 0 || y >= c) return 1;
    if(s[x][y] == '.') return 1;
    return 0;
}

void solve() {
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(s[i][j] == '.') ans[i][j] = '.';
            else {
                int br = 0;
                for(int k = 0; k < 4; k ++)
                    br += check(i + dx[k], j + dy[k]);
                if(br >= 3) ans[i][j] = '.';
                else ans[i][j] = 'X';
            }

    int minI = 10, maxI = -1, minJ = 10, maxJ = -1;
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(ans[i][j] == 'X') {
                minI = min(minI, i);
                maxI = max(maxI, i);

                minJ = min(minJ, j);
                maxJ = max(maxJ, j);
            }

    for(int i = minI; i <= maxI; i ++) {
        for(int j = minJ; j <= maxJ; j ++)
            printf("%c", ans[i][j]);
        printf("\n");
    }
}

int main()
{
    read();
    solve();

    return 0;
}
