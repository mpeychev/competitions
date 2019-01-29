/*
PROB: combo
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <cstdio>

bool isValid(int pivot, int n, int k) {
    if (k == pivot) {
        return true;
    }
    if (pivot + 1 <= n) {
        if (k == pivot + 1) {
            return true;
        }
    } else {
        if (k == 1) {
            return true;
        }
    }
    if (pivot + 2 <= n) {
        if (k == pivot + 2) {
            return true;
        }
    } else {
        if (pivot == n - 1 && k == 1) {
            return true;
        }
        if (pivot == n && k == 2) {
            return true;
        }
    }
    if (pivot - 1 >= 1) {
        if (k == pivot - 1) {
            return true;
        }
    } else {
        if (k == n) {
            return true;
        }
    }
    if (pivot - 2 >= 1) {
        if (k == pivot - 2) {
            return true;
        }
    } else {
        if (pivot == 2 && k == n) {
            return true;
        }
        if (pivot == 1 && k == n - 1) {
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);

    int n;
    int a, b, c;
    int d, e, f;

    std::cin >> n;
    std::cin >> a >> b >> c;
    std::cin >> d >> e >> f;

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (isValid(a, n, i) && isValid(b, n, j) && isValid(c, n, k)) {
                    cnt++;
                } else if (isValid(d, n, i) && isValid(e, n, j) && isValid(f, n, k)) {
                    cnt++;
                }
            }
        }
    }
    std::cout << cnt << std::endl;

    return 0;
}
