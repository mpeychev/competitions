/*
  Source: usaco - 2006/2007
  Task: acng
*/
#include <stdio.h>
#include <iostream>

using namespace std;

long long n;
int ans = 0;

int main()
{
    scanf("%d",&n);
    while(n != 1)
    {
        ans ++;
        if(n & 1) n = 3 * n + 1;
        else n >>= 1;
    }
    printf("%d\n",ans);

    return 0;
}
