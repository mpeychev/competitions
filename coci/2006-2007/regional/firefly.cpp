#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

int n, h, mn = 500500, cnt;
vector<int> up, down;

void read() {
    int x;

    scanf("%d %d", &n, &h);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &x);
        if(i % 2 == 0) up.pb(x);
        else down.pb(h - x + 1);
    }
}

int bs1(int x) {
    int le = 0, ri = down.size() - 1, mid;
    int ret = 0;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(down[mid] <= x) {
            ret = mid + 1;
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    return ret;
}

int bs2(int x) {
    int le = 0, ri = up.size() - 1, mid;
    int ret = 0;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(up[mid] >= x) {
            ret = up.size() - mid;
            ri = mid - 1;
        }
        else le = mid + 1;
    }
    return ret;
}

void solve() {
    sort(up.begin(), up.end());
    sort(down.begin(), down.end());

    for(int i = 1; i <= h; i ++) {
        int tmp = bs1(i) + bs2(i);
        if(tmp < mn) {
            mn = tmp;
            cnt = 1;
        }
        else if(tmp == mn) cnt ++;
    }

    cout << mn << " " << cnt << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
