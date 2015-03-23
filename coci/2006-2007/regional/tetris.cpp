#include <iostream>
#include <stdio.h>

using namespace std;

int c, p;
int h[128];
int ans;

void read() {
    scanf("%d %d", &c, &p);
    for(int i = 0; i < c; i ++)
        scanf("%d", &h[i]);
}

void solve() {
    if(p == 1) {
        ans = c;
        for(int i = 0; i < c - 3; i ++)
            if(h[i] == h[i + 1] && h[i] == h[i + 2] && h[i] == h[i + 3])
                ans ++;
        cout << ans << endl;
        return;
    }

    if(p == 2) {
        for(int i = 0; i < c - 1; i ++)
            if(h[i] == h[i + 1])
                ans ++;
        cout << ans << endl;
        return;
    }

    if(p == 5) {
        for(int i = 0; i < c - 2; i ++)
            if(h[i] == h[i + 1] && h[i] == h[i + 2])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] + 1 == h[i + 1])
                ans ++;

        for(int i = 1; i < c - 1; i ++)
            if(h[i] + 1 == h[i - 1] && h[i] + 1 == h[i + 1])
                ans ++;

        for(int i = 1; i < c; i ++)
            if(h[i] + 1 == h[i - 1])
                ans ++;

        cout << ans << endl;
        return;
    }

    if(p == 3) {
        for(int i = 0; i < c - 2; i ++)
            if(h[i] == h[i + 1] && h[i] + 1 == h[i + 2])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] - 1 == h[i + 1])
                ans ++;

        cout << ans << endl;
        return;
    }

    if(p == 4) {
        for(int i = 0; i < c - 2; i ++)
            if(h[i] - 1 == h[i + 1] && h[i] - 1 == h[i + 2])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] + 1 == h[i + 1])
                ans ++;

        cout << ans << endl;
        return;
    }

    if(p == 6) {
        for(int i = 0; i < c - 2; i ++)
            if(h[i] == h[i + 1] && h[i] == h[i + 2])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] == h[i + 1])
                ans ++;

        for(int i = 0; i < c - 2; i ++)
            if(h[i] + 1 == h[i + 1] && h[i] + 1 == h[i + 2])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] - 2 == h[i + 1])
                ans ++;

        cout << ans << endl;
        return;
    }

    if(p == 7) {
        for(int i = 0; i < c - 2; i ++)
            if(h[i] == h[i + 1] && h[i] == h[i + 2])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] == h[i + 1])
                ans ++;

        for(int i = 0; i < c - 1; i ++)
            if(h[i] + 2 == h[i + 1])
                ans ++;

        for(int i = 0; i < c - 2; i ++)
            if(h[i] == h[i + 1] && h[i] - 1 == h[i + 2])
                ans ++;

        cout << ans << endl;
        return;
    }
    cout << ans << endl;
    return;
}

int main()
{
    read();
    solve();

    return 0;
}
