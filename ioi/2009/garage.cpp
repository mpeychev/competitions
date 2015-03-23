/*
  Source: ioi - 2009
  Task: garage
*/
#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

int n,m,x;
int r[128],w[2048];
int used[128];
long long sol;
queue<int> q;

void read()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&r[i]);
    for(int i=1;i<=m;i++) scanf("%d",&w[i]);
}

void solve()
{
    for(int i=0;i<2*m;i++)
    {
        scanf("%d",&x);
        if(x>0)
        {
            bool fl=false;
            for(int j=1;j<=n;j++) if(!used[j]) { used[j]=x; sol+=r[j]*w[x]; fl=true; break; }
            if(!fl) q.push(x);
        }
        else
        {
            x=-x;
            for(int j=1;j<=n;j++)
             if(used[j]==x)
             {
                    if(q.empty()) { used[j]=0; break; }
                    x=q.front(); q.pop();
                    used[j]=x;
                    sol+=r[j]*w[x];
                    break;
             }
        }
    }
    
    cout << sol << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
