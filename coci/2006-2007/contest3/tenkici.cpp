#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 512;

struct el {
    int idx, x, y;

    el() {}
    el(int _idx, int _x, int _y): idx(_idx), x(_x), y(_y) {}
};

struct record {
    int idx;
    char dir;

    record() {}
    record(int _idx, char _dir): idx(_idx), dir(_dir) {}
};

int n;
int inpR[MAXN], inpC[MAXN];
int ma3x[MAXN][MAXN];

int r[MAXN], c[MAXN];
el vec[MAXN];
vector< PII > moveRight;

vector< record > ans;

void read() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%d %d", &inpR[i], &inpC[i]);
}

bool cmpY(el a, el b) {
    return a.y < b.y;
}

bool cmpX(el a, el b) {
    return a.x < b.x;
}

void solve() {
    for(int i = 1; i <= n; i ++)
        r[i] = inpR[i], c[i] = inpC[i];

    for(int i = 1; i <= n; i ++)
        vec[i] = el(i, r[i], c[i]);

    sort(vec + 1, vec + n + 1, cmpY);

    for(int i = 1; i <= n; i ++) {
        if(vec[i].y < i) moveRight.pb(mp(vec[i].idx, i));
        if(vec[i].y > i) {
            for(int j = vec[i].y; j > i; j --)
                ans.pb(record(vec[i].idx, 'L'));
            c[ vec[i].idx ] = i;
        }
    }

    for(int i = moveRight.size() - 1; i >= 0; i --) {
        for(int j = c[ moveRight[i].first ]; j < moveRight[i].second; j ++)
            ans.pb(record(moveRight[i].first, 'R'));
        c[ moveRight[i].first ] = moveRight[i].second;
    }

    for(int i = 1; i <= n; i ++)
        vec[i] = el(i, r[i], c[i]);

    sort(vec + 1, vec + n + 1, cmpX);

    for(int i = 1; i <= n; i ++) {
        if(vec[i].x < i) {
            for(int j = vec[i].x; j < i; j ++)
                ans.pb(record(vec[i].idx, 'D'));
        }
        if(vec[i].x > i) {
            for(int j = vec[i].x; j > i; j --)
                ans.pb(record(vec[i].idx, 'U'));
        }
    }
}

void print() {
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i ++)
        printf("%d %c\n", ans[i].idx, ans[i].dir);
}

bool check() {
    for(int i = 1; i <= n; i ++)
        ma3x[ inpR[i] ][ inpC[i] ] = 1;

    for(int i = 0; i < ans.size(); i ++) {
        int idx = ans[i].idx;
        int oldR = inpR[idx], oldC = inpC[idx];
        int newR = oldR, newC = oldC;

        switch(ans[i].dir) {
            case 'L': newC --; break;
            case 'R': newC ++; break;
            case 'U': newR --; break;
            case 'D': newR ++; break;
            default: printf("wrong direction"); exit(0);
        }

        if(newR < 1 || newR > n || newC < 1 || newC > n) {
            printf("out of bound\n");
            exit(0);
        }

        ma3x[oldR][oldC] --;
        ma3x[newR][newC] ++;

        if(ma3x[newR][newC] > 1) {
            printf("more than one tank on a cell\n");
            exit(0);
        }

        inpR[idx] = newR;
        inpC[idx] = newC;
    }

    for(int i = 1; i <= n; i ++) {
        int sum = 0;
        for(int j = 1; j <= n; j ++)
            sum += ma3x[i][j];
        if(sum != 1) {
            printf("wrong sum row\n");
            exit(0);
        }
    }

    for(int i = 1; i <= n; i ++) {
        int sum = 0;
        for(int j = 1; j <= n; j ++)
            sum += ma3x[j][i];
        if(sum != 1) {
            printf("wrong sum cols\n");
            exit(0);
        }
    }

    printf("ok\n");
}

int main()
{
    read();
    solve();
    print();
//    check();

    return 0;
}
