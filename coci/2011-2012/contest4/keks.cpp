#include <stdio.h>
#include <iostream>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

int n, k;
char s[500500];
PII t[1 << 20];
int lvs;

void read() {
    scanf("%d %d\n", &n, &k);
    scanf("%s", &s);
}

PII merge(PII a, PII b) {
    if(a.first >= b.first)
        return a;
    return b;
}

void update(int idx, PII val) {
    t[idx] = val;
    while(idx) {
        idx >>= 1;
        t[idx] = merge(t[idx << 1], t[(idx << 1) + 1]);
    }
}

PII query(int idx, int le, int ri, int a, int b) {
    if(ri < a || b < le)
        return mp(-1, -1);

    if(a <= le && ri <= b)
        return t[idx];

    int mid = (le + ri) >> 1;
    PII left = query(idx << 1, le, mid, a, b);
    PII right = query((idx << 1) + 1, mid + 1, ri, a, b);

    return merge(left, right);
}

void solve() {
    if(n == 1) {
        printf("%s\n", s);
        return;
    }

    lvs = 1;
    while(lvs < n) lvs <<= 1;

    for(int i = 0; i < lvs; i ++)
        t[i + lvs] = mp(-1, -1);

    for(int i = 0; i < lvs; i ++)
        update(i + lvs, mp(s[i] - '0', i));

    int pos = 0;
    int last = n - k;
    for(int i = 0; i < last; i ++) {
        PII q = query(1, 0, lvs - 1, pos, pos + k);
        printf("%d", q.first);
        k -= (q.second - pos);
        pos = q.second + 1;
    }

    printf("\n");
}

int main()
{
    read();
    solve();

    return 0;
}
