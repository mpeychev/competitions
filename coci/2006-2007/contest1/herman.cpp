#include <stdio.h>

#define pi 3.1415926535897932384626433832795

double n;

int main()
{
    scanf("%lf",&n);
    printf("%.6lf\n%.6lf\n",pi*n*n,2*n*n);
    
    return 0;
}
