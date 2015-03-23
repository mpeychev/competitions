#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

int n;
char s[1 << 15][1 << 5];
int l[1 << 15];
int m[1 << 15];
int last;
vector<int> ans;

void read() {
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%s", &s[i]);
        l[i] = strlen(s[i]);
    }
}

int lcp(int idx) {
    for(int i = 0; i < l[idx]; i ++)
        if(s[idx][i] != s[last][i])
            return i;

    return l[idx];
}

bool cmp(int a, int b) {
    if(a == last) return false;
    if(b == last) return true;

    int d1 = lcp(a), d2 = lcp(b);

    if(d1 && !d2) return false;
    if(!d1 && d2) return true;

    if(d1 && d2) {
        if(d1 < d2) return true;
        if(d1 > d2) return false;
        return strcmp(s[a], s[b]) <= 0;
    }

    return strcmp(s[a], s[b]) <= 0;
}

int lcp2(int a, int b) {
    for(int i = 0, j = 0; i < l[a] && j < l[b]; i ++, j ++)
        if(s[a][i] != s[b][j])
            return i;
    return min(l[a], l[b]);
}

void solve() {
    last = 0;
    for(int i = 1; i < n; i ++)
        if(l[i] > l[last])
            last = i;

    for(int i = 0; i < n; i ++)
        m[i] = i;

    sort(m, m + n, cmp);

    for(int i = 0; i < l[ m[0] ]; i ++)
        ans.pb(s[ m[0] ][i]);
    ans.pb('P');

    for(int i = 1; i < n; i ++) {
        int com = lcp2(m[i], m[i - 1]);
        for(int j = com; j < l[ m[i - 1] ]; j ++) ans.pb('-');
        for(int j = com; j < l[ m[i] ]; j ++) ans.pb(s[ m[i] ][j]);
        ans.pb('P');
    }
}

void write() {
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i ++)
        printf("%c\n", ans[i]);
}

int main() {
    read();
    solve();
    write();

    return 0;
}
