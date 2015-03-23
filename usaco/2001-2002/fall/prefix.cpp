/*
  Source: usaco - 2001/2002 - fall
  Task: prefix
  KeyW: hashing
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define pb push_back

using namespace std;

const int base1 = 29;
const int base2 = 31;

const int MOD = 1000000007;

typedef long long LL;
struct el
{
    LL h1, h2;
    int ind;

    el() {}
    el(LL _h1, LL _h2, int _ind): h1(_h1), h2(_h2), ind(_ind) {}
};

int n, l, mxl;
char w[20010][128];
vector< el > v[128];

void read()
{
    scanf("%d\n",&n);
    for(int i = 0; i < n; i ++)
        scanf("%s",&w[i]);
}

bool cmp(el a, el b)
{
    if(a.h1 < b.h1) return true;
    if(a.h1 > b.h1) return false;
    if(a.h2 < b.h2) return true;
    if(a.h2 > b.h2) return false;
    return a.ind < b.ind;
}

void compute()
{
    for(int i = 0; i < n; i ++)
    {
        l = strlen(w[i]);
        if(l > mxl) mxl = l;

        LL t1 = 0, t2 = 0;
        LL p1 = 1, p2 = 1;

        for(int j = 0; j < l; j ++)
        {
            t1 = (t1 + p1 * (w[i][j] - 'a')) % MOD;
            t2 = (t2 + p2 * (w[i][j] - 'a')) % MOD;
            p1 *= base1; p2 *= base2;

            v[j].pb(el(t1, t2, i));
        }
    }

    for(int i = 0; i < mxl; i ++)
        sort(v[i].begin(), v[i].end(), cmp);
}

void solve()
{
    int solSz = -1, pos;

    for(int i = mxl - 1; i >= 0; i --)
    {
        for(int j = 0; j < v[i].size() - 1; j ++)
            if(v[i][j].h1 == v[i][j + 1].h1 && v[i][j].h2 == v[i][j + 1].h2)
            {
                solSz = i;
                pos = j;
                break;
            }
        if(solSz != -1) break;
    }

    for(int j = pos + 1; j < v[solSz].size() - 1; j ++)
        if(v[solSz][j].h1 == v[solSz][j + 1].h1 && v[solSz][j].h2 == v[solSz][j + 1].h2 && v[solSz][j].ind < v[solSz][pos].ind)
            pos = j;

    printf("%s\n%s\n",w[ v[solSz][pos].ind ],w[ v[solSz][pos + 1].ind ]);
}

int main()
{
    read();
    compute();
    solve();

    return 0;
}
