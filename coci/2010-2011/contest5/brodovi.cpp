#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int m[5010];
int res;
bool used[5010];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&m[i]);
    
    for(int i=2;i<=n;i++)
        if(!used[i])
        {
            res ++;
            used[i] = 1;
            for(int j=i+1;j<=n;j++)
                if((m[j]-m[i])%(m[i]-1) == 0)
                    used[j] = 1;
        }
    
    printf("%d\n",res);
    
    return 0;
}
