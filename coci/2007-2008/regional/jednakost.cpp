#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAX_LEN = 1 << 10;
const int INF = 1 << 20;

char str[MAX_LEN];
int dp[MAX_LEN][5050];
int nxt[MAX_LEN][5050];
int s, n, dig[MAX_LEN];

void read() {
    scanf("%s", &str);
}

int go(int curPos, int curSum) {
    if(dp[curPos][curSum] != -1)
        return dp[curPos][curSum];
    
    if(curPos >= n) {
        if(curSum == s) return dp[curPos][curSum] = 0;
        return dp[curPos][curSum] = INF;
    }
    
    int p = dig[curPos];
    int tmp = 0;
    int ret = INF;
    
    if(p != curPos) {
        ret = 1 + go(p, curSum);
        nxt[curPos][curSum] = p;
    }
    
    for(int i = p; i < n; i ++) {
        tmp = tmp * 10 + (str[i] - '0');
        if(tmp + curSum > s) break;
        int eval = 1 + go(i + 1, tmp + curSum);
        if(ret > eval) {
            ret = eval;
            nxt[curPos][curSum] = i + 1;
        }
    }
    return dp[curPos][curSum] = ret;
}

void solve() {
    int p = 1;
    for(int i = strlen(str) - 1; i >= 0; i --) {
        if(str[i] == '=') {
            n = i;
            break;
        }
        s += p * (str[i] - '0');
        p *= 10;
    }
    
    dig[n] = n;
    for(int i = n - 1; i >= 0; i --)
        if(str[i] == '0') dig[i] = dig[i + 1];
        else dig[i] = i;
    
    memset(dp, -1, sizeof(dp));
    go(0, 0);
    
    int curPos = 0, curSum = 0;
    while(curPos < n) {
        int add = 0;
        for(int i = curPos; i < nxt[curPos][curSum]; i ++) {
            printf("%c", str[i]);
            add = add * 10 + (str[i] - '0');
        }
        curPos = nxt[curPos][curSum];
        curSum += add;
        if(curPos < n) printf("+");
    }
    printf("=%d\n", s);
}

int main()
{
    read();
    solve();
    
    return 0;
}
