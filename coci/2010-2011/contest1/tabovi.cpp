#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int p[1024],k;
int ans,tmp,fl;

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&k);
        if(k>p[i])
        {
            if(fl==1)
            {
                if(tmp<k-p[i]) tmp=k-p[i];
            }
            else
            {
                ans+=tmp;
                tmp=0;
                fl=1;
                tmp=k-p[i];
            }
        }
        else
        {
            if(fl==-1)
            {
                if(tmp<p[i]-k) tmp=p[i]-k;
            }
            else
            {
                ans+=tmp;
                tmp=0;
                fl=-1;
                tmp=p[i]-k;
            }
        }
    }
    ans+=tmp;
    printf("%d\n",ans);
    return 0;
}
