#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAX_BITS = 1 << 19;
const int MAX_LEN = 10100;

int m, n, sz;
int nxt[MAX_BITS][2];
int cntEnd[MAX_BITS], cntDown[MAX_BITS];

int len;
bool vec[MAX_LEN];

void readVec() {
    scanf("%d", &len);
    for(int i = 0; i < len; i ++)
        scanf("%d", &vec[i]);
}

void add(int cur) {
    for(int i = 0; i < len; i ++) {
        cntDown[cur] ++;
        if(nxt[ cur ][ vec[i] ] == -1) nxt[ cur ][ vec[i] ] = ++ sz;
        cur = nxt[ cur ][ vec[i] ];
    }
    cntEnd[cur] ++;
}

void goDown(int cur) {
    int ans = 0;
    for(int i = 0; i < len; i ++) {
        ans += cntEnd[cur];
        if(nxt[ cur ][ vec[i] ] == -1) {
            cout << ans << endl;
            return;
        }
        else cur = nxt[ cur ][ vec[i] ];
    }
    ans += cntDown[cur] + cntEnd[cur];

    printf("%d\n", ans);
}

int main()
{
    scanf("%d %d", &m, &n);

    memset(nxt, -1, sizeof(nxt));

    for(int i = 0; i < m; i ++) {
        readVec();
        add(0);
    }

    for(int i = 0; i < n; i ++) {
        readVec();
        goDown(0);
    }

    return 0;
}
