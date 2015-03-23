#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

FILE *in = fopen("skate.10.in", "r");

typedef pair<int, int> PII;

int r, c;
char s[128][128];
vector< PII > v;

bool valid(int x, int y)
{
    if(x < 0 || x >= r || y < 0 || y >= c) return false;
    return true;
}

int main()
{
    fscanf(in, "%d %d\n", &r, &c);
    for(int i = 0; i < r; i ++)
        fscanf(in, "%s", &s[i]);

    int x, y;
    while(scanf("%d %d",&x,&y) == 2)
    {
        x --; y --;
        if(!valid(x, y) || s[x][y] != '.')
        {
            printf("1 no\n");
            return 0;
        }
        v.pb(mp(x, y));
    }

    if(v[0] != mp(0, 0))
    {
        printf("2 no\n");
        return 0;
    }

    for(int i = 1; i < v.size(); i ++)
        if(v[i] == v[i - 1] || (v[i].first != v[i - 1].first && v[i].second != v[i - 1].second))
        {
            printf("3 no\n");
            return 0;
        }

    if(v[ v.size() - 1 ] != mp(r - 1, c - 1))
    {
        printf("4 no\n");
        return 0;
    }

    printf("ok\n");

    return 0;
}
