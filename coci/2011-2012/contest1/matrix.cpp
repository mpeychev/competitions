#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 512;

int n;
int m[MAXN][MAXN];
int a[MAXN][MAXN], b[MAXN][MAXN];
int ans = 0;

void read()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
        {
            scanf("%d", &m[i][j]);
            a[i][j] = m[i][j];
            b[i][j] = m[i][j];
        }
}

void solve()
{
    for(int k = 2; k <= n; k ++)
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
            {
                if(i + k - 1 < n && j + k - 1 < n)
                    a[i][j] += m[i + k - 1][j + k - 1];
                
                if(i + k - 1 < n && j - k + 1 >= 0)
                {
                    b[i][j] += m[i + k - 1][j - k + 1];
                    ans = max(ans, a[i][j - k + 1] - b[i][j]);
                }
            }
    
    cout << ans << endl;
}

int main()
{
    read();
    solve();
    
    return 0;
}
