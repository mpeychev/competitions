#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

const int MAXL = 25;

int n;
char s[128][16];
int start;
bool letters[32], used[32];
int l[128];
int g[32][32];
int dp[32], prv[32], st;

void read() {
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%s", &s[i]);
        l[i] = strlen(s[i]);

        for(int j = 0; j < l[i]; j ++)
            letters[ s[i][j] - 'a' ] = 1;
    }
}

void dfs(int let) {
    used[let] = 1;
    for(int i = 0; i <= MAXL; i ++)
        if(g[let][i]) {
            if(i == start) {
                printf("!\n");
                exit(0);
            }
            if(!used[i])
                dfs(i);
        }
}

int get(int let) {
    if(dp[let] != -1)
        return dp[let];

    int ret = 0, prvs = -1;
    for(int i = 0; i <= MAXL; i ++)
        if(g[i][let]) {
            int path = get(i);
            if(ret < path) {
                ret = path;
                prvs = i;
            }
        }

    dp[let] = ret + 1;
    prv[let] = prvs;

    return dp[let];
}

void print(int let) {
    if(let == -1) return;
    print(prv[let]);
    printf("%c", let + 'a');
}

void solve() {
    for(int i = 0; i < n; i ++)
        for(int j = i + 1; j < n; j ++) {
            int m = min(l[i], l[j]);
            for(int k = 0; k < m; k ++)
                if(s[i][k] != s[j][k]) {
                    g[ s[i][k] - 'a' ][ s[j][k] - 'a' ] = 1;
                    break;
                }
        }

    for(int i = 0; i <= MAXL; i ++)
        if(letters[i]) {
            memset(used, 0, sizeof(used));
            start = i;
            dfs(i);
        }

    for(int i = 0; i <= MAXL; i ++)
        st += letters[i];

    memset(dp, -1, sizeof(dp));
    memset(prv, -1, sizeof(prv));

    for(int i = 0; i <= MAXL; i ++)
        if(get(i) == st) {
            print(i);
            printf("\n");
            return;
        }

    printf("?\n");
}

int main()
{
    read();
    solve();

    return 0;
}
