#include <stdio.h>
#include <iostream>

using namespace std;

int n, p;
int used[300000];
int br;
int dpow[10];

int poww(int dig)
{
    int ret = 1;
    for(int i = 0; i < p; i ++)
        ret *= dig;
    return ret;
}

int nxt(int x)
{
    int ret = 0;
    while(x)
    {
        ret += dpow[x % 10];
        x /= 10;
    }
    return ret;
}

int main()
{
    scanf("%d %d",&n,&p);

    for(int i = 0; i <= 9; i ++)
        dpow[i] = poww(i);

    for( ; ; )
    {
        if(used[n])
        {
            printf("%d\n",used[n] - 1);
            break;
        }
        br ++;
        used[n] = br;
        n = nxt(n);
    }

    return 0;
}
