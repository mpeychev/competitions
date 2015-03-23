#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 1000100;

int n;
int a;
long long c1[32];
long long s = 0;
bool fl = false;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &a);
        for(int j = 0; a; j ++)
        {
            if(a & 1) c1[j] ++;
            a >>= 1;
        }
    }
    
    for(int i = 20; i >= 0; i --)
    {
        if(c1[i] && !fl) fl = true;
        
        if(fl)
        {
            long long x = c1[i];
            long long y = n - c1[i];
            
            s += x * y * (1 << i);
        }
    }
    
    cout << s << endl;
    
    return 0;
}
