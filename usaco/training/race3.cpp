/*
PROB: race3
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <vector>
#include <cstring>

const int MAXN = 64;

int n;
std::vector<int> g[MAXN];
std::vector<int> unavoidable;
std::vector<int> splitting;
bool used[MAXN];
int color[MAXN];

void read() {
    while (true) {
        int a;
        while (std::cin >> a) {
            if (a < 0) {
                break;
            }
            g[n].push_back(a);
        }
        if (a == -1) {
            n--;
            break;
        }
        n++;
    }
}

void dfs(int node, int forbidden) {
    used[node] = true;
    for (int nxt : g[node]) {
        if (!used[nxt] && nxt != forbidden) {
            dfs(nxt, forbidden);
        }
    }
}

void findUnavoidable() {
    for (int i = 1; i < n; i++) {
        memset(used, 0, sizeof(used));
        dfs(0, i);
        if (!used[n]) {
            unavoidable.push_back(i);
        }
    }
    std::cout << (int) unavoidable.size();
    for (int x : unavoidable) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}

void dfsEnding(int node, int splittingPoint) {
    color[node] = 1;
    if (node == splittingPoint) {
        return;
    }
    for (int nxt : g[node]) {
        if (!color[nxt]) {
            dfsEnding(nxt, splittingPoint);
        }
    }
}

bool dfsStarting(int node, int splittingPoint) {
    color[node] = 2;
    for (int nxt : g[node]) {
        if (!color[nxt]) {
            if (dfsStarting(nxt, splittingPoint)) {
                return true;
            }
        } else if (color[nxt] == 1) {
            return true;
        }
    }
    return false;
}

bool testSplitting(int node) {
    memset(color, 0, sizeof(color));
    dfsEnding(0, node);
    return !(dfsStarting(node, node));
}

void findSplitting() {
    for (int x : unavoidable) {
        if (testSplitting(x)) {
            splitting.push_back(x);
        }
    }
    std::cout << (int) splitting.size();
    for (int x : splitting) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}

int main()
{
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);

    read();
    findUnavoidable();
    findSplitting();

    return 0;
}
