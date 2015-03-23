#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

const int MAXN = 30100;

int n;
char s[MAXN];

void read() {
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++)
        scanf("%c\n", &s[i]);
}

bool check(int le, int ri) {
    for(int i = le, j = ri; i < ri; i ++, j --)
        if(s[i] < s[j]) return 0;
        else if(s[i] > s[j]) return 1;
    return 0;
}

void solve() {
    int le = 0, ri = n - 1;
    int cnt = 0;
    while(le <= ri) {
        if(!check(le, ri)) {
            printf("%c", s[le]);
            le ++;
        }
        else {
            printf("%c", s[ri]);
            ri --;
        }
        cnt ++;
        if(cnt == 80) {
            printf("\n");
            cnt = 0;
        }
    }
    if(cnt) printf("\n");
}

int main()
{
    read();
    solve();

    return 0;
}
