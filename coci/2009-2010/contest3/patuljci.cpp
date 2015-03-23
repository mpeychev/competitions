/*
  Source: coci - 2009/2010 - contest 3
  Task: 5 - patuljci
  KeyW: interval tree + bs
*/
#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int , int> Node;

const int MAXN = (1 << 19);
const int MAXC = 10010;

int n, c;
Node tree[2 * MAXN];
int leaves;
vector<int> pos[MAXC];
int m;

Node combine(Node le, Node ri)
{
    if(le.first == ri.first) return mp(le.first, le.second + ri.second);
    else if(le.second > ri.second) return mp(le.first, le.second - ri.second);
    else if(le.second == ri.second) return mp(0, 0);
    else return mp(ri.first, ri.second - le.second);
}

void update(int ind, int var)
{
    tree[ind] = mp(var, 1);
    ind >>= 1;
    while(ind)
    {
        tree[ind] = combine(tree[2 * ind], tree[2 * ind + 1]);
        ind >>= 1;
    }
}

Node query(int ind, int le, int ri, int a, int b)
{
    //cout << ind << " " << le << " " << ri << " " << a << " " << b << endl;
    if(ri < a || b < le) return mp(0, 0);
    if(a <= le && ri <= b) return tree[ind];

    Node lnode = query(2 * ind, le, (le + ri)/2, a, b);
    Node rnode = query(2 * ind + 1, (le + ri)/2 + 1, ri, a, b);

    return combine(lnode, rnode);
}

int ubound(int ind, int key)
{
    int l = 0, r = pos[ind].size() - 1, mid;
    while(l < r)
    {
        mid = (l + r + 1) / 2;
        if(pos[ind][mid] > key) r = mid - 1;
        else l = mid;
    }
    if(pos[ind][l] <= key) return l;
    return -1;
}

int lbound(int ind, int key)
{
    int l = 0, r = pos[ind].size() - 1, mid;
    while(l < r)
    {
        mid = (l + r) / 2;
        if(pos[ind][mid] < key) l = mid + 1;
        else r = mid;
    }
    if(pos[ind][l] >= key) return l;
    return -1;
}

void check(int col, int a, int b)
{
    //cout << col << " " << a << " " << b << endl;
    if(pos[col].size() == 0)
    {
        printf("no\n");
        return;
    }

    int down = lbound(col, a);
    int up = ubound(col, b);

    if(down == -1 || up == -1)
    {
        printf("no\n");
        return;
    }
    if(up - down + 1 > (b - a + 1) / 2) printf("yes %d\n",col);
    else printf("no\n");
}

void init()
{
    scanf("%d %d",&n,&c);

    leaves = 2;
    while(leaves < n) leaves <<= 1;

    for(int i = 1; i < 2 * leaves; i ++)
        tree[i] = mp(0 , 0);

    for(int i = 0; i < n; i ++)
    {
        int col;
        scanf("%d",&col);
        pos[col].pb(i);
        update(i + leaves, col);
    }

    //for(int i = 1; i < leaves * 2; i ++)
    //    cout << i << " " << tree[i].first << " " << tree[i].second << endl;
}

void solve()
{
    scanf("%d",&m);
    for(int i = 0; i < m; i ++)
    {
        int a, b;
        scanf("%d %d",&a,&b);
        a --; b --;
        check(query(1, 0, leaves - 1, a, b).first, a, b);
    }
}

int main()
{
    init();
    solve();

    return 0;
}
