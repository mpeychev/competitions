#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;
const LL INF = 1LL << 62;

int n;
int a[MAXN], b[MAXN];
LL dp[MAXN];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &a[i], &b[i]);
}

inline LL abs(LL x) {
    if(x < 0) return -x;
    return x;
}

void solve() {
    sort(a, a + n);
    sort(b, b + n);

    for(int i = n - 1; i >= 0; i --) {
        dp[i] = INF;
        vector<int> vec;
        for(int j = 1; j <= 3 && i + j - 1 < n; j ++) {
            vec.pb(j - 1);
            sort(vec.begin(), vec.end());
            do {
                bool fl = true;
                LL tmp = 0;
                for(int k = 0; k < vec.size(); k ++) {
                    tmp += abs(a[i + k] - b[ i + vec[k] ]);
                    if(a[i + k] == b[ i + vec[k] ]) {
                        fl = false;
                        break;
                    }
                }
                if(fl && dp[i] > tmp + dp[i + j]) dp[i] = tmp + dp[i + j];
            }
            while(next_permutation(vec.begin(), vec.end()));
        }
    }

    cout << dp[0] << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
