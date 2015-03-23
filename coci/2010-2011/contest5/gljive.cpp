#include <stdio.h>
#include <iostream>

using namespace std;

const int n = 10;

int m[n];
int r = 10000 , ans;

int MyAbs(int x)
{
    if(x < 0) return -x;
    return x;
}

int main()
{
    int sum = 0;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m[i]);
        sum += m[i];
        if(MyAbs(sum-100) <= r)
        {
            ans = sum;
            r = MyAbs(sum-100);
        }
    }
    
    printf("%d\n",ans);
    
    return 0;
}
