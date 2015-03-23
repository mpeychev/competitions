/*
PROG: milk3
LANG: C++
ID: mompej951
*/
#include <iostream>
using namespace std;

struct vertex
{
    int a,b,c;
} v;
int a,b,c;
bool can[32],used[262144];

int num(int x,int y,int z)
{
    return z+y*100+x*10000;
}

void dfs(vertex v)
{
    //cout << v.a << " " << v.b << " " << v.c << endl;
    
    used[num(v.a,v.b,v.c)]=1;
    
    if(v.a==0) can[v.c]=1;
    
    vertex s;
    if(v.a>0)
    {
        if(v.a+v.b<=b)
        {
            s.a=0; s.b=v.a+v.b; s.c=v.c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        else
        {
            s.a=v.a-(b-v.b); s.b=b; s.c=v.c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        
        if(v.a+v.c<=c)
        {
            s.a=0; s.b=v.b; s.c=v.a+v.c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        else
        {
            s.a=v.a-(c-v.c); s.b=v.b; s.c=c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
    }
    if(v.b>0)
    {
        if(v.b+v.a<=a)
        {
            s.a=v.a+v.b; s.b=0; s.c=v.c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        else
        {
            s.a=a; s.b=v.b-(a-v.a); s.c=v.c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        
        if(v.b+v.c<=c)
        {
            s.a=v.a; s.b=0; s.c=v.b+v.c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        else
        {
            s.a=v.a; s.b=v.b-(c-v.c); s.c=c;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
    }
    if(v.c>0)
    {
        if(v.c+v.a<=a)
        {
            s.a=v.a+v.c; s.b=v.b; s.c=0;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        else
        {
            s.a=a; s.b=v.b; s.c=v.c-(a-v.a);
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        
        if(v.c+v.b<=b)
        {
            s.a=v.a; s.b=v.c+v.b; s.c=0;
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
        else
        {
            s.a=v.a; s.b=b; s.c=v.c-(b-v.b);
            if(!used[num(s.a,s.b,s.c)]) dfs(s);
        }
    }
}

int main()
{
    freopen("milk3.in","r",stdin);
    freopen("milk3.out","w",stdout);
    
    scanf("%d %d %d",&a,&b,&c);
    v.a=0; v.b=0; v.c=c;
    
    dfs(v);
    
    int end;
    for(int i=20;i>=0;i--) if(can[i]) { end=i; break; }
    
    for(int i=0;i<end;i++) if(can[i]) cout << i << " ";
    cout << end << endl;
         
    return 0;
}
