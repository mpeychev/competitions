/*
  Source: ceoi-1999
  Task: Trip
  KeyW: dijkstra (N^2)
        complexity O(N^4)
*/
#include <stdio.h>

#define INF 50100
#define nopar -1

int n,m;
int g[128][128];
bool used[128];
int d[128],prev[128];

int len=INF,sol[128],sz;

void init()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        if(!g[x][y]) g[x][y]=g[y][x]=z;
        else if(g[x][y]>z) g[x][y]=g[y][x]=z;
    }
}

void way(int t)
{
    if(prev[t]==-1) return;
    way(prev[t]);
    sol[sz]=prev[t]; sz++;
}

void dijkstra(int v)
{
    for(int i=1;i<=n;i++)
    {
        used[i]=0;
        if(g[v][i]) { d[i]=g[v][i]; prev[i]=v; }
        else { d[i]=INF; prev[i]=nopar; }
    }
    used[v]=1;
    d[v]=0;
    while(1)
    {
        int tmpd=INF,j=nopar;
        for(int i=1;i<=n;i++) if(!used[i] && d[i]<tmpd) { tmpd=d[i]; j=i; }
        if(j==nopar) break;
        used[j]=1;
        for(int i=1;i<=n;i++)
         if(!used[i] && g[j][i] && d[i]>d[j]+g[j][i])
         {
                d[i]=d[j]+g[j][i];
                prev[i]=j;
         }
    }
}

void update(int cur,int v)
{
    int ttmp=g[cur][v];
    g[cur][v]=g[v][cur]=0;
    
    dijkstra(v);
    
    g[cur][v]=g[v][cur]=ttmp;
    if(d[cur]==INF) return;
    if(len>d[cur]+ttmp) { len=d[cur]+ttmp; sol[0]=cur; sz=1; way(cur); }
}

int main()
{
    init();
    
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      if(g[i][j])
       update(i,j);
    
    if(len==INF) { printf("No solution.\n"); return 0; }
    for(int i=0;i<sz-1;i++) printf("%d ",sol[i]);
    printf("%d\n",sol[sz-1]);

    return 0;
}
