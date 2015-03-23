/*
  Source: ioi-2002
  Task: XOR
  KeyW: Postoianno podobriavane na situaciata.
*/
#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef pair<int,int> pii;
typedef pair< pii , pii > Type;

const int MAXN = (1<<11);

int n;
bool d[MAXN][MAXN];
vector< Type > sol;

void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&d[i][j]);
}

void xxor(int l,int r,int t,int b)
{
    for(int i=t;i<=b;i++)
        for(int j=l;j<=r;j++)
            d[i][j]^=1;
}

void solve()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(d[i][j])
            {
                int left,right,top,bottom;
                bool fl=false;
                left=j; top=i;
                
                // try 4
                for(int k=j;k<=n;k++)
                    for(int h=i;h<=n;h++)
                        if((d[i][k]+d[i][k+1]+d[i-1][k]+d[i-1][k+1])%2 &&
                           (d[h][j]+d[h][j-1]+d[h+1][j]+d[h+1][j-1])%2 &&
                           (d[h][k]+d[h][k+1]+d[h+1][k]+d[h+1][k+1])%2)
                        {
                            right=k;
                            bottom=h;
                            fl=true;
                            goto mark;
                        }

                if(!fl) { // try 3
                for(int k=n;k>=j;k--)
                    if((d[i][k]+d[i][k+1]+d[i-1][k]+d[i-1][k+1])%2)
                    {
                        right=k;
                        break;
                    }

                for(int k=n;k>=i;k--)
                    if((d[k][j]+d[k][j-1]+d[k+1][j]+d[k+1][j-1])%2)
                    {
                        bottom=k;
                        break;
                    }
                }
                mark:
                xxor(left,right,top,bottom);
                sol.pb( mp( mp(left,right) , mp(top,bottom) ) );
            }
}

void write()
{
    printf("%d\n",sol.size());
    for(int i=0;i<sol.size();i++)
        printf("%d %d %d %d\n",sol[i].fi.fi,sol[i].fi.se,sol[i].se.fi,sol[i].se.se);
}

int main()
{
    init();
    solve();
    write();

    return 0;
}
