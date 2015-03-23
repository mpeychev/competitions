#include <iostream>
#include <stdio.h>
#include <map>

using namespace std;

int n, k;
int b[1 << 17];
map<int, int> cnt;
int le, groups, ans;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i ++)
        scanf("%d", &b[i]);
}

void solve() {
    cnt[ b[0] ] ++;
    groups ++;
    ans = 1;
    for(int i = 1; i < n; i ++)
        if(cnt[ b[i] ]) {
            cnt[ b[i] ] ++;
            ans = max(ans, cnt[ b[le] ]);
        }
        else {
            cnt[ b[i] ] ++;
            groups ++;
            while(groups > k + 1) {
                ans = max(ans, cnt[ b[le] ]);
                cnt[ b[le] ] --;
                if(!cnt[ b[le] ]) groups --;
                le ++;
            }
        }

    while(le < n) {
        ans = max(ans, cnt[ b[le] ]);
        cnt[ b[le] ] --;
        le ++;
    }

    cout << ans << endl;
}

int main()
{
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);

    read();
    solve();

    return 0;
}
