/*
PROG: lamps
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <string.h>
#include <string>
using namespace std;

int n,c,m[128];
vector<int> on,off;
set<string> sol;

void read()
{
     scanf("%d",&n);
     scanf("%d",&c);
     for( ; ; )
     {
          int x;
          scanf("%d",&x);
          if(x==-1) break;
          on.push_back(x);
     }
     for( ; ; )
     {
          int x;
          scanf("%d",&x);
          if(x==-1) break;
          off.push_back(x);
     }
}

void op(int k)
{
     if(k==1)
     {
             for(int i=1;i<=n;i++)
              if(m[i]==0) m[i]=1;
              else m[i]=0;
             return;
     }
     if(k==2)
     {
             for(int i=1;i<=n;i+=2)
              if(m[i]==0) m[i]=1;
              else m[i]=0;
             return;
     }
     if(k==3)
     {
             for(int i=2;i<=n;i+=2)
              if(m[i]==0) m[i]=1;
              else m[i]=0;
             return;
     }
     if(k==4)
     {
             for(int i=1;i<=n;i+=3)
              if(m[i]==0) m[i]=1;
              else m[i]=0;
             return;
     }
}

void check()
{
     for(int i=0;i<on.size();i++) if(m[ on[i] ] == 0) return;
     for(int i=0;i<off.size();i++) if(m[ off[i] ]) return;
     
     string tmp;
     for(int i=1;i<=n;i++) tmp.push_back(m[i]+'0');
     sol.insert(tmp);
}

void init()
{
     memset(m,1,sizeof(m));
}

int main()
{
    freopen("lamps.in","r",stdin);
    freopen("lamps.out","w",stdout);
    
    read();
    if(c%2==0) { init(); check(); }
    if(c%2 && c-1>=0) { init(); op(1); check(); }
    if(c%2 && c-1>=0) { init(); op(2); check(); }
    if(c%2 && c-1>=0) { init(); op(3); check(); }
    if(c%2 && c-1>=0) { init(); op(4); check(); }
    if(c%2==0 && c-2>=0) { init(); op(1); op(2); check(); }
    if(c%2==0 && c-2>=0) { init(); op(1); op(3); check(); }
    if(c%2==0 && c-2>=0) { init(); op(1); op(4); check(); }
    if(c%2==0 && c-2>=0) { init(); op(2); op(3); check(); }
    if(c%2==0 && c-2>=0) { init(); op(2); op(4); check(); }
    if(c%2==0 && c-2>=0) { init(); op(3); op(4); check(); }
    if(c%2 && c-3>=0) { init(); op(1); op(2); op(3); check(); }
    if(c%2 && c-3>=0) { init(); op(1); op(2); op(4); check(); }
    if(c%2 && c-3>=0) { init(); op(1); op(3); op(4); check(); }
    if(c%2 && c-3>=0) { init(); op(2); op(3); op(4); check(); }
    if(c%2==0 && c-4>=0) { init(); op(1); op(2); op(3); op(4); check(); }
    
    if(sol.size()==0) { printf("IMPOSSIBLE\n"); return 0; }
    
    set<string> ::iterator it;
    for(it=sol.begin();it!=sol.end();it++) cout << *it << endl;
    
    return 0;
}
