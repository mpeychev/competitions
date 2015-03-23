/*
  Source: coci - 2009/2008 - contest3
  Task: No 4 - razgovori
  KeyW: set
*/
#include <stdio.h>
#include <iostream>
#include <set>

#define p first
#define c second

using namespace std;

typedef pair<int,int> Detector;
typedef long long ll;

const int MAXN = (1<<17);

struct cmps
{
    bool operator()(Detector a,Detector b) { return a.p<b.p; }
};

int n,m;
Detector d[MAXN];
ll ans;
set< Detector , cmps > s;
set< Detector , cmps > :: iterator it;

bool cmpd(Detector a,Detector b) { return a.c<b.c; }

void init()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
        scanf("%d %d",&d[i].p,&d[i].c);
    sort(d,d+n,cmpd);
}

void solve()
{
    ans=d[0].c;
    s.insert(d[0]);
    for(int i=1;i<n;i++)
    {
        int cl,cr;
        it=s.lower_bound(d[i]);

        if(it!=s.end()) cr=(*it).c;
        else cr=0;

        if(it==s.begin()) cl=0;
        else
        {
            it--;
            cl=(*it).c;
        }

        ans+=d[i].c-max(cl,cr);
        s.insert(d[i]);
    }
    cout << ans << endl;
}

int main()
{
    init();
    solve();

    return 0;
}
