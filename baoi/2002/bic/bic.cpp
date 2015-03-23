/*
  Source: baoi-2002
  Task: Bicriterial routing
  KeyW: dijkstra + grapf expansion
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

#define pb push_back

using namespace std;

typedef struct
{
    int next;
    int c;
    int t;
} edge;
typedef struct
{
    int ver;
    int price;
    int time;
} vertex;

struct cmp
{
    bool operator()(vertex x,vertex y)
    {
        if(x.price<y.price) return false;
        if(x.price>y.price) return true;
        if(x.time<y.time) return false;
        return true;
    }
};

const int MAXN = 1<<7;

int n,m,s,e;
int a,b,c,d;

vertex tmp,go;
vector<edge> g[MAXN];
priority_queue< vertex , vector<vertex> , cmp > pq;

int mint[MAXN];
int sol;

edge makee(int _next,int _c,int _t)
{
    edge ret;
    ret.next=_next; ret.c=_c; ret.t=_t;
    return ret;
}

vertex makev(int _ver,int _price,int _time)
{
    vertex ret;
    ret.ver=_ver; ret.price=_price; ret.time=_time;
    return ret;
}

void init()
{
    scanf("%d %d %d %d",&n,&m,&s,&e);
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d %d",&a,&b,&c,&d);
        g[a].pb( makee(b,c,d) );
        g[b].pb( makee(a,c,d) );
    }
    for(int i=1;i<=n;i++) mint[i]=10010;
}

void dijkstra()
{
    pq.push(makev(s,0,0));
    while(!pq.empty())
    {
        tmp=pq.top(); pq.pop();

        if(mint[tmp.ver]<=tmp.time) continue;
        mint[tmp.ver]=tmp.time;
        if(tmp.ver==e) { sol++; continue; }

        for(int i=0;i<g[tmp.ver].size();i++)
        {
            go=makev(g[tmp.ver][i].next,tmp.price+g[tmp.ver][i].c,tmp.time+g[tmp.ver][i].t);
            if(mint[go.ver]>go.time) pq.push(go);
        }
    }
}

int main()
{
    init();
    dijkstra();
    printf("%d\n",sol);

    return 0;
}
