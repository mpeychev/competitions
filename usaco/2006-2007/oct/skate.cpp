/*
  Source: usaco - 2006/2007 - oct
  Task: skate
*/
#include <stdio.h>
#include <iostream>
#include <queue>

#define x first
#define y second
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int r, c;
char s[128][128];
PII prev[128][128];
queue< PII > q;

bool valid(int x, int y)
{
    if(x < 0 || x >= r || y < 0 || y >= c) return false;
    return true;
}

void read()
{
    scanf("%d %d\n",&r,&c);
    for(int i = 0; i < r; i ++)
        scanf("%s",&s[i]);
}

void bfs()
{
    q.push(mp(0, 0));
    s[0][0] = '$';
    while(!q.empty())
    {
        PII cur = q.front();
        q.pop();

        if(cur.x == r - 1 && cur.y == c - 1) break;

        for(int i = 0; i < 4; i ++)
            if(valid(cur.x + dx[i], cur.y + dy[i]) && s[ cur.x + dx[i] ][ cur.y + dy[i] ] == '.')
            {
                s[ cur.x + dx[i] ][ cur.y + dy[i] ] = '$';
                prev[ cur.x + dx[i] ][ cur.y + dy[i] ] = cur;
                q.push(mp(cur.x + dx[i], cur.y + dy[i]));
            }
    }
}

void write(int x, int y)
{
    if(x == 0 && y == 0)
    {
        printf("1 1\n");
        return;
    }
    write(prev[x][y].x, prev[x][y].y);
    printf("%d %d\n",x + 1, y + 1);
}

int main()
{
    read();
    bfs();
    write(r - 1, c - 1);

    return 0;
}
