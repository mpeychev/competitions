#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef long long LL;

LL n, x0, y0, m;
LL xmax, xmin, ymax, ymin;
LL x, y, le, ri, mid;
int cnt[4];

bool examine(LL x, LL y) {
    if(x < 1 || x > n || y < 1 || y > n) return false;

    char inp[8];

    printf("examine %lld %lld\n", x, y);
    fflush(stdout);
    scanf("%s", &inp);
    if(inp[0] == 't') return true;
    return false;
}

void solution(LL x, LL y) {
    printf("solution %lld %lld\n", x, y);
    fflush(stdout);
    exit(0);
}

void read() {
    scanf("%lld %lld %lld", &n, &x0, &y0);
}

void findBorders() {
    /// go right
    x = x0;
    for(int i = 0; ; i ++) {
        x += (1 << i);
        if(x > n) {
            x = n;
            break;
        }
        if(!examine(x, y0)) break;
    }

    le = x0, ri = x;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        bool val1, val2;
        val1 = examine(mid, y0);
        if(!val1) ri = mid - 1;
        else {
            val2 = examine(mid + 1, y0);
            if(!val2) {
                xmax = mid;
                break;
            }
            le = mid + 1;
        }
    }

    /// go left
    x = x0;
    for(int i = 0; ; i ++) {
        x -= (1 << i);
        if(x < 1) {
            x = 1;
            break;
        }
        if(!examine(x, y0)) break;
    }

    le = x, ri = x0;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        bool val1, val2;
        val1 = examine(mid, y0);
        if(!val1) le = mid + 1;
        else {
            val2 = examine(mid - 1, y0);
            if(!val2) {
                xmin = mid;
                break;
            }
            ri = mid - 1;
        }
    }

    /// go up
    y = y0;
    for(int i = 0; ; i ++) {
        y += (1 << i);
        if(y > n) {
            y = n;
            break;
        }
        if(!examine(x0, y)) break;
    }

    le = y0, ri = y;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        bool val1, val2;
        val1 = examine(x0, mid);
        if(!val1) ri = mid - 1;
        else {
            val2 = examine(x0, mid + 1);
            if(!val2) {
                ymax = mid;
                break;
            }
            le = mid + 1;
        }
    }

    m = xmax - xmin + 1;
    ymin = ymax - m + 1;
}

void findCentre() {
    x0 = (xmin + xmax) >> 1;
    y0 = (ymin + ymax) >> 1;

    for(int i = 1; ; i ++)
        if(examine(x0 - 2 * i * m, y0)) cnt[0] ++;
        else break;

    for(int i = 1; ; i ++)
        if(examine(x0 + 2 * i * m, y0)) cnt[1] ++;
        else break;

    for(int i = 1; ; i ++)
        if(examine(x0, y0 - 2 * i * m)) cnt[2] ++;
        else break;

    if(cnt[0] == 0 && cnt[1] == 2 && cnt[2] == 2) solution(x0 + 2 * m, y0 - 2 * m);
    if(cnt[0] == 1 && cnt[1] == 1 && cnt[2] == 2) solution(x0, y0 - 2 * m);
    if(cnt[0] == 2 && cnt[1] == 0 && cnt[2] == 2) solution(x0 - 2 * m, y0 - 2 * m);
    if(cnt[0] == 0 && cnt[1] == 1 && cnt[2] == 1) solution(x0 + m, y0 - m);
    if(cnt[0] == 1 && cnt[1] == 0 && cnt[2] == 1) solution(x0 - m, y0 - m);
    if(cnt[0] == 0 && cnt[1] == 2 && cnt[2] == 1) solution(x0 + 2 * m, y0);
    if(cnt[0] == 1 && cnt[1] == 1 && cnt[2] == 1) solution(x0, y0);
    if(cnt[0] == 2 && cnt[1] == 0 && cnt[2] == 1) solution(x0 - 2 * m, y0);
    if(cnt[0] == 0 && cnt[1] == 1 && cnt[2] == 0) solution(x0 + m, y0 + m);
    if(cnt[0] == 1 && cnt[1] == 0 && cnt[2] == 0) solution(x0 - m, y0 + m);
    if(cnt[0] == 0 && cnt[1] == 2 && cnt[2] == 0) solution(x0 + 2 * m, y0 + 2 * m);
    if(cnt[0] == 1 && cnt[1] == 1 && cnt[2] == 0) solution(x0, y0 + 2 * m);
    if(cnt[0] == 2 && cnt[1] == 0 && cnt[2] == 0) solution(x0 - 2 * m, y0 + 2 * m);
}

int main()
{
    read();
    findBorders();
    findCentre();

    return 0;
}
