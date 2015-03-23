#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stack>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

struct lily
{
    int x, y, f, idx;
};

const int MAXN = 300300;
const int MAX_XY = 100100;

int n, k;
lily l[MAXN];
PII coords[MAXN];
PII mxX[MAX_XY], mxY[MAX_XY];
int prev[MAXN];
stack<int> st;

void read()
{
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d %d %d", &l[i].x, &l[i].y, &l[i].f);
        coords[i] = mp(l[i].x, l[i].y);
        l[i].idx = i;
    }
}

bool cmp(lily a, lily b)
{
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    if(a.y < b.y) return true;
    return false;
}

void write()
{
    int tmp = n;
    for( ; ; )
    {
        st.push(tmp);
        if(tmp == 1) break;
        tmp = prev[tmp];
    }

    printf("%d\n", st.size());
    while(!st.empty())
    {
        printf("%d %d\n", coords[ st.top() ].first, coords[ st.top() ].second);
        st.pop();
    }
}

void solve()
{
    for(int i = 0; i <= 100000; i ++)
    {
        mxX[i] = mp(-1, -1);
        mxY[i] = mp(-1, -1);
    }

    sort(l + 1, l + n + 1, cmp);

    for(int i = 1; i <= n; i ++)
    {
        if(l[i].idx == 1)
        {
            mxX[ l[i].x ] = mp(l[i].f, 1);
            mxY[ l[i].y ] = mp(l[i].f, 1);
            continue;
        }

        int dx = -1, dy = -1;
        int power;

        if(mxX[ l[i].x ].first - k >= 0) dx = mxX[ l[i].x ].first - k + l[i].f;
        if(mxY[ l[i].y ].first - k >= 0) dy = mxY[ l[i].y ].first - k + l[i].f;

        if(dx == -1 && dy == -1) continue;

        if(dx >= dy)
        {
            prev[ l[i].idx ] = mxX[ l[i].x ].second;
            power = dx;
        }
        else
        {
            prev[ l[i].idx ] = mxY[ l[i].y ].second;
            power = dy;
        }

        if(mxX[ l[i].x ].first < power) mxX[ l[i].x ] = mp(power, l[i].idx);
        if(mxY[ l[i].y ].first < power) mxY[ l[i].y ] = mp(power, l[i].idx);

        if(l[i].idx == n)
        {
            printf("%d\n", power);
            write();
            break;
        }
    }
}

int main()
{
    read();
    solve();

    return 0;
}
