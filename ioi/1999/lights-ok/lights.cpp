/*
PROG: traffic
LANG: C++
ID: mompej951
*/

/*
  Source: usaco - 2010/2011 - jan - silver
  Task: Traffic lights
  KewW: dijksrta
*/

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int , int> PII;

const int MAXN = 300 + 10;

int s,d;
int n,m;
int cInt[MAXN],r[MAXN],t[MAXN][2];
bool col[MAXN][256];

vector<PII> g[MAXN];

struct cmp
{
    bool operator()(PII a , PII b)
    {
        return !(a.second < b.second);
    }
};

bool used[MAXN];
priority_queue< PII , vector< PII > , cmp > pq;

void Paint(int ind)
{
    for(int i=0;i<r[ind];i++)
        col[ind][i] = cInt[ind];
    for(int i=r[ind];i<r[ind]+t[ind][cInt[ind] ^ 1];i++)
        col[ind][i] = cInt[ind] ^ 1;
    for(int i=r[ind]+t[ind][cInt[ind] ^ 1];i<t[ind][0] + t[ind][1];i++)
        col[ind][i] = cInt[ind];
}

void Init()
{
    scanf("%d %d",&s,&d);
    scanf("%d %d\n",&n,&m);
    for(int i=1;i<=n;i++)
    {
        char c;
        scanf("%c %d %d %d\n",&c,&r[i],&t[i][0],&t[i][1]);
        if(c == 'B') cInt[i] = 0;
        else cInt[i] = 1;
        Paint(i);
    }
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        g[a].pb(mp(b , c));
        g[b].pb(mp(a , c));
    }
}

int gcd(int a,int b)
{
    while(b)
    {
        int r = a%b;
        a=b; b=r;
    }
    return a;
}

int lca(int a,int b)
{
    return a*b/gcd(a,b);
}

int FindMinT(int x,int y,int tmp)
{
    if(tmp<t[x][0] + t[x][1] && tmp < t[y][0] + t[y][1])
    {
        if(col[x][tmp] == col[y][tmp]) return tmp;
    }
    for(int i=tmp;i<=tmp+lca(t[x][0] + t[x][1] , t[y][0] + t[y][1]);i++)
        if(col[x][i%(t[x][0] + t[x][1])] == col[y][i%(t[y][0] + t[y][1])])
            return i;
    return -1;
}

int Dijkstra()
{
    pq.push(mp(s , 0));
    while(!pq.empty())
    {
        PII at = pq.top();
        pq.pop();

        if(used[at.first]) continue;
        used[at.first] = 1;

        if(at.first == d) return at.second;

        for(int i=0;i<g[at.first].size();i++)
        {
            int from = at.first;
            int to = g[at.first][i].first;
            int strT = g[at.first][i].second;
            if(!used[to])
            {
                int nxtTime = FindMinT(to,from,at.second);
                if(nxtTime != -1)
                    pq.push(mp(to , nxtTime + strT));
            }
        }
    }
    return 0;
}

int main()
{
    freopen("traffic.in","r",stdin);
    freopen("traffic.out","w",stdout);

    Init();
    printf("%d\n",Dijkstra());

    return 0;
}
