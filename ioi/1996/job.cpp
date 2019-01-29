/*
PROB: job
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <algorithm>
#include <cstring>

int n, typeA, typeB;
int ta[32], tb[32];
int earliestFree[32];
int timesComing[1024];
bool done[1024];

void read() {
    std::cin >> n >> typeA >> typeB;
    for (int i = 0; i < typeA; i++) {
        std::cin >> ta[i];
    }
    for (int i = 0; i < typeB; i++) {
        std::cin >> tb[i];
    }
}

bool checkA(int t) {
    int cnt = 0;
    for (int i = 0; i < typeA; i++) {
        cnt += (t / ta[i]);
    }
    return (cnt >= n);
}

void performA() {
    int le = 0, ri = 20 * n, mid, ans = 20 * n;
    while (le <= ri) {
        mid = (le + ri) >> 1;
        if (checkA(mid)) {
            ans = mid;
            ri = mid - 1;
        } else {
            le = mid + 1;
        }
    }
    std::cout << ans << ' ';
}

bool checkB(int t) {
    memset(done, 0, sizeof(done));

    for (int i = typeB - 1; i >= 0; i--) {
        int limit = t;
        for (int j = n - 1; j >= 0; j--) {
            if (!done[j] && timesComing[j] + tb[i] <= limit) {
                done[j] = true;
                limit -= tb[i];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!done[i]) {
            return false;
        }
    }
    return true;
}

void performAB() {
    std::sort(ta, ta + typeA);
    std::sort(tb, tb + typeB);

    for (int i = 0; i < n; i++) {
        int j_best = 0;
        for (int j = 1; j < typeA; j++) {
            if (earliestFree[j] + ta[j] < earliestFree[j_best] + ta[j_best]) {
                j_best = j;
            }
        }
        timesComing[i] = earliestFree[j_best] + ta[j_best];
        earliestFree[j_best] += ta[j_best];
    }

    int le = 0, ri = 40 * n, mid, ans = 40 * n;
    while (le <= ri) {
        mid = (le + ri) >> 1;
        if (checkB(mid)) {
            ans = mid;
            ri = mid - 1;
        } else {
            le = mid + 1;
        }
    }
    std::cout << ans << '\n';
}

void solve() {
    performA();
    performAB();
}

int main()
{
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);

    read();
    solve();

    return 0;
}
