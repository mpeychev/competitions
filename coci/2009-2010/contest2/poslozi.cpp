/*
  Source: coci - 2009/2008 - contest2
  Task: No 5 - poslozi
  KeyW: A* heuristics
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <queue>
#include <stack>

#define mp make_pair

using namespace std;

typedef vector<int> VI;
typedef pair<int,int> State;

const int MAXN = (1<<4);
const int MAXM = (1<<7);

struct cmp
{
    bool operator()(State v1,State v2)
    {
        return v1.first>v2.first;
    }
};

int N,M;
int F[MAXN],ind[MAXM][2];
VI perm,check;
State var;
int Lev;
map<int,int> lvl,prev;
priority_queue< State , vector<State> , cmp > pq;

int encode(VI p)
{
    int used[MAXN];
    memset(used,0,sizeof(used));
    int ret=0,mul;
    for(int i=0;i<N;i++)
    {
        mul=0;
        for(int j=1;j<p[i];j++)
            mul+=(!used[j]);
        used[p[i]]=1;
        ret+=mul*F[N-i-1];
    }
    return ret;
}

VI decode(int num)
{
    int used[MAXN];
    memset(used,0,sizeof(used));
    VI ret;
    ret.resize(N);
    int mul;
    for(int i=0;i<N;i++)
    {
        mul=num/F[N-i-1]+1;
        num%=F[N-i-1];
        for(int j=1;j<=N;j++)
            if(!used[j])
            {
                mul--;
                if(!mul) { ret[i]=j; used[j]=1; break; }
            }
    }
    return ret;
}

void init()
{
    scanf("%d %d",&N,&M);
    perm.resize(N);
    check.resize(N);
    for(int i=0;i<N;i++)
    {
        scanf("%d",&perm[i]);
        check[i]=perm[i];
    }
    for(int i=0;i<M;i++)
    {
        scanf("%d %d",&ind[i][0],&ind[i][1]);
        ind[i][0]--; ind[i][1]--;
    }
    F[0]=1;
    for(int i=1;i<N;i++) F[i]=F[i-1]*i;
}

int h(VI p)
{
    int ret=0;
    for(int i=0;i<N;i++)
        ret+=(p[i]!=i+1);
    return ret;
}

void write(int len)
{
    stack<int> ans;
    int go=0;
    while(prev[go]!=-1)
    {
        int add=prev[go];
        ans.push(add);
        perm=decode(go);
        swap(perm[ind[add][0]] , perm[ind[add][1]]);
        go=encode(perm);
    }
    if(ans.size()!=len) { printf("wa\n"); return; }
    while(!ans.empty())
    {
        printf("%d\n",ans.top()+1);
        swap(check[ind[ans.top()][0]] , check[ind[ans.top()][1]]);
        ans.pop();
    }
    if(encode(check)) { printf("wa\n"); return; }
    printf("ok\n");
}

void solve()
{
    int go=encode(perm);
    lvl[go]=1; prev[go]=-1;
    pq.push(mp(lvl[go]+h(perm) , go));
    while(!pq.empty())
    {
        var=pq.top();
        pq.pop();
        if(var.second==0)
        {
            printf("%d\n",var.first-1);
            write(var.first-1);
            break;
        }
        perm=decode(var.second);
        Lev=lvl[var.second];
        for(int i=0;i<M;i++)
        {
            swap(perm[ ind[i][0] ] , perm[ ind[i][1] ]);
            go=encode(perm);
            if(!lvl[go] || lvl[go]>Lev+1)
            {
                lvl[go]=Lev+1; prev[go]=i;
                pq.push(mp(lvl[go]+h(perm) , go));
            }
            swap(perm[ ind[i][0] ] , perm[ ind[i][1] ]);
        }
    }
}

int main()
{
    init();
    solve();

    return 0;
}
