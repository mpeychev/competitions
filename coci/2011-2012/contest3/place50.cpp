#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

struct chain
{
    vector<int> nodes;
    vector<int> tree;
    
    void update(int idx, int val)
    {
        while(idx < tree.size())
        {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }
    
    int sum(int idx)
    {
        int ret = 0;
        while(idx)
        {
            ret += tree[idx];
            idx -= (idx & -idx);
        }
        return ret;
    }
};

int n, m;
vector<int> g[500500];
int w[500500], prev[500500];
vector< chain > vec;
PII p[500500];

void read()
{
    scanf("%d %d", &n, &m);
    
    prev[1] = -1;
    scanf("%d", &w[1]);
    for(int i = 2; i <= n; i ++)
    {
        scanf("%d %d", &w[i], &prev[i]);
        g[prev[i]].pb(i);
    }
}

void dfs(int cur)
{
    vector<int> l;
    
    l.pb(cur);
    
    while(g[cur].size() == 1)
    {
        cur = g[cur][0];
        l.pb(cur);
    }
    
    chain tmp;
    tmp.nodes = l;
    vec.pb(tmp);
    
    for(int i = 0; i < g[cur].size(); i ++)
        dfs(g[cur][i]);
}

void init()
{
    dfs(1);
    
    for(int i = 0; i < vec.size(); i ++)
    {
        for(int j = 0; j < vec[i].nodes.size(); j ++)
            p[ vec[i].nodes[j] ] = mp(i, j + 1);
        vec[i].tree.resize( vec[i].nodes.size() + 1 );
    }
}

int query(int cur)
{
    int ret = w[cur];
    cur = prev[cur];
    for( ; ; )
    {
        if(cur == -1)
            break;
        
        int ch = p[cur].first;
        ret += vec[ch].sum(p[cur].second);
        
        cur = vec[ch].nodes[0];
        cur = prev[cur];
    }
    return ret;
}

void modify(int cur, int val)
{
    vec[ p[cur].first ].update(p[cur].second, val);
}

void solve()
{
    scanf("\n");
    
    char cmd;
    int a, x;
    
    for(int i = 0; i < m; i ++)
    {
        scanf("%c", &cmd);
        if(cmd == 'p')
        {
            scanf("%d %d\n", &a, &x);
            modify(a, x);
        }
        else
        {
            scanf("%d\n", &a);
            printf("%d\n", query(a));
        }
    }
}

int main()
{
    read();
    init();
    solve();
    
    return 0;
}
