#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

int n, h;
vector<int> a, b, c, d;

void init()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &h);
        if(h > 0) a.pb(h);
        else c.pb(-h);
    }
    
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &h);
        if(h > 0) d.pb(h);
        else b.pb(-h);
    }
}

int calc(vector<int> x, vector<int> y)
{
    int ret = 0;
    int i = 0, j = 0;
    
    while(i < x.size() && j < y.size())
    {
        if(x[i] < y[j])
        {
            ret ++;
            i ++;
        }
        j ++;
    }
    
    return ret;
}

int main()
{
    init();
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    sort(d.begin(), d.end());
    
    cout << calc(a, b) + calc(d, c) << endl;
    
    return 0;
}
