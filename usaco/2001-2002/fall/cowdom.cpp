/*
  Source: usaco - 2001/2002 - fall
  Task: cowdom
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

int n, a, b;
int m[64];
vector<int> sol;

int main()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d %d",&a,&b);
        m[i] = a + b;
    }
    sort(m, m + n);

    int p = 0;
    for(int i = 0; i < n; i ++)
    {
        int d = m[i] + p;
        sol.pb(d % 10);
        p = d / 10;
    }
    if(p) sol.pb(1);

    reverse(sol.begin(), sol.end());

    for(int i = 0; i < sol.size(); i ++)
        printf("%d",sol[i]);
    printf("\n");

    return 0;
}
