#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long long LL;

int n, m;
int x[100100], y[100100];
long long x1[100100], y1[100100];
char s[300300];
long long ans;

void read()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &x[i], &y[i]);
    scanf("%s", &s);
    
    sort(x, x + n);
    sort(y, y + n);
    
    x1[0] = (LL)x[0];
    y1[0] = (LL)y[0];
    for(int i = 1; i < n; i ++)
    {
        x1[i] = x1[i - 1] + (LL)x[i];
        y1[i] = y1[i - 1] + (LL)y[i];
    }
}

long long sumX(long long k)
{
    int l = 0, r = n - 1, mid;
    int pos = -1;
    
    while(l <= r)
    {
        mid = (l + r) >> 1;
        if(x[mid] <= k)
        {
            pos = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    if(pos == -1)
    {
        cout << x1[n - 1] - n * k << endl;
        return x1[n - 1] - n * k;
    }
    else
    {
        return (LL)(pos + 1) * k - x1[pos] + x1[n - 1] - x1[pos] - (n - pos - 1) * k;
    }
}

long long sumY(long long k)
{
    
    int l = 0, r = n - 1, mid;
    int pos = -1;
    
    while(l <= r)
    {
        mid = (l + r) >> 1;
        if(y[mid] <= k)
        {
            pos = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    if(pos == -1)
    {
        cout << y1[n - 1] - n * k << endl;
        return y1[n - 1] - n * k;
    }
    else
    {
        return (pos + 1) * k - y1[pos] + y1[n - 1] - y1[pos] - (n - pos - 1) * k;
    }
}

int main()
{
    read();
    
    long long X = 0, Y = 0;
    for(int i = 0; i < m; i ++)
    {
        switch(s[i])
        {
            case 'S': Y ++; break;
            case 'J': Y --; break;
            case 'I': X ++; break;
            case 'Z': X --; break;
        }
        
        printf("%lld\n", sumX(X) + sumY(Y));
    }
    
    return 0;
}
