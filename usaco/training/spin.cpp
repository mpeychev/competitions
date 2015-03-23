/*
PROG: spin
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define init first
#define ext second
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int,int> pii;
typedef struct
{
    int speed;
    int w;
    vector< pii > v;
} wheel;

wheel m[8];
int ind[8];

int sol = 360;

void read()
{
    for(int i=0;i<5;i++)
    {
        scanf("%d %d",&m[i].speed,&m[i].w);
        for(int j=0;j<m[i].w;j++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            m[i].v.pb( mp(x,y) );
        }
    }
}

int check()
{
    int temp[8];
    for(int i=0;i<360;i++)
    {
        for(int j=0;j<5;j++) temp[j]=(m[j].v[ ind[j] ].init + i*m[j].speed)%360;
        for(int j=0;j<5;j++)
        {
            bool fl=true;
            
            int e[8];
            memcpy(e,temp,sizeof(temp));
            for(int k=0;k<5;k++) if(e[k]<=temp[j]) e[k]+=360;
            for(int k=0;k<5;k++) if(e[k]+m[k].v[ ind[k] ].ext<e[j]) { fl=false; break; }
            
            if(fl) return i;
        }
    }
    return -1;
}

void rec(int k)
{
    if(k==5)
    {
        int ret=check();
        if(ret!=-1 && ret<sol) sol=ret;
        return;
    }
    for(int i=0;i<m[k].w;i++)
    {
        ind[k]=i;
        rec(k+1);
    }
}

int main()
{
    freopen("spin.in","r",stdin);
    freopen("spin.out","w",stdout);
    
    read();
    rec(0);
    if(sol!=360) printf("%d\n",sol);
    else printf("none\n");
    
    return 0;
}
