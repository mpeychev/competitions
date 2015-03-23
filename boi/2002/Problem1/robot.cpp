/*
  Source: boi - 2002 - day1
  Task: zad1
  KeyW: Namirane na maximum, chrez naprechen minimum.
        Modificirane na algoritym na Dijkstra.
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define mp make_pair
#define x first
#define y second
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXM = (1 << 5);
const int MAXN = (1 << 7);
const int INF = (1 << 20);

int m, n;
PII wall[2][MAXM], p[MAXN];
int minX[MAXM], maxX[MAXM];
int minY[MAXM], maxY[MAXM];
vector< PII > pts[MAXM];
int ans = INF;

inline int min(int a, int b)
{
    if(a < b) return a;
    return b;
}
inline int min4(int a, int b, int c, int d) { return min(min(a, b), min(c, d)); }

inline int max(int a, int b)
{
    if(a > b) return a;
    return b;
}
inline int max4(int a, int b, int c, int d) { return max(max(a, b), max(c, d)); }

inline int abs(int x)
{
    if(x < 0) return -x;
    return x;
}

void read()
{
    scanf("%d", &m);

    for(int k = 0; k < 2; k ++)
    {
        for(int i = 0; i <= m; i ++)
            scanf("%d %d", &wall[k][i].x, &wall[k][i].y);
    }

    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &p[i].x, &p[i].y);

//    for(int i = 0; i < n; i ++)
//        cout << p[i].x << " " << p[i].y << endl;
//    cout << endl;
}

void init()
{
    for(int i = 0; i < m; i ++)
    {
        minX[i] = min4(wall[0][i].x, wall[0][i + 1].x, wall[1][i].x, wall[1][i + 1].x);
        maxX[i] = max4(wall[0][i].x, wall[0][i + 1].x, wall[1][i].x, wall[1][i + 1].x);
        minY[i] = min4(wall[0][i].y, wall[0][i + 1].y, wall[1][i].y, wall[1][i + 1].y);
        maxY[i] = max4(wall[0][i].y, wall[0][i + 1].y, wall[1][i].y, wall[1][i + 1].y);

//        cout << minX[i] << " " << minY[i] << endl;
//        cout << maxX[i] << " " << maxY[i] << endl;
//        cout << endl;

        for(int j = 0; j < n; j ++)
            if(minX[i] <= p[j].x && p[j].x <= maxX[i] && minY[i] <= p[j].y && p[j].y  <= maxY[i])
                pts[i].pb(p[j]);
    }
}

int get(bool dir, int idx)
{
/*
    if(idx == 9)
    {
        cout << "sss " << idx << endl;
        for(int i = 0; i < pts[idx].size(); i ++)
            cout << pts[idx][i].x << " " << pts[idx][i].y << endl;
    }
*/
    int br = pts[idx].size();
    int w1 = br, w2 = br + 1;
    PII w1first, w1second;
    PII w2first, w2second;

    int d[MAXN], dist[MAXN][MAXN];
    bool used[MAXN];

    memset(used, 0, sizeof(used));
    memset(dist, 0, sizeof(dist));

    for(int i = 0; i < br; i ++)
        for(int j = i + 1; j < br; j ++)
            dist[i][j] = dist[j][i] = max(abs(pts[idx][i].x - pts[idx][j].x), abs(pts[idx][i].y - pts[idx][j].y));

    if(!dir) dist[w1][w2] = dist[w2][w1] = maxY[idx] - minY[idx];
    else dist[w1][w2] = dist[w2][w1] = maxX[idx] - minX[idx];

    if(!dir)
    {
        if(wall[0][idx].y == minY[idx])
        {
            w1first = wall[0][idx]; w1second = wall[0][idx + 1];
            w2first = wall[1][idx]; w2second = wall[1][idx + 1];
        }
        else
        {
            w1first = wall[1][idx]; w1second = wall[1][idx + 1];
            w2first = wall[0][idx]; w2second = wall[0][idx + 1];
        }

        if(w1first.x > w1second.x) swap(w1first, w1second);
        if(w2first.x > w2second.x) swap(w2first, w2second);

        if(w1first.y > w2first.y)
        {
            swap(w1first, w2first);
            swap(w1second, w2second);
        }
    }
    else
    {
        if(wall[0][idx].x == minX[idx])
        {
            w1first = wall[0][idx]; w1second = wall[0][idx + 1];
            w2first = wall[1][idx]; w2second = wall[1][idx + 1];
        }
        else
        {
            w1first = wall[1][idx]; w1second = wall[1][idx + 1];
            w2first = wall[0][idx]; w2second = wall[0][idx + 1];
        }

        if(w1first.y > w1second.y) swap(w1first, w1second);
        if(w2first.y > w2second.y) swap(w2first, w2second);

        if(w1first.x > w2first.x)
        {
            swap(w1first, w2first);
            swap(w1second, w2second);
        }
    }

//    cout << w1first.x << " " << w1first.y << "  " << w1second.x << " " << w1second.y << endl;
//    cout << w2first.x << " " << w2first.y << "  " << w2second.x << " " << w2second.y << endl;

    for(int i = 0; i < br; i ++)
        if(!dir)
        {
            if(w1first.x <= pts[idx][i].x && pts[idx][i].x <= w1second.x)
                dist[i][w1] = dist[w1][i] = pts[idx][i].y - minY[idx];
            else if(w1first.x > pts[idx][i].x)
                dist[i][w1] = dist[w1][i] = max(w1first.x - pts[idx][i].x, pts[idx][i].y - w1first.y);
            else
                dist[i][w1] = dist[w1][i] = max(pts[idx][i].x - w1second.x, pts[idx][i].y - w1second.y);
        }
        else
        {
            if(w1first.y <= pts[idx][i].y && pts[idx][i].y <= w1second.y)
                dist[i][w1] = dist[w1][i] = pts[idx][i].x - minX[idx];
            else if(w1first.y > pts[idx][i].y)
                dist[i][w1] = dist[w1][i] = max(w1first.y - pts[idx][i].y, pts[idx][i].x - w1first.x);
            else
                dist[i][w1] = dist[w1][i] = max(pts[idx][i].y - w1second.y, pts[idx][i].x - w1second.x);
        }

    for(int i = 0; i < br; i ++)
        if(!dir)
        {
            if(w2first.x <= pts[idx][i].x && pts[idx][i].x <= w2second.x)
                dist[i][w2] = dist[w2][i] = maxY[idx] - pts[idx][i].y;
            else if(w2first.x > pts[idx][i].x)
                dist[i][w2] = dist[w2][i] = max(w2first.x - pts[idx][i].x, w2first.y - pts[idx][i].y);
            else
                dist[i][w2] = dist[w2][i] = max(pts[idx][i].x - w2second.x, w2second.y - pts[idx][i].y);
        }
        else
        {
            if(w2first.y <= pts[idx][i].y && pts[idx][i].y <= w2second.y)
                dist[i][w2] = dist[w2][i] = maxX[idx] - pts[idx][i].x;
            else if(w2first.y > pts[idx][i].y)
                dist[i][w2] = dist[w2][i] = max(w2first.y - pts[idx][i].y, w2first.x - pts[idx][i].x);
            else
                dist[i][w2] = dist[w2][i] = max(pts[idx][i].y - w2second.y, w2second.x - pts[idx][i].x);
        }

    br += 2;

//    for(int i = 0; i < br; i ++)
//    {
//        for(int j = 0; j < br; j ++) cout << dist[i][j] << " ";
//        cout << endl;
//    }

    for(int i = 0; i < br; i ++)
        d[i] = dist[i][w1];
    used[w1] = 1;

    while(1)
    {
        int j = -1, mn = INF;
        for(int i = 0; i < br; i ++)
            if(!used[i] && d[i] < mn)
                j = i, mn = d[i];

        if(j == -1) break;
//        cout << j << endl;
        used[j] = 1;

        for(int i = 0; i < br; i ++)
            if(!used[i] && d[i] > max(d[j], dist[i][j]))
                d[i] = max(d[j], dist[i][j]);
    }

//    cout << d[w2] << endl;
//    cout << endl;

    return d[w2];
}

void solve()
{
    for(int i = 0; i < m; i ++)
    {
        int tmp = get(i & 1, i);
//        cout << tmp << endl;
        if(ans > tmp) ans = tmp;
    }
    printf("%d\n", ans);
}

int main()
{
    read();
    init();
    solve();

    return 0;
}
