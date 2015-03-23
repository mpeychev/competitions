#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int p[1024];

void read()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);
}

void solve()
{
    int ans = 0;
    int down = -1;
    for(int i=0;i<n;i++)
        if(i == 0) down = p[i];
        else
        {
            if(p[i] > p[i - 1]) ans = max(ans , p[i] - down);
            else down = p[i];
        }
    printf("%d\n",ans);
}

int main()
{
    read();
    solve();

    return 0;
}
