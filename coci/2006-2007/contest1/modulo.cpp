#include <stdio.h>

int cnt[64];
int a;

int main()
{
    for(int i=0;i<10;i++)
    {
        scanf("%d",&a);
        cnt[a%42]=1;
    }
    
    int sol=0;
    for(int i=0;i<42;i++) sol+=cnt[i];
    
    printf("%d\n",sol);
    
    return 0;
}
