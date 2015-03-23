/*
PROG: msquare
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

#define pb push_back

using namespace std;

const int sz = 8;
typedef vector<int> vi;
typedef struct
{
    vi squ;
    string pos;
} state;

vi goal,k;
map< vi , bool > used;
state tmp,p;

void init()
{
    for(int i=0;i<sz;i++)
    {
        int x;
        scanf("%d",&x);
        goal.pb( x );
        k.pb( i+1 );
    }
}

void bfs()
{
    queue< state > q;
    used[ k ] = 1;
    tmp.squ=k;
    q.push(tmp);
    
    while(!q.empty())
    {
        tmp=q.front(); q.pop();
        if(tmp.squ==goal) { cout << tmp.pos.size() << endl << tmp.pos << endl; return; }
        
        // A
        p.squ.clear();
        for(int i=sz-1;i>=0;i--) p.squ.pb( tmp.squ[i] );
        p.pos=tmp.pos+'A';
        if(!used[p.squ]) { used[p.squ]=1; q.push(p); }
        // B
        p.squ.clear();
        p.squ.pb( tmp.squ[3] ); p.squ.pb( tmp.squ[0] ); p.squ.pb( tmp.squ[1] ); p.squ.pb( tmp.squ[2] );
        p.squ.pb( tmp.squ[5] ); p.squ.pb( tmp.squ[6] ); p.squ.pb( tmp.squ[7] ); p.squ.pb( tmp.squ[4] );
        p.pos=tmp.pos+'B';
        if(!used[p.squ]) { used[p.squ]=1; q.push(p); }
        // C
        p.squ.clear();
        p.squ.pb( tmp.squ[0] ); p.squ.pb( tmp.squ[6] ); p.squ.pb( tmp.squ[1] ); p.squ.pb( tmp.squ[3] );
        p.squ.pb( tmp.squ[4] ); p.squ.pb( tmp.squ[2] ); p.squ.pb( tmp.squ[5] ); p.squ.pb( tmp.squ[7] );
        p.pos=tmp.pos+'C';
        if(!used[p.squ]) { used[p.squ]=1; q.push(p); }
    }
}

int main()
{
    freopen("msquare.in","r",stdin);
    freopen("msquare.out","w",stdout);
    
    init();
    bfs();
    
    return 0;
}
