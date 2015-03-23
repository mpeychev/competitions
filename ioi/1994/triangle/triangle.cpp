#include <iostream>
using namespace std;

int n;
int tmp[128],m[128];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
            for(int j=1;j<=i;j++) { scanf("%d",&tmp[j]); tmp[j]+=max(m[j],m[j-1]); }
            for(int j=1;j<=i;j++) m[j]=tmp[j];
    }
    
    int sol=tmp[0];
    for(int i=1;i<=n;i++) sol=max(sol,tmp[i]);
    
    printf("%d\n",sol);

    return 0;
}
