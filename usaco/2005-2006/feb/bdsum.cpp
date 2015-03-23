/*
  Source: usaco - 2005/2006 - feb
  Task: bdsum
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int n, target;
int m[16], tmp[16];

bool check()
{
    memcpy(tmp, m, sizeof(m));
    for(int i = 0; i < n - 1; i ++)
        for(int j = 0; j < n - 1; j ++)
            tmp[j] += tmp[j + 1];
    return tmp[0] == target;
}

void write()
{
    for(int i = 0; i < n; i ++)
    {
        if(i) printf(" ");
        printf("%d",m[i]);
    }
    printf("\n");
}

int main()
{
    scanf("%d %d",&n,&target);

    for(int i = 0; i < n; i ++)
        m[i] = i + 1;

    do
    {
        if(check())
        {
            write();
            return 0;
        }
    }
    while(next_permutation(m, m + n));

    return 0;
}
