#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 312;
const int INF = (1 << 30);

int n, m;
int x;
int toAdd;
vector<int> a;
int dp[2][2][MAXN][MAXN];
int mx;

void init()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        if(!x) toAdd = m;
        else a.pb(x);
    }
    n = a.size();
    sort(a.begin(), a.end());
}

void goRight(int idx)
{
    int res = toAdd;
    for(int i = idx; i < n; i ++)
        if(a[i] >= m) break;
        else res += m - a[i];

    if(mx < res) mx = res;
}

void goLeft(int idx)
{
    int res = toAdd;
    for(int i = idx; i >= 0; i --)
    {
        if(-a[i] >= m) break;
        else res += m + a[i];
    }

    if(mx < res) mx = res;
}

void solve()
{
    if(n == 0)
    {
        printf("%d\n", toAdd);
        return;
    }
    if(a[0] > 0)
    {
        goRight(0);
        printf("%d\n", mx);
        return;
    }

    if(a[n - 1] < 0)
    {
        goLeft(n - 1);
        printf("%d\n", mx);
        return;
    }

    for(int i = 0; i < n - 1; i ++)
        if(a[i] < 0 && a[i + 1] > 0)
        {
            goLeft(i);
            goRight(i + 1);
            break;
        }

    for(int i = 0; i < n; i ++)
        for(int j = 1; j <= n; j ++)
            if(a[i] < 0)
                dp[0][0][i][j] = dp[0][1][i][j] = -(j * a[i]);
            else
                dp[0][0][i][j] = dp[0][1][i][j] = j * a[i];

    for(int len = 2; len <= n; len ++)
    {
        int mn = INF;

        for(int dir = 0; dir <= 1; dir ++)
            for(int pos = 0; pos < n; pos ++)
                for(int coef = 1; coef <= n; coef ++)
                    dp[1][dir][pos][coef] = INF;

//        left .. dir = 0
        for(int pos = 0; pos + len - 1 < n; pos ++)
            for(int coef = 1; coef <= n - len + 1; coef ++)
            {
                int t1, t2;
                t1 = coef * (a[pos + 1] - a[pos]) + dp[0][0][pos + 1][coef + 1];
                t2 = coef * (a[pos + len - 1] - a[pos]) + dp[0][1][pos + len - 1][coef + 1];

                if(t1 < t2) dp[1][0][pos][coef] = t1;
                else dp[1][0][pos][coef] = t2;
            }
//        right .. dir = 1
        for(int pos = len - 1; pos < n; pos ++)
            for(int coef = 1; coef <= n - len + 1; coef ++)
            {
                int t1, t2;
                t1 = coef * (a[pos] - a[pos - 1]) + dp[0][1][pos - 1][coef + 1];
                t2 = coef * (a[pos] - a[pos - len + 1]) + dp[0][0][pos - len + 1][coef + 1];

                if(t1 < t2) dp[1][1][pos][coef] = t1;
                else dp[1][1][pos][coef] = t2;
            }

        memcpy(dp[0], dp[1], sizeof(dp[1]));

//        finish left .. dir = 0
        for(int pos = 0; pos + len - 1 < n; pos ++)
        {
            if(a[pos] > 0) break;
            if(a[pos + len - 1] < 0) continue;
            if(mn > dp[0][0][pos][1]) mn = dp[0][0][pos][1];
        }

//        finish right .. dir = 1
        for(int pos = n - 1; pos - len + 1 >= 0; pos --)
        {
            if(a[pos] < 0) break;
            if(a[pos - len + 1] > 0) continue;
            if(mn > dp[0][1][pos][1]) mn = dp[0][1][pos][1];
        }

        if(mx < toAdd + len * m - mn) mx = toAdd + len * m - mn;
    }

    printf("%d\n", mx);
}

int main()
{
    init();
    solve();

    return 0;
}
