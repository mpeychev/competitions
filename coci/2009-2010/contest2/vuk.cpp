#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define mp make_pair

using namespace std;

typedef pair<int,int> PII;
typedef pair< PII , int > State;

const int MAXN = (1<<9);
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

int N,M;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int ans[MAXN][MAXN];

struct cmp
{
    bool operator()(State v1,State v2)
    {
        return !(v1.second>v2.second);
    }
};

void precalc()
{
    queue<PII> q;

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            if(grid[i][j]=='+')
            {
                dist[i][j]=1;
                q.push( mp(i,j) );
            }

    while(!q.empty())
    {
        PII pos=q.front();
        q.pop();

        for(int i=0;i<4;i++)
            if(pos.first+dx[i]>=0 && pos.first+dx[i]<N &&
               pos.second+dy[i]>=0 && pos.second+dy[i]<M &&
               !dist[pos.first+dx[i]][pos.second+dy[i]])
            {
                dist[pos.first+dx[i]][pos.second+dy[i]]=dist[pos.first][pos.second]+1;
                q.push( mp(pos.first+dx[i],pos.second+dy[i]) );
            }
    }
}

void init()
{
    scanf("%d %d",&N,&M);
    for(int i=0;i<N;i++)
        scanf("%s",&grid[i]);
    precalc();
}

void solve()
{
    priority_queue< State , vector<State> , cmp > pq;

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            if(grid[i][j]=='V')
                pq.push( mp( mp(i,j) , dist[i][j] ) );

    while(!pq.empty())
    {
        State pos=pq.top();
        pq.pop();

        if(grid[pos.first.first][pos.first.second]=='J') { printf("%d\n",pos.second-1); return; }
        if(ans[pos.first.first][pos.first.second]) continue;
        ans[pos.first.first][pos.first.second]=pos.second;

        for(int i=0;i<4;i++)
            if(pos.first.first+dx[i]>=0 && pos.first.first+dx[i]<N &&
               pos.first.second+dy[i]>=0 && pos.first.second+dy[i]<M &&
               !ans[pos.first.first+dx[i]][pos.first.second+dy[i]])
                    pq.push( mp( mp(pos.first.first+dx[i],pos.first.second+dy[i]) ,
                                 min(pos.second,dist[pos.first.first+dx[i]][pos.first.second+dy[i]]) ) );
    }
}

int main()
{
    init();
    solve();

    return 0;
}
