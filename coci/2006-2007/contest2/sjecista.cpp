#include <stdio.h>

int n;
long long p=0;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-2;i++) p+=i*(n-i-2);
    printf("%d\n",(p*n)/4);
    
    return 0;
}
