#include <iostream>
#include <stdio.h>
#include <fstream>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 19;

int n, m;
PII l[MAXN];
int vec[MAXN];

void init() {
    scanf("%d %d\n", &n, &m);

    l[0].second = 1;
    l[n + 1].first = n;
    for(int i = 1; i <= n; i ++)
        l[i] = mp(i - 1, i + 1);
}

void removeNode(int x) {
    int a = l[x].first;
    int b = l[x].second;
    l[a].second = b;
    l[b].first = a;
}

void addXAfterY(int x, int y) {
    l[x] = mp(y, l[y].second);
    l[ l[x].first ].second = x;
    l[ l[x].second ].first = x;
}

void read() {
    char cmd;
    int x, y;

    for(int i = 0; i < m; i ++) {
        scanf("%c %d %d\n", &cmd, &x, &y);

///        A) Move node X in front of node Y.
///        B) Move node X after node Y.

        if(cmd == 'A' && l[y].first == x) continue;
        if(cmd == 'B' && l[y].second == x) continue;

        removeNode(x);

        if(cmd == 'A') addXAfterY(x, l[y].first);
        else addXAfterY(x, y);
    }
}

void check() {
    int idx = 1;
    int cur = 0;
    while(l[cur].second != n + 1) {
        vec[idx ++] = l[cur].second;
        cur = l[cur].second;
    }

    for(int i = 1; i <= n; i ++)
        if(vec[i] != i) {
            printf("wa\n");
            return;
        }

    printf("ok\n");
}

int main()
{
    init();

    read();
    scanf("%d\n", &m);
    read();

    check();

    return 0;
}
