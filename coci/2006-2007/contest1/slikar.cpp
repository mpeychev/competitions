#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define pb push_back
#define mp make_pair
using namespace std;

struct pos
{
    int x,y;
};

int n,m;
char s[64][64];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
pos S,D;
int level[64][64];
int mx=1;

void read()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",&s[i]);
    
    for(int i=0;i<n;i++)
     for(int j=0;j<m;j++)
     {
            if(s[i][j]=='S') { S.x=i; S.y=j; }
            if(s[i][j]=='D') { D.x=i; D.y=j; }
     }
    
}

bool in(int g,int h)
{
    if(g<0 || h<0 || g>=n || g>=m) return false;
    return true;
}

bool neigh(int g,int h)
{
    for(int i=0;i<4;i++)
     if(in(g+dx[i],h+dy[i]) && s[ g+dx[i] ][ h+dy[i] ]=='*') return true;
    return false;
}

void flood()
{
    vector< pair<int,int> > tmp;
    for(int i=0;i<n;i++)
     for(int j=0;j<m;j++)
      if(s[i][j]=='.' && neigh(i,j))
       tmp.pb( mp(i,j) );
    for(int i=0;i<tmp.size();i++) s[tmp[i].first][tmp[i].second]='*';
}

void bfs(pos v)
{
    queue<pos> q;
    
    level[v.x][v.y]=1;
    q.push(v);
    
    while(!q.empty())
    {
        v=q.front(); q.pop();
        if(level[v.x][v.y]+1>mx) { mx=level[v.x][v.y]+1; flood(); }
        for(int i=0;i<4;i++)
         if(in(v.x+dx[i],v.y+dy[i]) &&
            !level[v.x+dx[i]][v.y+dy[i]] &&
            (s[v.x+dx[i]][v.y+dy[i]]=='.' || s[v.x+dx[i]][v.y+dy[i]]=='D'))
         {
                pos ins;
                ins.x=v.x+dx[i];
                ins.y=v.y+dy[i];
                level[ins.x][ins.y]=level[v.x][v.y]+1;
                q.push(ins);
         }
    }
}

void print()
{
    if(level[D.x][D.y]) printf("%d\n",level[D.x][D.y]-1);
    else printf("KAKTUS\n");
}

int main()
{
    read();
    bfs(S);
    print();
    
    return 0;
}
