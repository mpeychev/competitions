#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAXL = 200200;

struct el {
    int idx, val1, val2;

    el() {}
    el(int _idx, int _val1, int _val2): idx(_idx), val1(_val1), val2(_val2) {}
};

int l;
char s[MAXL];
int suffArr[MAXL][2], used[32], row;
el vec[MAXL];
int p[MAXL], inv[MAXL], ans;

void read() {
    scanf("%d\n", &l);
    gets(s);
}

bool cmp(el a, el b) {
    if(a.val1 < b.val1) return true;
    if(a.val1 > b.val1) return false;
    return a.val2 < b.val2;
}

void build() {
    int tmp = 0;
    memset(used, -1, sizeof(used));

    for(int i = 0; i < l; i ++)
        used[ s[i] - 'a' ] = 0;

    for(int i = 0; i < 26; i ++)
        if(used[i] != -1)
            used[i] = tmp ++;

    for(int i = 0; i < l; i ++)
        suffArr[i][row] = used[ s[i] - 'a' ];

    for(int k = 1; (1 << (k - 1)) <= l; k ++) {
        int len = (1 << (k - 1));

        for(int i = 0; i < l; i ++)
            if(i + len < l) vec[i] = el(i, suffArr[i][row], suffArr[i + len][row]);
            else vec[i] = el(i, suffArr[i][row], -1);

        sort(vec, vec + l, cmp);

        row ^= 1;

        tmp = 0;
        suffArr[ vec[0].idx ][row] = tmp;
        for(int i = 1; i < l; i ++) {
            if(vec[i].val1 != vec[i - 1].val1 || vec[i].val2 != vec[i - 1].val2) tmp ++;
            suffArr[ vec[i].idx ][row] = tmp;
        }
    }

    for(int i = 0; i < l; i ++)
        p[ suffArr[i][row] ] = i;
}

void solve() {
    for(int i = 0; i < l; i ++)
        inv[ p[i] ] = i;

    int h = 0;
    for(int i = 0; i < l; i ++) {
        int j = inv[i];
        if(j == l - 1) continue;
        while(s[ p[j] + h ] == s[ p[j + 1] + h ]) h ++;
        ans = max(ans, h);
        h --;
        if(h < 0) h = 0;
    }

    cout << ans << endl;
}

int main()
{
    read();
    build();
    solve();

    return 0;
}
