#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

const int n = 9;
const int INF = 1 << 10;

struct triple {
    int a, b, c;

    triple() {}
    triple(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
};

char s[16][16];
int ma3x[16];
vector<int> m;
vector<triple> tr;
int c[4][1 << n];
int diff[16][1 << n];

void read() {
    for(int i = 0; i < n; i ++)
        scanf("%s", &s[i]);
}

bool check(int ma1, int ma2, int ma3) {
    int num;
    num = (ma1 & 7) + ((ma2 & 7) << 3) + ((ma3 & 7) << 6);
    if(__builtin_popcount(num) & 1) return false;
    num = (ma1 & 56) + ((ma2 & 56) << 3) + ((ma3 & 56) << 6);
    return !(__builtin_popcount(num) & 1);
}

void init() {
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            if(s[i][j] == '1')
                ma3x[i] += 1 << (n - j - 1);

    for(int i = 0; i < (1 << n); i ++)
        if(!(__builtin_popcount(i) & 1))
            m.pb(i);

    for(int i = 0; i < m.size(); i ++)
        for(int j = 0; j < m.size(); j ++)
            for(int k = 0; k < m.size(); k ++)
                if(check(m[i], m[j], m[k]))
                    tr.pb(triple(m[i], m[j], m[k]));

    for(int i = 0; i < 4; i ++)
        for(int j = 0; j < (1 << n); j ++)
            c[i][j] = INF;

    for(int i = 0; i < n; i ++)
        for(int j = 0; j < (1 << n); j ++)
            diff[i][j] = __builtin_popcount(ma3x[i] ^ j);
}

void calc(int r) {
    for(int i = 0; i < tr.size(); i ++) {
        int cost = 0;
        cost += diff[r][ tr[i].a ];
        cost += diff[r + 1][ tr[i].b ];
        cost += diff[r + 2][ tr[i].c ];
        c[r / 3][ tr[i].a ^ tr[i].b ^ tr[i].c ] = min(c[r / 3][ tr[i].a ^ tr[i].b ^ tr[i].c ], cost);
    }
}

void solve() {
    for(int i = 0; i < n; i += 3)
        calc(i);

    int ans = INF;

    for(int i = 0; i < (1 << n); i ++)
        for(int j = 0; j < (1 << n); j ++) {
            int k = i ^ j;
            ans = min(ans, c[0][i] + c[1][j] + c[2][k]);
        }

    cout << ans << endl;
}

int main()
{
    read();
    init();
    solve();

    return 0;
}
