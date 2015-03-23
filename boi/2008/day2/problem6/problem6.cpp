#include <stdio.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#define pb push_back

using namespace std;

int n, m;
int a[8];

vector< deque<int> > vec[5010];
deque<int> tmp;
int num;
bool used[5010];

int idx[8];

bool cmp(int a, int b) {
    return (int)vec[a].size() < (int)vec[b].size();
}

void read() {
    for(int i = 0; i < n; i ++)
        scanf("%d", &a[i]);
}

void split(int p, int last) {
    if(last >= p)
        return;

    if(p <= 100) {
        tmp.pb(p);
        vec[num].pb(tmp);
        tmp.pop_back();
    }

    for(int i = last + 1; i * i < p; i ++)
        if(p % i == 0) {
            tmp.pb(i);
            split(p / i, i);
            tmp.pop_back();
        }
}

bool check2(int a, int i, int b, int j) {
    int k1 = 0, k2 = 0;
    for( ; ; ) {
        if(k1 >= vec[a][i].size() || k2 >= vec[b][j].size()) break;
        if(vec[a][i][k1] == vec[b][j][k2]) return true;
        if(vec[a][i][k1] < vec[b][j][k2]) k1 ++;
        else k2 ++;
    }
    return false;
}

bool check(int k) {
    if(k == n)
        return true;

    for(int i = 0; i < vec[ a[k] ].size(); i ++) {
        bool fl = true;
        for(int j = 0; j < k; j ++)
            if(check2(a[k], i, a[j], idx[j])) {
                fl = false;
                break;
            }
        if(fl) {
            idx[k] = i;
            if(check(k + 1))
                return true;
        }
    }

    return false;
}

void solve() {
    if(!used[1]) {
        vec[1].pb(tmp);
        used[1] = true;
    }

    for(int i = 0; i < n; i ++) {
        if(!used[ a[i] ]) {
            used[ a[i] ] = true;
            num = a[i];
            split(a[i], 1);
        }

        if(vec[ a[i] ].empty()) {
            printf("NO\n");
            return;
        }
    }

    sort(a, a + n, cmp);

    if(check(0)) printf("YES\n");
    else printf("NO\n");
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++) {
        read();
        solve();
    }

    return 0;
}
