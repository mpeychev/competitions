#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 1 << 7;

int n, l;
int d[MAXN], r[MAXN], g[MAXN];
bool fl[MAXN];
int br[MAXN];
int pos, ti, sidx;

void read() {
    scanf("%d %d", &n, &l);
    for(int i = 0; i < n; i ++)
        scanf("%d %d %d", &d[i], &r[i], &g[i]);
}

void solve() {
    while(pos < l) {
        if(pos != d[sidx]) pos ++;
        else {
            if(fl[sidx]) {
                pos ++;
                sidx ++;
            }
        }
        ti ++;
        for(int i = sidx; i < n; i ++) {
            br[i] ++;
            if(!fl[i] && br[i] == r[i]) {
                fl[i] = true;
                br[i] = 0;
            }
            if(fl[i] && br[i] == g[i]) {
                fl[i] = false;
                br[i] = 0;
            }
        }
    }
    cout << ti << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
