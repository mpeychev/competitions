#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 1 << 7;

int n;
int y[MAXN], x1[MAXN], x2[MAXN];
int ans;

void read() {
    cin >> n;
    for(int i = 0; i < n; i ++)
        cin >> y[i] >> x1[i] >> x2[i];
}

void solve() {
    for(int i = 0; i < n; i ++) {
        int left = 0, right = 0;
        for(int j = 0; j < n; j ++)
            if(y[j] < y[i]) {
                if(left < y[j] && x1[j] <= x1[i] && x2[j] > x1[i]) left = y[j];
                if(right < y[j] && x1[j] < x2[i] && x2[j] >= x2[i]) right = y[j];
            }
        ans += (y[i] - left) + (y[i] - right);
    }
    
    cout << ans << endl;
}

int main()
{
    read();
    solve();
    
    return 0;
}
