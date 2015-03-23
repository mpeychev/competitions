/*
  Source: coci - 2009/2010 - contest2
  Task: pasijans
  KeyW: pq ? - slow ?
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

const int MAXN = (1<<10);

int n,l,a;
deque<int> seq[MAXN];

bool lower(int ind1,int ind2)
{
    int sz1=seq[ind1].size();
    int sz2=seq[ind2].size();

    for(int i=0;i<min(sz1 , sz2);i++)
        if(seq[ind1][i]<seq[ind2][i]) return true;
        else if(seq[ind1][i]>seq[ind2][i]) return false;

    if(sz1<sz2) return false;
    return true;
}

struct cmp
{
    bool operator()(int a,int b)
    {
        return !lower(a,b);
    }
};

priority_queue< int , vector<int> , cmp > pq;

void read()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&l);
        for(int j=0;j<l;j++)
        {
            scanf("%d",&a);
            seq[i].push_back(a);
        }
    }
}

void solve()
{
    for(int i=0;i<n;i++) pq.push(i);

    int tmp;

    tmp=pq.top(); pq.pop();
    printf("%d",seq[tmp][0]); seq[tmp].pop_front();
    if(seq[tmp].size()) pq.push(tmp);

    while(!pq.empty())
    {
        tmp=pq.top(); pq.pop();
        printf(" %d",seq[tmp][0]); seq[tmp].pop_front();
        if(seq[tmp].size()) pq.push(tmp);
    }
    printf("\n");
}

int main()
{
    read();
    solve();

    return 0;
}
