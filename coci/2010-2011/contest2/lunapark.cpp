#include <stdio.h>
#include <iostream>
#include <string>

#define pb push_back

using namespace std;

const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

int r, c;
int ma3x[1024][1024];
int mn = 1024, x = -1, y = -1;
string ans;

void read() {
    scanf("%d %d", &r, &c);
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            scanf("%d", &ma3x[i][j]);
}

void go2rowsDown() {
    for(int i = 1; i < c; i ++)
        ans.pb(RIGHT);
    ans.pb(DOWN);
    for(int i = 1; i < c; i ++)
        ans.pb(LEFT);
    ans.pb(DOWN);
}

void go2colsRight() {
    for(int i = 1; i < r; i ++)
        ans.pb(DOWN);
    ans.pb(RIGHT);
    for(int i = 1; i < r; i ++)
        ans.pb(UP);
    ans.pb(RIGHT);
}

void finishRoute(int i) {
    ans.pb(DOWN);
    for(int k = i; k < r; k ++)
        if(k & 1) {
            for(int h = 1; h < c; h ++)
                ans.pb(RIGHT);
            if(k != r - 1) ans.pb(DOWN);
        }
        else {
            for(int h = 1; h < c; h ++)
                ans.pb(LEFT);
            ans.pb(DOWN);
        }
}

void solve() {
    if(r & 1) {
        for(int i = 1; i <= r / 2; i ++)
            go2rowsDown();
        for(int i = 1; i < c; i ++)
            ans.pb(RIGHT);
        return;
    }
    else if(c & 1) {
        for(int i = 1; i <= c / 2; i ++)
            go2colsRight();
        for(int i = 1; i < r; i ++)
            ans.pb(DOWN);
        return;
    }

    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(((i + j) & 1) && ma3x[i][j] < mn) {
                mn = ma3x[i][j];
                x = i; y = j;
            }

    ma3x[x][y] = -1;

    int i = 0;
    for( ; ; ) {
        if(x == i || x == i + 1) break;
        go2rowsDown();
        i += 2;
    }

    if(x == i) {
        for(int k = 0; k < y / 2; k ++) {
            ans.pb(DOWN);
            ans.pb(RIGHT);
            ans.pb(UP);
            ans.pb(RIGHT);
        }
        ans.pb(DOWN);
        ans.pb(RIGHT);
        for(int k = 0; k < (c - y) / 2; k ++) {
            ans.pb(RIGHT);
            ans.pb(UP);
            ans.pb(RIGHT);
            ans.pb(DOWN);
        }
        if(x + 2 == r) return;
        finishRoute(i + 2);
    }
    else {
        for(int k = 1; k <= y / 2; k ++) {
            ans.pb(DOWN);
            ans.pb(RIGHT);
            ans.pb(UP);
            ans.pb(RIGHT);
        }
        ans.pb(RIGHT);
        for(int k = 1; k < (c - y) / 2; k ++) {
            ans.pb(DOWN);
            ans.pb(RIGHT);
            ans.pb(UP);
            ans.pb(RIGHT);
        }
        ans.pb(DOWN);
        if(x + 2 == r) return;
        finishRoute(i + 2);
    }
}

void write() {
    cout << ans << endl;
}

int main()
{
    read();
    solve();
    write();

    return 0;
}
