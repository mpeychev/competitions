#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 300010;

int n, pat[MAXN], b[MAXN];
int le, ri;
int coef[MAXN];
int ans[MAXN];

void init() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &pat[i]);
    for(int i = 0; i < n; i ++)
        scanf("%d", &b[i]);
    sort(b, b + n);
}

void solve() {
    if(pat[0] < pat[1]) coef[0] = -1;
    else coef[0] = 1;

    if(pat[n - 1] < pat[n - 2]) coef[n - 1] = -1;
    else coef[n - 1] = 1;

    for(int i = 1; i < n - 1; i ++) {
        if(pat[i - 1] > pat[i] && pat[i] < pat[i + 1]) coef[i] = -2;
        if(pat[i - 1] < pat[i] && pat[i] > pat[i + 1]) coef[i] = 2;
    }

    le = 0; ri = n - 1;
    for(int i = 0; i < n; i ++) {
        if(coef[i] == -2) ans[i] = b[le ++];
        if(coef[i] == 2) ans[i] = b[ri --];
    }

    if(coef[0] == 1) ans[0] = b[ri --];
    else ans[0] = b[le ++];

    if(coef[n - 1] == 1) ans[n - 1] = b[ri --];
    else ans[n - 1] = b[le ++];

    for(int i = 1; i < n - 1; i ++)
        if(!ans[i]) {
            int bound;
            for(int j = i + 1; j < n; j ++)
                if(ans[j]) {
                    bound = j - 1;
                    break;
                }
            if(ans[i - 1] < ans[bound + 1]) {
                for(int j = i; j <= bound; j ++)
                    ans[j] = b[le ++];
            }
            else {
                for(int j = i; j <= bound; j ++)
                    ans[j] = b[ri --];
            }

            i = bound;
        }
}

void write() {
    long long res = 0;
    for(int i = 0; i < n - 1; i ++)
        res += abs(ans[i] - ans[i + 1]);
    printf("%lld\n", res);

    printf("%d", ans[0]);
    for(int i = 1; i < n; i ++)
        printf(" %d", ans[i]);
    printf("\n");
}

int main()
{
    init();
    solve();
    write();

    return 0;
}
