#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int N,C,seq[1024];
map<int,int> freq,first;

bool cmp(int a,int b)
{
    if(freq[a]>freq[b]) return true;
    if(freq[a]<freq[b]) return false;
    if(first[a]<first[b]) return true;
    return false;
}

int main()
{
    scanf("%d %d",&N,&C);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&seq[i]);
        freq[seq[i]]++;
        if(!first[seq[i]]) first[seq[i]]=i;
    }
    sort(seq+1,seq+N+1,cmp);
    for(int i=1;i<N;i++) printf("%d ",seq[i]);
    printf("%d\n",seq[N]);

    return 0;
}
