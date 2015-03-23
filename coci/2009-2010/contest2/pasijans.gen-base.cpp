#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

int a=100000000;

bool IsPrime(int x)
{
    for(int i=2;i<=sqrt(x);i++)
        if(x%i==0) return false;
    return true;
}

int main()
{
    for(int i=a;;i++)
        if(IsPrime(i))
        {
            printf("%d\n",i);
            system("Pause");
        }

    return 0;
}
