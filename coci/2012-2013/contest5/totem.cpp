#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

int n;
int a[1 << 18], b[1 << 18];
bool startEven[1 << 18], endEven[1 << 18];
bool startOdd[1 << 18], endOdd[1 << 18];
int firstRowBound, lastRowBound;
int level[1 << 18], prv[1 << 18];
queue<int> q;

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n * n - n / 2; i ++)
        scanf("%d %d", &a[i], &b[i]);
}

void init() {
    firstRowBound = n - 1;

    if(n & 1) lastRowBound = n * n - (n / 2) - n;
    else lastRowBound = n * n - (n / 2) - n + 1;

    int cur = 0;
    for(int i = 0; i < n; i ++) {
        if(i % 2 == 0) {
            startEven[cur] = true;
            endEven[cur + n - 1] = true;
            cur = cur + n;
        }
        else {
            startOdd[cur] = true;
            endOdd[cur + n - 2] = true;
            cur = cur + n - 1;
        }
    }
}

void bfs() {
    q.push(0);
    level[0] = 1;
    prv[0] = -1;

    while(!q.empty()) {
        int x = q.front();
        q.pop();

        if(!endEven[x] && !endOdd[x] && !level[x + 1] && b[x] == a[x + 1]) {
            level[x + 1] = level[x] + 1;
            prv[x + 1] = x;
            q.push(x + 1);
        }

        if(!startEven[x] && !startOdd[x] && !level[x - 1] && a[x] == b[x - 1]) {
            level[x - 1] = level[x] + 1;
            prv[x - 1] = x;
            q.push(x - 1);
        }

        if(x < lastRowBound && !endEven[x] && !level[x + n] && b[x] == a[x + n]) {
            level[x + n] = level[x] + 1;
            prv[x + n] = x;
            q.push(x + n);
        }

        if(x < lastRowBound && !startEven[x] && !level[x + n - 1] && a[x] == b[x + n - 1]) {
            level[x + n - 1] = level[x] + 1;
            prv[x + n - 1] = x;
            q.push(x + n - 1);
        }

        if(x > firstRowBound && !endEven[x] && !level[x - n + 1] && b[x] == a[x - n + 1]) {
            level[x - n + 1] = level[x] + 1;
            prv[x - n + 1] = x;
            q.push(x - n + 1);
        }

        if(x > firstRowBound && !startEven[x] && !level[x - n] && a[x] == b[x - n]) {
            level[x - n] = level[x] + 1;
            prv[x - n] = x;
            q.push(x - n);
        }
    }
}

void write(int cur) {
    if(cur == 0) {
        printf("1");
        return;
    }

    write(prv[cur]);
    printf(" %d", cur + 1);
}

int main()
{
    read();
    init();
    bfs();
    for(int i = n * n - n / 2 - 1; i >= 0; i --)
        if(level[i]) {
            printf("%d\n", level[i]);
            write(i);
            break;
        }

    return 0;
}
