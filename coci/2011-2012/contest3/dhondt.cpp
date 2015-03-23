#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, double> PID;

const double eps = 1e-12;

int x;
int n;
int m[32];
int ans[32];
bool pr[32];

void read()
{
    scanf("%d %d\n", &x, &n);
    for(int i = 0; i < n; i ++)
    {
        char p;
        int g;
        scanf("%c %d\n", &p, &g);

        if(5 * x <= 100 * g) {
            m[p - 'A'] = g;
            pr[p - 'A'] = 1;
        }
    }
}

bool cmp(PID a, PID b)
{
    return (a.second - b.second > eps);
}

void solve()
{
    vector< PID > vec;

    for(int i = 0; i <= (int)('Z' - 'A'); i ++)
        if(m[i])
        {
            for(int j = 1; j <= 14; j ++)
                vec.pb(mp(i, (double)m[i] / (double)j));
        }
    sort(vec.begin(), vec.end(), cmp);

    for(int i = 0; i < 14; i ++)
        ans[ vec[i].first ] ++;
}

void write()
{
    for(int i = 0; i <= (int)('Z' - 'A'); i ++)
        if(pr[i])
            printf("%c %d\n", i + 'A', ans[i]);
}

int main()
{
    read();
    solve();
    write();

    return 0;
}
