/*
PROB: skidesign
LANG: C++
ID: mompej951
*/

#include <iostream>

int main()
{
    freopen("skidesign.in", "r", stdin);
    freopen("skidesign.out", "w", stdout);

    int n;
    int h[10224];

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }

    int ret = 1 << 30;
    for (int lo = 0; lo <= 100; lo++) {
        int hi = lo + 17;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (h[i] < lo) {
                sum += (lo - h[i]) * (lo - h[i]);
            } else if (hi < h[i]) {
                sum += (h[i] - hi) * (h[i] - hi);
            }
        }
        ret = std::min(ret, sum);
    }

    std::cout << ret << std::endl;

    return 0;
}
