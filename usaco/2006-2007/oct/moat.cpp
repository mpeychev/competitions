/*
  Source: usaco - 2006/2007 - oct
  Task: moat
  KeyW: convex hull
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>

#define x first
#define y second
#define mp make_pair

using namespace std;

typedef pair<int, int> Point;

int n;
Point p[5010];
Point O;
int ind;

Point hull[5010];
int sz;

double ans;

short int s(Point a, Point b, Point c)
{
    int d = (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
    if(d < 0) return -1;
    return 1;
}

bool cmp(Point a, Point b)
{
    return s(O, a, b) == 1;
}

void init()
{
    O = mp(50000, 50000);
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d %d",&p[i].x,&p[i].y);
        if(p[i].y < O.y || (p[i].y == O.y && p[i].x < O.x))
        {
            O = p[i];
            ind = i;
        }
    }
    swap(p[0], p[ind]);
    sort(p + 1, p + n, cmp);
}

void build()
{
    hull[0] = p[0];
    sz ++;
    for(int i = 1; i < n; i ++)
    {
        while(sz >= 2 && s(hull[sz - 2], hull[sz - 1], p[i]) == -1) sz --;
        hull[sz] = p[i];
        sz ++;
    }
}

int SQR(int a) { return a * a; }

double dist(Point a, Point b)
{
    int t = SQR(a.x - b.x) + SQR(a.y - b.y);
    return (double)sqrt((double)t);
}

void calc()
{
    for(int i = 0; i < sz - 1; i ++)
        ans += dist(hull[i], hull[i + 1]);
    ans += dist(hull[0], hull[sz - 1]);

    printf("%.2lf\n",ans);
}

int main()
{
    init();
    build();
    calc();

    return 0;
}
