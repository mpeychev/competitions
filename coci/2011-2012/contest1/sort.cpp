#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

int n;
int m[100100];
int tree[100100];

void read()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &m[i]);
}

int sum(int idx)
{
    int ret = 0;
    while(idx)
    {
        ret += tree[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

void update(int idx)
{
    while(idx <= n)
    {
        tree[idx] ++;
        idx += (idx & -idx);
    }
}

void solve()
{
    long long sol = 0;
    
    int idx = 0;
    for(int i = 1; i < n; i ++)
        if(m[i] > m[i - 1])
        {
            if(idx != i - 1)
            {
                sol ++;
                reverse(m + idx, m + i);
            }
            
            idx = i;
        }
    
    if(idx != n - 1)
    {
        sol ++;
        reverse(m + idx, m + n);
    }
    
    for(int i = 0; i < n; i ++)
    {
        sol += sum(n) - sum(m[i] - 1);
        update(m[i]);
    }
    
    cout << sol << endl;
}

int main()
{
    read();
    solve();
    
    return 0;
}
