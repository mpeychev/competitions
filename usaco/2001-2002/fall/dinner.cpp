/*
  Source: usaco - 2001/2002 - fall
  Task: dinner
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int n, dig;
int pos[50010];
int sol[50010];

int main()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d",&dig);
        pos[ dig ] = i;
    }

    dig = n;
    while(1)
    {
        if(dig <= 1) break;
        if(pos[dig - 1] > pos[dig])
        {
            swap(pos[dig - 1], pos[dig]);
            dig -= 2;
        }
        else dig --;
    }

    for(int i = 1; i <= n; i ++)
        sol[ pos[i] ] = i;

    for(int i = 1; i <= n; i ++)
        printf("%d\n",sol[i]);

    return 0;
}
