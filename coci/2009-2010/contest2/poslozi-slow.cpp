/*
  Source: coci - 2009/2008 - contest2
  Task: No 5 - poslozi
  KeyW: Bidirectial BFS
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

typedef vector<int> VI;

int N,M,cur;
VI seq,target,tmp;
int swaps[128][2];
map< VI , int > lvlb,lvle;
map< VI , int > prevb,preve;
queue< VI > qb,qe;

void init()
{
    scanf("%d %d",&N,&M);
    seq.resize(N);
    target.resize(N);
    for(int i=0;i<N;i++)
    {
        scanf("%d",&seq[i]);
        target[i]=i+1;
    }
    for(int i=0;i<M;i++)
    {
        scanf("%d %d",&swaps[i][0],&swaps[i][1]);
        swaps[i][0]--; swaps[i][1]--;
    }
}

void print1(VI tmp)
{
    if(tmp==seq) return;
    int out=prevb[tmp];
    swap(tmp[swaps[out][0]],tmp[swaps[out][1]]);
    print1(tmp);
    printf("%d\n",out+1);
}

void print2(VI tmp)
{
    while(tmp!=target)
    {
        int out=preve[tmp];
        swap(tmp[swaps[out][0]],tmp[swaps[out][1]]);
        printf("%d\n",out+1);
    }
}

void BBFS()
{
    lvlb[seq]=1;
    qb.push(seq);
    lvle[target]=1;
    qe.push(target);

    while(1)
    {
        tmp=qb.front();
        qb.pop();
        if(lvle[tmp])
        {
            printf("%d\n",lvlb[tmp]+lvle[tmp]-2);
            print1(tmp);
            print2(tmp);
            break;
        }

        cur=lvlb[tmp];
        for(int i=0;i<M;i++)
        {
            swap(tmp[swaps[i][0]],tmp[swaps[i][1]]);
            if(!lvlb[tmp])
            {
                lvlb[tmp]=cur+1;
                prevb[tmp]=i;
                qb.push(tmp);
            }
            swap(tmp[swaps[i][0]],tmp[swaps[i][1]]);
        }

        tmp=qe.front();
        qe.pop();
        if(lvlb[tmp])
        {
            printf("%d\n",lvlb[tmp]+lvle[tmp]-2);
            print1(tmp);
            print2(tmp);
            break;
        }

        cur=lvle[tmp];
        for(int i=0;i<M;i++)
        {
            swap(tmp[swaps[i][0]],tmp[swaps[i][1]]);
            if(!lvle[tmp])
            {
                lvle[tmp]=cur+1;
                preve[tmp]=i;
                qe.push(tmp);
            }
            swap(tmp[swaps[i][0]],tmp[swaps[i][1]]);
        }
    }
}

int main()
{
    init();
    BBFS();

    return 0;
}
