#include <stdio.h>

int A,I;

int check(int x)
{
    if(x%A==0) return x/A;
    return x/A+1;
}

int main()
{
    scanf("%d %d",&A,&I);
    for(int i=A*(I-1);;i++)
        if(check(i)==I)
        {
            printf("%d\n",i);
            break;
        }

    return 0;
}
