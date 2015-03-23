#include <iostream>
#include <stdio.h>

using namespace std;

int a, b, c;
int l[4], r[4];
int ans;

void read() {
    cin >> a >> b >> c;
    for(int i = 0; i < 3; i ++) {
        cin >> l[i] >> r[i];
        r[i] --;
    }
}

void solve() {
    for(int i = 1; i <= 100; i ++) {
        int br = 0;
        for(int j = 0; j < 3; j ++)
            if(l[j] <= i && i <= r[j])
                br ++;

        if(br == 1) ans += a;
        if(br == 2) ans += 2 * b;
        if(br == 3) ans += 3 * c;
    }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
