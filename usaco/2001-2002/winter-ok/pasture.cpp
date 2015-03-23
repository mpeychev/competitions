/*
  Source: usaco - 2001/2002 - winter
  Task: pasture
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int n, a;
int s[3010];
int mn = 3000010;
int l = -1, r = -1;

inline int abs(int x)
{
    if(x < 0) return -x;
    return x;
}

int main()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d",&a);
        s[i] = s[i - 1] + a;
    }

    for(int i = 1; i <= n; i ++)
        for(int j = i; j <= n; j ++)
        {
            int t = abs(s[j] - s[i - 1]);
            if(t < mn || (t == mn && r - l + 1 < j - i + 1))
            {
                l = i; r = j;
                mn = t;
            }
        }

    printf("%d %d %d\n",l,r,mn);

    return 0;
}
