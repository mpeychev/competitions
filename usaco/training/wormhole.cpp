/*
PROB: wormhole
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <cstring>

struct Point {
    int x, y;
    
    void read() {
        std::cin >> x >> y;
    }
};

int n;
Point points[16];
int pairing[16];
int ans;

void read() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        points[i].read();
    }
}

bool check() {
    for (int i = 0; i < n; i++) {
        int enter = i;
        while (enter != -1) {
            int out = -1;
            for (int j = 0; j < n; j++) {
                if (enter != j && pairing[enter] == pairing[j]) {
                    out = j;
                    break;
                }
            }
            enter = -1;
            for (int j = 0; j < n; j++) {
                if (points[out].y == points[j].y && points[out].x < points[j].x) {
                    if (enter == -1 || points[enter].x > points[j].x) {
                        enter = j;
                    }
                }
            }

            if (enter == i) {
                return true;
            }
        }
    }
    return false;
}

void go(int color) {
    if (color == n / 2) {
        ans += check();
        return;
    }

    int f = -1;
    for (int i = 0; i < n; i++) {
        if (pairing[i] == -1) {
            f = i;
            break;
        }
    }

    pairing[f] = color;
    for (int i = f + 1; i < n; i++) {
        if (pairing[i] == -1) {
            pairing[i] =  color;
            go(color + 1);
            pairing[i] = -1;
        }
    }
    pairing[f] = -1;
}

void solve() {
    memset(pairing, -1, sizeof(pairing));
    go(0);
    std::cout << ans << std::endl;
}

int main()
{
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);

    read();
    solve();

    return 0;
}
