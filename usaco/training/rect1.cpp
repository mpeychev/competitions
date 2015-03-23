/*
PROG: rect1
LANG: C++
ID: mompej951
*/

/*
  Source: usaco, training 3.1
  Task: rect1
  KeyW: rectangles
*/

#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back

using namespace std;

typedef struct
{
    int lx,ly,dx,dy;
    int col;
} rect;

int n;
rect tmp,p;
vector<rect> v,vv;
int color[2510];

int main()
{
    freopen("rect1.in","r",stdin);
    freopen("rect1.out","w",stdout);
    
    tmp.lx=0; tmp.ly=0; tmp.col=1;
    scanf("%d %d %d",&tmp.dx,&tmp.dy,&n);
    tmp.dx--; tmp.dy--;
    v.pb(tmp);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d %d %d %d",&tmp.lx,&tmp.ly,&tmp.dx,&tmp.dy,&tmp.col);
        tmp.dx--; tmp.dy--;
        vv.clear();
        vv.pb(tmp);
        for(int j=0;j<v.size();j++)
        {
            if(v[j].lx>tmp.dx || v[j].ly>tmp.dy || v[j].dx<tmp.lx || v[j].dy<tmp.ly) { vv.pb(v[j]); continue; }
            p.col=v[j].col;
            
            p.lx=v[j].lx; p.ly=v[j].ly; p.dx=v[j].dx; p.dy=tmp.ly-1;
            if(p.lx<=p.dx && p.ly<=p.dy) vv.pb(p);
            
            p.lx=v[j].lx; p.ly=max(tmp.ly,v[j].ly); p.dx=tmp.lx-1; p.dy=v[j].dy;
            if(p.lx<=p.dx && p.ly<=p.dy) vv.pb(p);
            
            p.lx=tmp.dx+1; p.ly=max(tmp.ly,v[j].ly); p.dx=v[j].dx; p.dy=v[j].dy;
            if(p.lx<=p.dx && p.ly<=p.dy) vv.pb(p);
            
            p.lx=max(tmp.lx,v[j].lx); p.ly=tmp.dy+1; p.dx=min(tmp.dx,v[j].dx); p.dy=v[j].dy;
            if(p.lx<=p.dx && p.ly<=p.dy) vv.pb(p);
        }
        v.clear();
        v=vv;
        /*
        for(int j=0;j<v.size();j++)
         cout << v[j].lx << " " << v[j].ly << " " << v[j].dx << " " << v[j].dy << " " << v[j].col << endl;
        cout << endl;
        */
    }
    
    for(int i=0;i<v.size();i++) color[ v[i].col ] += (v[i].dx-v[i].lx+1)*(v[i].dy-v[i].ly+1);
    
    for(int i=1;i<=2500;i++) if(color[i]) printf("%d %d\n",i,color[i]);
    
    return 0;
}
