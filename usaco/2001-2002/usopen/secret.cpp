#include <iostream>
#include <algorithm>
using namespace std;

struct edge
{
    int a,b; int c;
};

int w,p;
int prev[2048];
edge g[32768];

bool cmp(edge x,edge y)
{
    if(x.c<y.c) return true;
    return false;
}

int rt(int v)
{
    int root=v;
    while(prev[root]>0) root=prev[root];
    while(v!=root)
    {
        int tmp=v;
        v=prev[v];
        prev[tmp]=root;
    }
    return root;
}

int main()
{
    scanf("%d %d",&w,&p);
    for(int i=0;i<p;i++) scanf("%d %d %d",&g[i].a,&g[i].b,&g[i].c);
    sort(g,g+p,cmp);

    int cnt=0;
    int t[2048];
    for(int i=0;i<p && cnt<w-1;i++)
    {
        int x,y;
        x=g[i].a; y=g[i].b;
        int r1=rt(x);
        int r2=rt(y);
        if(r1!=r2) { t[cnt]=i; cnt++; prev[r2]=r1; }
    }

    long long sol=(long long)400000000;
    for(int i=0;i<w-1;i++)
    {
        memset(prev,0,sizeof(prev));
        cnt=0;
        long long tmp=0;
        for(int j=0;j<p && cnt<w-1 && tmp<sol;j++)
        {
            if(j==t[i]) continue;
            int x,y;
            x=g[j].a; y=g[j].b;
            int r1=rt(x);
            int r2=rt(y);
            if(r1!=r2) { cnt++; tmp+=g[j].c; prev[r2]=r1; }
        }
        if(sol>tmp) sol=tmp;
    }

    cout << sol << endl;

    return 0;
}
