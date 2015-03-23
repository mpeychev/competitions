#include <iostream>
#include <stdio.h>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 15;

FILE *in = fopen("mo.out", "r");

int n, x;
LL tree[MAXN];
int level[MAXN];

void init(int idx) {
    fscanf(in, "%d", &x);
    tree[idx] = x;
    if(2 * idx < (1 << n)) {
        level[2 * idx] = level[idx] + 1;
        level[2 * idx + 1] = level[idx] + 1;
        init(2 * idx);
        init(2 * idx + 1);
    }
}

inline int abs(int x) {
    if(x < 0) return -x;
    return x;
}

int main()
{
    cin >> n;
    level[1] = 0;
    init(1);

    for(int i = (1 << (n - 1)) - 1; i >= 1; i --) {
        if(abs(tree[2 * i] - tree[2 * i + 1]) != 1 << level[i]) {
            printf("wa\n");
            return 0;
        }
        tree[i] += tree[2 * i] + tree[2 * i + 1];
    }

    printf("ok\n");

    return 0;
}
