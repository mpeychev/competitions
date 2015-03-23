/*
PROG: sort3
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

struct pos
{
       int have_to_be;
       int now_is;
};

int n;
pos m[1024];
int cnt[4];

int main()
{
    freopen("sort3.in","r",stdin);
    freopen("sort3.out","w",stdout);
    
    scanf("%d",&n);
    for(int i=0;i<n;i++) { scanf("%d",&m[i].now_is); cnt[ m[i].now_is ] ++; }
    for(int i=0;i<cnt[1];i++) m[i].have_to_be=1;
    for(int i=cnt[1];i<cnt[1]+cnt[2];i++) m[i].have_to_be=2;
    for(int i=cnt[1]+cnt[2];i<n;i++) m[i].have_to_be=3;
    
    int br=0;
    for(int i=0;i<n-cnt[3];i++)
    {
            if(m[i].now_is==m[i].have_to_be) continue;
            if(m[i].have_to_be==1)
            {
                                  int pos2=-1,pos3=-1;
                                  for(int j=i+1;j<n;j++)
                                  {
                                          if(m[j].now_is==1 && m[j].have_to_be==2) pos2=j;
                                          if(m[j].now_is==1 && m[j].have_to_be==3) pos3=j;
                                  }
                                  if(m[i].now_is==2 && pos2!=-1) { br++; swap(m[i].now_is,m[pos2].now_is); continue; }
                                  if(m[i].now_is==3 && pos3!=-1) { br++; swap(m[i].now_is,m[pos3].now_is); continue; }
                                  if(pos2!=-1) { br++; swap(m[i].now_is,m[pos2].now_is); continue; }
                                  if(pos3!=-1) { br++; swap(m[i].now_is,m[pos3].now_is); continue; }
            }
            else
            {
                int pos3=-1;
                for(int j=i+1;j<n;j++) if(m[j].now_is==2 && m[j].have_to_be==3) { pos3=j; break; }
                br++; swap(m[i].now_is,m[pos3].now_is);
            }
    }
    
    printf("%d\n",br);
    
    return 0;
}
