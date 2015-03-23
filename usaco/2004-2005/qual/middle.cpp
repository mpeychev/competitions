/*
  Source: usaco - 2004/2005 - qual
  Task: middle
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
int m[10010];

int main()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
        scanf("%d",m + i);
    sort(m, m + n);
    printf("%d\n",m[n / 2]);

    return 0;
}
