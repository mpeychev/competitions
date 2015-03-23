/*
  Source: usaco - 2004/2005 - qual
  Task: lkcount
  KeyW: counting connected components
*/
#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int n, m;
char s[128][128];
int ans;

void read()
{
    scanf("%d %d\n",&n,&m);
    for(int i = 0; i < n; i ++)
        scanf("%s",&s[i]);
}

bool check(int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= m) return false;
    return true;
}

void bfs(int x, int y)
{
    queue <int> qx;
    queue <int> qy;

    qx.push(x);
    qy.push(y);
    s[x][y] = '.';

    while(!qx.empty())
    {
        x = qx.front();
        y = qy.front();
        qx.pop(); qy.pop();

        for(int i = 0; i < 8; i ++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if(check(tx, ty) && s[tx][ty] == 'W')
            {
                s[tx][ty] = '.';
                qx.push(tx);
                qy.push(ty);
            }
        }
    }
}

void solve()
{
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            if(s[i][j] == 'W')
            {
                bfs(i, j);
                ans ++;
            }
    printf("%d\n",ans);
}

int main()
{
    read();
    solve();

    return 0;
}
