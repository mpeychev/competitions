#include <stdio.h>
#include <iostream>

using namespace std;

int m,n,k;

int main()
{
    scanf("%d %d %d",&m,&n,&k);
    for(int i=n;i>=0;i--)
    {
        int males_intern=min(k,n-i);
        int girls_intern=k-males_intern;
        if(m-girls_intern>=2*i)
        {
            printf("%d\n",i);
            break;
        }
    }
    
    return 0;
}
