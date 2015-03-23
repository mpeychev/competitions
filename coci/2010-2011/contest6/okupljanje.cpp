#include <stdio.h>
#include <iostream>

using namespace std;

int l,p;

int main()
{
    scanf("%d %d",&l,&p);
    for(int i=0;i<5;i++)
    {
        int s;
        if(i) printf(" ");
        scanf("%d",&s);
        printf("%d",s - l*p);
    }
    printf("\n");
    return 0;
}
