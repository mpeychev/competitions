/*
  Source: boi - 2004
  Task: Team
  KeyW: Reshavane na zadachi s pylni dvoichni dyrveta (index-ni dyrveta).
        Update & Query sistemi s cena na operacia LogN ili LogN*LogN.
*/
// To check - Z-training
#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 500010;
const int INF  = 500010;

int n,a;
int Res[MAXN];
int Ind[2][MAXN];
int Tree[MAXN];

void Update(int ind,int val)
{
    while(ind<=n)
    {
        Tree[ind] = min(Tree[ind] , val);
        ind += (ind & -ind);
    }
}

int Query(int ind)
{
    int ret = INF;
    while(ind)
    {
        ret = min(ret , Tree[ind]);
        ind -= (ind & -ind);
    }
    return ret;
}

void Init()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&Res[i]);
    for(int i=0;i<2;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a);
            Ind[i][a]=j;
        }
    for(int i=0;i<=n;i++) Tree[i] = INF;
}

void Solve()
{
    int sol=n;
    for(int i=0;i<n;i++)
    {
        int get = Query(Ind[0][Res[i]]);
        if(get<Ind[1][Res[i]]) sol --;
        Update(Ind[0][Res[i]] , Ind[1][Res[i]]);
    }

    printf("%d\n",sol);
}

int main()
{
    Init();
    Solve();
    return 0;
}
