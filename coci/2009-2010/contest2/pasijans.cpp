/*
  Source: coci - 2009/2010 - contest 2
  Task: pasijans
  KeyW: hash + bs
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef unsigned long long ULL;

const ULL base1 = 100000007;
const ULL base2 = 100000037;

const int MAXN = (1<<10);
const int MAXL = (1<<10);

int n , mxl = -1;
int l[MAXN] , seq[MAXN][MAXL];
int lpos[MAXN];

ULL hash1[MAXN][MAXL] , hash2[MAXN][MAXL];
ULL deduce1[MAXN] , deduce2[MAXN];
ULL pow1[MAXL] , pow2[MAXL];

ULL get_hash1(int ind , int len) { return hash1[ind][lpos[ind] + len] - deduce1[ind]*pow1[len]; }
ULL get_hash2(int ind , int len) { return hash2[ind][lpos[ind] + len] - deduce2[ind]*pow2[len]; }

bool equal(int ind1 , int ind2 , int len)
{
    return (get_hash1(ind1 , len) == get_hash1(ind2 , len) &&
            get_hash2(ind1 , len) == get_hash2(ind2 , len));
}

struct cmp
{
    bool operator()(int ind1 , int ind2)
    {
        int l1 = l[ind1] - lpos[ind1];
        int l2 = l[ind2] - lpos[ind2];
        if(equal( ind1 , ind2 , min(l1,l2) )) return !(l1>l2);

        int le = 0 , ri = min(l1,l2) , mid;
        while(le<ri)
        {
            mid = (le + ri + 1)/2;
            if(equal( ind1 , ind2 , mid )) le = mid;
            else ri = mid - 1;
        }

        return !(seq[ind1][lpos[ind1] + le + 1] < seq[ind2][lpos[ind2] + le + 1]);
    }
};

priority_queue< int , vector<int> , cmp > pq;

void init()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&l[i]);
        if(mxl<l[i]) mxl=l[i];
        for(int j=1;j<=l[i];j++)
            scanf("%d",&seq[i][j]);
    }

    pow1[0]=1; pow2[0]=1;
    for(int i=1;i<=mxl;i++)
    {
        pow1[i]=pow1[i-1]*base1;
        pow2[i]=pow2[i-1]*base2;
    }

    for(int i=0;i<n;i++)
        for(int j=1;j<=l[i];j++)
        {
            hash1[i][j] = hash1[i][j-1]*base1 + seq[i][j];
            hash2[i][j] = hash2[i][j-1]*base2 + seq[i][j];
        }
}

void take(int get)
{
    deduce1[get] = deduce1[get]*base1 + seq[get][lpos[get]];
    deduce2[get] = deduce2[get]*base2 + seq[get][lpos[get]];
}

void solve()
{
    for(int i=0;i<n;i++)
        pq.push(i);

    int get;

    get = pq.top();
    pq.pop();

    lpos[get] ++;
    printf("%d",seq[get][lpos[get]]);
    take(get);

    if(lpos[get]!=l[get]) pq.push(get);

    while(!pq.empty())
    {
        get = pq.top();
        pq.pop();

        lpos[get] ++;
        printf(" %d",seq[get][lpos[get]]);
        take(get);

        if(lpos[get]!=l[get]) pq.push(get);
    }

    printf("\n");
}

int main()
{
    init();
    solve();

    return 0;
}
