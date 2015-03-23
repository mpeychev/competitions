#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 1 << 17;

int n;
int m[MAXN], pos[MAXN];
int t[2][MAXN];

void read() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &m[i]);
        pos[ m[i] ] = i;
    }
}

void update(int dir, int idx) {
    while(idx <= n) {
        t[dir][idx] ++;
        idx += (idx & -idx);
    }
}

int get(int dir, int idx) {
    int ret = 0;
    while(idx) {
        ret += t[dir][idx];
        idx -= (idx & -idx);
    }
    return ret;
}

int getLeft(int idx) {
    return get(0, n) - get(0, idx);
}

int getRight(int idx) {
    return get(1, idx);
}

void solve() {
    int n1 = 1, n2 = n;
    bool fl = 0;
    while(n1 <= n2)
    {
        int posNow;
        if(!fl)
        {
            posNow = pos[n1] + getLeft(pos[n1]) - getRight(pos[n1]);
            printf("%d\n", posNow - n1);
            update(0, pos[n1]);
            n1 ++;
        }
        else
        {
            posNow = pos[n2] + getLeft(pos[n2]) - getRight(pos[n2]);
            printf("%d\n", n2 - posNow);
            update(1, pos[n2]);
            n2 --;
        }

        fl ^= 1;
    }
}

int main()
{
    read();
    solve();

    return 0;
}
