#include <stdio.h>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 20100;

int n;
int m[MAXN];
map<int, int> mp[5];

bool cmp(int a, int b) {
    int cnt = 0;
    for(int i = 0; i < 5; i ++)
        cnt += (mp[i][a] < mp[i][b]);
    return cnt >= 3;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < 5; i ++)
        for(int j = 0; j < n; j ++) {
            scanf("%d", &m[j]);
            mp[i][ m[j] ] = j;
        }

    sort(m, m + n, cmp);

    for(int i = 0; i < n; i ++)
        printf("%d\n", m[i]);

    return 0;
}
