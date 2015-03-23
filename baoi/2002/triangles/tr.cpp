/*
  Source: baoi - 2002
  Task: Triangles
  KeyW: Obrabotka na elementite siakash vseki e posleden.
        Obrabotka na ravninata po lenti.
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef struct
{
    int x,y,m;
} Triangle;

const int MINX = -10000010;

Triangle make(int _x,int _y,int _m)
{
    Triangle ret;
    ret.x=_x; ret.y=_y; ret.m=_m;
    return ret;
}

struct cmp
{
    bool operator()(Triangle t1,Triangle t2)
    {
        if(t1.x<t2.x) return false;
        if(t1.x>t2.x) return true;
        if(t1.y<t2.y) return false;
        if(t1.y>t2.y) return true;
        return !(t1.m<t2.m);
    }
};

int n;
Triangle inp;
priority_queue< Triangle , vector<Triangle> , cmp > pq;

void init()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d %d",&inp.x,&inp.y,&inp.m);
        pq.push(inp);
    }
}

void solve()
{
    ll ans=1;
    Triangle tmp=make(MINX,0,0);
    while(!pq.empty())
    {
        inp=pq.top();
        pq.pop();

        if(tmp.x<inp.x || tmp.y+tmp.m<=inp.y)
        {
            ans+=2*tmp.m-1;
            tmp.x=inp.x; tmp.y=inp.y; tmp.m=inp.m;
        }
        else tmp.m=max(tmp.m,inp.y+inp.m-tmp.y);

        if(inp.m>1) pq.push(make(inp.x+1 , inp.y , inp.m-1));
    }

    ans+=2*tmp.m-1;

    if(ans%2==0) cout << ans/2 << ".0\n";
    else cout << ans/2 << ".5\n";
}

int main()
{
    init();
    solve();

    return 0;
}
