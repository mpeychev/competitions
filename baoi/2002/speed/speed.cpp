/*
  Source: baoi - 2002
  Task: speed
  KeyW: dijkstra
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

#define pb push_back
#define mp make_pair
#define vertex first
#define speed second

using namespace std;

const int MAXN = 150 + 10;
const int MAXV = 500 + 12;

typedef pair<int,int> pii;

typedef struct
{
    int b;
    int v,l;
} edge;

typedef struct
{
    int prev_vertex;
    int prev_speed;
    int ver,v;
    double t;
} state;

struct cmp
{
    bool operator()(state x,state y)
    {
        return !(x.t<y.t);
    }
};

int n,m,d;
vector<edge> g[MAXN];
pii prev[MAXN][MAXV];
double curt[MAXN][MAXV];
int max_speed[MAXN];
priority_queue< state , vector<state> , cmp> pq;

inline state make(int _prev_vertex,int _prev_speed,int _ver,int _v,double _t)
{
    state ret;
    ret.prev_vertex=_prev_vertex;
    ret.prev_speed=_prev_speed;
    ret.ver=_ver; ret.v=_v; ret.t=_t;
    return ret;
}

void init()
{
    scanf("%d %d %d",&n,&m,&d);
    for(int i=0;i<m;i++)
    {
        int a;
        edge temp;
        scanf("%d %d %d %d",&a,&temp.b,&temp.v,&temp.l);
        g[a].pb(temp);
    }
}

inline int f(int a,int b)
{
    if(!a) return b;
    return a;
}

pii dijkstra()
{
    for(int i=0;i<n;i++)
     for(int j=0;j<MAXV;j++)
      curt[i][j]=1e9;

    pq.push( make(-1,-1,0,70,0) );

    while(!pq.empty())
    {
        state tmp;
        tmp=pq.top(); pq.pop();

        if(max_speed[tmp.ver]>=tmp.v) continue;
        max_speed[tmp.ver]=tmp.v;
        if(curt[tmp.ver][tmp.v]>tmp.t)
        {
            curt[tmp.ver][tmp.v]=tmp.t;
            prev[tmp.ver][tmp.v]=mp(tmp.prev_vertex,tmp.prev_speed);
        }
        if(tmp.ver==d) return mp(tmp.ver,tmp.v);

        for(int i=0;i<g[tmp.ver].size();i++)
         if(max_speed[g[tmp.ver][i].b]<f(g[tmp.ver][i].v,tmp.v))
         {
             if(g[tmp.ver][i].v) pq.push( make(tmp.ver , tmp.v , g[tmp.ver][i].b , g[tmp.ver][i].v , tmp.t+(double)g[tmp.ver][i].l/(double)g[tmp.ver][i].v) );
             else pq.push( make(tmp.ver , tmp.v , g[tmp.ver][i].b , tmp.v , tmp.t+(double)g[tmp.ver][i].l/(double)tmp.v) );
         }
    }
}

void print(pii cur)
{
    if(cur.vertex==0) { printf("0"); return; }
    print(prev[cur.vertex][cur.speed]);
    printf(" %d",cur.vertex);
}

int main()
{
    init();
    memset(max_speed,-1,sizeof(max_speed));
    print( dijkstra() );
    printf("\n");

    return 0;
}
