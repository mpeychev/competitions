#include <stdio.h>

bool fl1=true,fl2=true;

int main()
{
    for(int i=1;i<=8;i++)
    {
        int a;
        scanf("%d",&a);
        if(a!=i) fl1=false;
        if(a!=9-i) fl2=false;
    }
    if(fl1) printf("ascending");
    else if(fl2) printf("descending");
    else printf("mixed");
    printf("\n");
    
    return 0;
}
