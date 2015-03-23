/*
  Source: usaco - 2004/2005 - mar
  Task: yogfac
  KeyW: dp (+ small optimization)
*/
#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long LL;

const int MAXN = 10010;
const int INF = (1 << 30);

int n, s;
int c[MAXN], y, mxc = -1;
LL ans;

int main()
{
    scanf("%d %d", &n, &s);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d %d", &c[i], &y);
        if(c[i] > mxc) mxc = c[i];

        LL mn = INF;
        for(int j = i; j >= 0 && s * (i - j) <= mxc; j --)
            mn = min(mn, (s * (i - j) + c[j]) * (LL)y);

        ans += mn;
    }

    cout << ans << endl;

    return 0;
}
