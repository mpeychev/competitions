#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 1 << 10;

int n, a[MAXN];

inline int gcd(int x, int y) {
    while(y) {
        int r = x % y;
        x = y; y = r;
    }
    return x;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++)
        cin >> a[i];

    for(int i = 1; i < n; i ++) {
        int d = gcd(a[0], a[i]);
        cout << a[0] / d << "/" << a[i] / d << endl;
    }

    return 0;
}
