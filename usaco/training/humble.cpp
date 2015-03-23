/*
PROG: humble
LANG: C++
ID: mompej951
*/
#include <stdio.h>

typedef long long LL;

int k,n;
LL s[128],v[100010];
int ind[128];

int main()
{
    freopen("humble.in","r",stdin);
    freopen("humble.out","w",stdout);
    
    scanf("%d %d",&k,&n);
    for(int i=0;i<k;i++) scanf("%I64d",&s[i]);
    
    v[0]=1;
    for(int i=1;i<=n;i++)
    {
        LL mn=v[i-1]*s[k-1];
        for(int j=0;j<k;j++)
        {
            while(v[ ind[j] ]*s[j]<=v[i-1]) ind[j]++;
            if(mn>v[ ind[j] ]*s[j]) mn=v[ ind[j] ]*s[j];
        }
        v[i]=mn;
    }
    
    printf("%lld\n",v[n]);
    
    return 0;
}
