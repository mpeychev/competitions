/*
PROG: milk2
LANG: C++
ID: mompej951
*/
#include <fstream>
#include <algorithm>
#include <vector>

#define start first
#define end second 

using namespace std;

FILE *in=fopen("milk2.in","r");
FILE *out=fopen("milk2.out","w");

int n;
vector<pair<int,int> > v;
pair<int,int> p;

bool cmp(pair<int,int>a,pair<int,int>b)
{
     if(a.start<b.start) return true;
     return false;
}

int main()
{
    fscanf(in,"%d",&n);
    for(int i=0;i<n;i++)
    {
            fscanf(in,"%d %d",&p.start,&p.end);
            v.push_back(p);
    }
    
    sort(v.begin(),v.begin()+n,cmp);
    
    int a=v[0].start,b=v[0].end,sol=v[0].end-v[0].start,res=0;
    
    while(v.size())
    {
                   if(b>=v[0].end) { v.erase(v.begin(),v.begin()+1); continue; }
                   if(b>=v[0].start) { b=v[0].end; v.erase(v.begin(),v.begin()+1); continue; }
                   if(v[0].start-b>res) res=v[0].start-b;
                   if(b-a>sol) sol=b-a;
                   a=v[0].start; b=v[0].end;
                   v.erase(v.begin(),v.begin()+1);
    }
    
    fprintf(out,"%d %d\n",sol,res);

    return 0;
}
