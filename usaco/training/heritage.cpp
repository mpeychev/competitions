/*
PROG: heritage
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

char in[32],pre[32];
int n,tree[32][2];

void init()
{
    scanf("%s",&in);
    scanf("%s",&pre);
    n=strlen(in);
    memset(tree,-1,sizeof(tree));
}

void build(int l1,int r1,int l2,int r2,int root)
{
    int nl=0,nr=0;
    for(int i=l1;i<=r1;i++)
    {
        if(in[i]-'A'==root) break;
        nl++;
    }
    nr=r1-l1-nl;
    
    if(nl)
    {
        tree[root][0]=pre[l2+1]-'A';
        build(l1,l1+nl-1,l2+1,l2+nl,tree[root][0]);
    }
    if(nr)
    {
        tree[root][1]=pre[l2+nl+1]-'A';
        build(l1+nl+1,r1,l2+nl+1,r2,tree[root][1]);
    }
}

void print(int root)
{
    if(tree[root][0]!=-1) print(tree[root][0]);
    if(tree[root][1]!=-1) print(tree[root][1]);
    printf("%c",root+'A');
}

int main()
{
    freopen("heritage.in","r",stdin);
    freopen("heritage.out","w",stdout);
    
    init();
    build(0,n-1,0,n-1,pre[0]-'A');
    print(pre[0]-'A');
    printf("\n");
    
    return 0;
}
