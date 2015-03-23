#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int m[128];

void read()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&m[i]);
}

void solve()
{
    int ans = 0;
    for(int i=n-2;i>=0;i--)
        if(m[i] >= m[i + 1])
        {
            ans += (m[i] - m[i + 1] + 1);
            m[i] = m[i + 1] - 1;
        }
    printf("%d\n",ans);
}

int main()
{
    read();
    solve();

    return 0;
}
