/*
PROG: maze1
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;

struct point
{
    int x,y;
};

int w,h;
string s[256];
int lvl1[256][128];
int lvl2[256][128];

bool ok(int x,int y)
{
    if(x<0 || y<0 || x>2*h || y>2*w) return false;
    return true;
}

void bfs1(int x,int y)
{
    point tmp;
    tmp.x=x; tmp.y=y;
    
    queue<point> q;
    lvl1[x][y]=1;
    q.push(tmp);
    while(!q.empty())
    {
        x=q.front().x; y=q.front().y;
        q.pop();
        if(s[x][y-1]!='|' && ok(x,y-2) && !lvl1[x][y-2])
        {
            lvl1[x][y-2]=lvl1[x][y]+1;
            tmp.x=x; tmp.y=y-2;
            q.push(tmp);
        }
        if(s[x][y+1]!='|' && ok(x,y+2) && !lvl1[x][y+2])
        {
            lvl1[x][y+2]=lvl1[x][y]+1;
            tmp.x=x; tmp.y=y+2;
            q.push(tmp);
        }
        if(s[x-1][y]!='-' && ok(x-2,y) && !lvl1[x-2][y])
        {
            lvl1[x-2][y]=lvl1[x][y]+1;
            tmp.x=x-2; tmp.y=y;
            q.push(tmp);
        }
        if(s[x+1][y]!='-' && ok(x+2,y) && !lvl1[x+2][y])
        {
            lvl1[x+2][y]=lvl1[x][y]+1;
            tmp.x=x+2; tmp.y=y;
            q.push(tmp);
        }
    }
}

void bfs2(int x,int y)
{
    point tmp;
    tmp.x=x; tmp.y=y;
    
    queue<point> q;
    lvl2[x][y]=1;
    q.push(tmp);
    while(!q.empty())
    {
        x=q.front().x; y=q.front().y;
        q.pop();
        if(s[x][y-1]!='|' && ok(x,y-2) && !lvl2[x][y-2])
        {
            lvl2[x][y-2]=lvl2[x][y]+1;
            tmp.x=x; tmp.y=y-2;
            q.push(tmp);
        }
        if(s[x][y+1]!='|' && ok(x,y+2) && !lvl2[x][y+2])
        {
            lvl2[x][y+2]=lvl2[x][y]+1;
            tmp.x=x; tmp.y=y+2;
            q.push(tmp);
        }
        if(s[x-1][y]!='-' && ok(x-2,y) && !lvl2[x-2][y])
        {
            lvl2[x-2][y]=lvl2[x][y]+1;
            tmp.x=x-2; tmp.y=y;
            q.push(tmp);
        }
        if(s[x+1][y]!='-' && ok(x+2,y) && !lvl2[x+2][y])
        {
            lvl2[x+2][y]=lvl2[x][y]+1;
            tmp.x=x+2; tmp.y=y;
            q.push(tmp);
        }
    }
}


int main()
{
    freopen("maze1.in","r",stdin);
    freopen("maze1.out","w",stdout);
    cin >> w >> h;
    cin.get();
    for(int i=0;i<2*h+1;i++) getline(cin,s[i]);
    
    bool fl=false;
    for(int i=1;i<2*w;i+=2)
    {
        if(s[0][i]!='-')
        {
            if(!fl) { bfs1(1,i); fl=true; }
            else bfs2(1,i);
        }
        if(s[2*h][i]!='-')
        {
            if(!fl) { bfs1(2*h-1,i); fl=true; }
            else bfs2(2*h-1,i);
        }
    }
    for(int i=1;i<2*h;i+=2)
    {
        if(s[i][0]!='|')
        {
            if(!fl) { bfs1(i,1); fl=true; }
            else bfs2(i,1);
        }
        if(s[i][2*w]!='|')
        {
            if(!fl) { bfs1(i,2*w-1); fl=true; }
            else bfs2(i,2*w-1);
        }
    }
    
    int sol=-1;
    for(int i=1;i<2*h;i+=2)
     for(int j=1;j<2*w;j+=2)
      sol=max(sol,min(lvl1[i][j],lvl2[i][j]));
    
    cout << sol << endl;
    
    return 0;
}
