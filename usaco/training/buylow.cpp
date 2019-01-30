/*
PROB: buylow
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 5050;
const int BASE = 100000000;

int n;
int p[MAXN];
int longest[MAXN];
std::vector<int> cnt[MAXN];

void read() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
}

inline std::vector<int> oneConst() {
    return std::vector<int>(1, 1);
}

std::vector<int> sum(std::vector<int> a, std::vector<int> b) {
    while (a.size() < b.size()) {
        a.insert(a.begin(), 0);
    }
    while (a.size() > b.size()) {
        b.insert(b.begin(), 0);
    }
    std::vector<int> ret;
    ret.reserve(a.size());
    int addOn = 0;
    for (int i = (int) a.size() - 1; i >= 0; i--) {
        int digit = a[i] + b[i] + addOn;
        ret.push_back(digit % BASE);
        addOn = digit / BASE;
    }
    if (addOn) {
        ret.push_back(addOn);
    }
    std::reverse(ret.begin(), ret.end());

    return ret;
}

void solve() {
    cnt[0] = oneConst();
    for (int i = 1; i <= n; i++) {
        cnt[i] = oneConst();
        int prvP = p[i];
        for (int j = i - 1; j >= 0; j--) {
            if (p[j] > p[i]) {
                if (longest[j] + 1 > longest[i]) {
                    longest[i] = longest[j] + 1;
                    cnt[i] = cnt[j];
                    prvP = p[j];
                } else if (longest[j] + 1 == longest[i] && prvP > p[j]) {
                    cnt[i] = sum(cnt[i], cnt[j]);
                    prvP = p[j];
                }
            }
        }
    }
    std::cout << longest[n] << ' ';
    for (int digit : cnt[n]) {
        std::cout << digit;
    }
    std::cout << '\n';
}

int main()
{
    freopen("buylow.in", "r", stdin);
    freopen("buylow.out", "w", stdout);

    read();
    solve();

    return 0;
}
