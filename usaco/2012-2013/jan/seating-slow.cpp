#include <iostream>
#include <stdio.h>

using namespace std;

int n, m;
bool a[256];
int ans;

void put(int le, int ri, bool val) {
    for(int i = le; i <= ri; i ++)
        a[i] = val;
}

bool check(int le, int ri) {
    for(int i = le; i <= ri; i ++)
        if(a[i])
            return false;
    return true;
}

void find(int p) {
    for(int i = 0; i + p - 1 < n; i ++)
        if(check(i, i + p - 1)) {
            put(i, i + p - 1, true);
            cout << "ok\n";
            return;
        }
    cout << "fail\n";
    ans ++;
}

int main()
{
    freopen("seating.in", "r", stdin);
    freopen("seating2.out", "w", stdout);

    scanf("%d %d\n", &n, &m);

    char cmd;
    int a, b, p;

    for(int i = 0; i < m; i ++) {
        scanf("%c", &cmd);
        if(cmd == 'A') {
            scanf("%d\n", &p);
            find(p);
        }
        else {
            scanf("%d %d\n", &a, &b);
            a --;
            b --;
            put(a, b, false);
        }
    }

    cout << ans << endl;

    return 0;
}
