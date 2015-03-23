#include <stdio.h>

int n;
int a[128],b[128];
int taba[128],tabb[128];

void solve()
{
    int ia,ib;
    int sol=0;
    
    for(int i=1;i<=100;i++) { a[i]=taba[i]; b[i]=tabb[i]; }
    
    for(ia=1,ib=100;ia<=100 && ib>=1;)
    {
        if(a[ia])
        {
            while(!b[ib]) ib--;
            if(sol<ia+ib) sol=ia+ib;
            if(a[ia]==b[ib]) { a[ia]=0; b[ib]=0; }
            else if(a[ia]>b[ib]) { a[ia]-=b[ib]; b[ib]=0; }
            else { b[ib]-=a[ia]; a[ia]=0; }
        }
        else if(b[ib])
        {
            while(!a[ia]) ia++;
            if(sol<ia+ib) sol=ia+ib;
            if(a[ia]==b[ib]) { a[ia]=0; b[ib]=0; }
            else if(a[ia]>b[ib]) { a[ia]-=b[ib]; b[ib]=0; }
            else { b[ib]-=a[ia]; a[ia]=0; }
        }
        if(!a[ia]) ia++;
        if(!b[ib]) ib--;
    }
    printf("%d\n",sol);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        taba[x]++; tabb[y]++;
        solve();
    }
    
    return 0;
}
