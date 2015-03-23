#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

int n, t;
int x, y;
int k[32][32];
bool used[32][32], move[32][32];

void read()
{
    scanf("%d %d", &n, &t);
    scanf("%d %d", &x, &y);
    
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            scanf("%d", &k[i][j]);
}

void solve()
{
    used[x][y] = 1;
    for(int g = 1; g <= t; g ++)
    {
        memset(move, 0, sizeof(move));
        int cnt = 0;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++)
                if(used[i][j])
                {
                    cnt ++;
                    for(int t = 0; t < 8; t ++)
                    {
                        int gox = i + dx[t];
                        int goy = j + dy[t];
                        
                        if(gox >= 1 && gox <= n && goy >= 1 && goy <= n && g % k[gox][goy] == 0)
                            move[gox][goy] = 1;
                    }
                }
        memcpy(used, move, sizeof(move));
        if(!cnt) break;
    }
}

void write()
{
    int cnt = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(used[i][j])
                cnt ++;
    
    printf("%d\n", cnt);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(used[i][j])
                printf("%d %d\n", i, j);
}

int main()
{
    read();
    solve();
    write();
    
    return 0;
}
