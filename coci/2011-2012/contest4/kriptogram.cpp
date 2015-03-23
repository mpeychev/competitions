#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 1 << 20;

char s[MAXN];
map<string, int> mp1, mp2;
vector<int> t, p;
int f[MAXN];
int n, m;

void read() {
    while(scanf("%s", &s) && s[0] != '$') {
        string tmp = string(s);
        if(mp1.find(tmp) != mp1.end())
            t.pb(t.size() - mp1[tmp]);
        else
            t.pb(-1);
        mp1[tmp] = t.size() - 1;
    }

    while(scanf("%s", &s) && s[0] != '$') {
        string tmp = string(s);
        if(mp2.find(tmp) != mp2.end())
            p.pb(p.size() - mp2[tmp]);
        else
            p.pb(-1);
        mp2[tmp] = p.size() - 1;
    }

    n = t.size();
    m = p.size();
}

bool cmp1(int x, int y) {
    if(p[x] == -1) {
        if(p[y] == -1) return true;
        return p[y] > x;
    }
    return p[x] == p[y];
}

void prekmp() {
    f[0] = 0;
    for(int i = 1; i < m; i ++) {
        int j = f[i - 1];
        while(j && !cmp1(j, i)) j = f[j - 1];
        if(cmp1(j, i)) f[i] = j + 1;
        else f[i] = 0;
    }
}

bool cmp(int x, int y) {
    if(t[x] == p[y]) return true;
    if(t[y] == -1) {
        if(t[x] > y) return true;
        return false;
    }
    return false;
}

void kmp() {
    int j = 0;
    for(int i = 0; i < n; i ++)
    {
        while(j && !cmp(i, j)) j = f[j - 1];
        if(cmp(i, j)) j ++;

        if(j == m) {
            printf("%d\n", i - m + 2);
            return;
        }
    }
}

int main()
{
    read();
    prekmp();
    kmp();

    return 0;
}
