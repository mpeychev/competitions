/*
  Source: usaco - 2006/2006 - oct
  Task: cowski
  KeyW: dijkstra
*/
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <queue>

using namespace std;

typedef struct
{
    double t;
    int x, y;
    int z;
} Vertex;

Vertex make(double _t, int _x, int _y, int _z)
{
    Vertex ret;
    ret.t = _t;
    ret.x = _x;
    ret.y = _y;
    ret.z = _z;
    return ret;
}

const int MAXN = (1 << 7);
const double eps = 1e-6;

const short int dx[] = {0, 0, 1, -1};
const short int dy[] = {1, -1, 0, 0};

struct cmp
{
    bool operator()(Vertex a, Vertex b)
    {
        return !(a.t - b.t < -eps);
    }
};

double v;
int r, c;
short int e[MAXN][MAXN];
bool used[MAXN][MAXN][MAXN];
priority_queue< Vertex , vector< Vertex > , cmp > pq;

void read()
{
    scanf("%lf %d %d",&v,&r,&c);
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            scanf("%d",&e[i][j]);
}

bool inside(int a, int b)
{
    if(a < 0 || a >= r || b < 0 || b >= c) return false;
    return true;
}

double dijkstra()
{
    pq.push(make(0.0, 0, 0, 0));
    while(!pq.empty())
    {
        Vertex tmp = pq.top();
        pq.pop();

        if(used[tmp.x][tmp.y][tmp.z + 50]) continue;
        used[tmp.x][tmp.y][tmp.z + 50] = 1;
        if(tmp.x == r - 1 && tmp.y == c - 1) return tmp.t;

        for(int i = 0; i < 4; i ++)
            if(inside(tmp.x + dx[i], tmp.y + dy[i]))
            {
                Vertex toAdd = make(tmp.t + 1 / (v * pow(2.0, tmp.z)), tmp.x + dx[i], tmp.y + dy[i],
                                    tmp.z + e[tmp.x][tmp.y] - e[ tmp.x + dx[i] ][ tmp.y + dy[i] ]);
                if(!used[toAdd.x][toAdd.y][toAdd.z + 50]) pq.push(toAdd);
            }
    }
}

int main()
{
    read();
    printf("%.2lf\n",dijkstra());

    return 0;
}
