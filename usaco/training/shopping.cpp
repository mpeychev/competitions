/*
PROG: shopping
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define pb push_back
#define num first
#define code second

using namespace std;

typedef pair<int,int> pii;
typedef struct
{
    int n;
    pii item[8];
    int price;
} offer;

const int maxp = 9999000;

int s;
offer m[128];

int b;
vector<int> c,k,p;
map< vector<int> , int > dp;

void read()
{
    scanf("%d",&s);
    for(int i=0;i<s;i++)
    {
        scanf("%d",&m[i].n);
        for(int j=0;j<m[i].n;j++) scanf("%d %d",&m[i].item[j].code,&m[i].item[j].num);
        scanf("%d",&m[i].price);
    }
    scanf("%d",&b);
    for(int i=0;i<b;i++)
    {
        int tc,tk,tp;
        scanf("%d %d %d",&tc,&tk,&tp);
        c.pb(tc); k.pb(tk); p.pb(tp);
    }
}

int f(vector<int> pos)
{
    if(dp[pos]) return dp[pos];
    
    bool zero_only=true;
    for(int i=0;i<pos.size();i++) if(pos[i]) { zero_only=false; break; }
    
    if(zero_only) return 0;

    vector<int> next;

    int ret = maxp;
    for(int i=0;i<pos.size();i++)
    {
        if(!pos[i]) continue;
        next=pos;
        next[i]=0;
        int temp=pos[i]*p[i]+f(next);

        if(ret>temp) ret=temp;
    }

    for(int i=0;i<s;i++)
    {
        bool ok=true;
        next=pos;
        for(int j=0;j<m[i].n;j++)
        {
            bool fl=false;
            for(int ii=0;ii<b;ii++)
             if(m[i].item[j].code==c[ii] && m[i].item[j].num<=next[ii])
             {
                 next[ii]-=m[i].item[j].num;
                 fl=true;
                 break;
             }
            if(!fl) { ok=false; break; }
        }
        if(!ok) continue;

        int temp=m[i].price+f(next);
        if(ret>temp) ret=temp;
    }

    dp[pos]=ret;
    return ret;
}

int main()
{
    freopen("shopping.in","r",stdin);
    freopen("shopping.out","w",stdout);

    read();
    
    printf("%d\n",f(k));

    return 0;
}
