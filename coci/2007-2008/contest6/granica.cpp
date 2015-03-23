#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

int n, d;
int a[1 << 7];
vector<int> ans;

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &a[i]);
}

int gcd(int x, int y) {
    while(y) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

void solve() {
    sort(a, a + n);

    d = a[1] - a[0];
    for(int i = 1; i < n; i ++)
        for(int j = 0; j < i; j ++)
            d = gcd(d, a[i] - a[j]);

    for(int i = 2; i * i <= d; i ++)
        if(d % i == 0) {
            ans.pb(i);
            if(i != d / i) ans.pb(d / i);
        }

    sort(ans.begin(), ans.end());
    ans.pb(d);

    for(int i = 0; i < ans.size(); i ++) {
        if(i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
}

int main()
{
    read();
    solve();

    return 0;
}
