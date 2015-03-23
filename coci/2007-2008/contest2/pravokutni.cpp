#include <stdio.h>
#include <iostream>
#include <map>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

const int MAXN = 1515;

inline LL MyAbs(LL x) {
    if(x < 0) return -x;
    return x;
}

inline LL gcd(LL a, LL b) {
    LL r;
    while(b) {
        r = a % b;
        a = b; b = r;
    }
    return a;
}

int n;
PLL m[MAXN];
LL ans = 0;
int hor[MAXN], ver[MAXN];
map<PLL, int> mp[MAXN];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%lld %lld", &m[i].x, &m[i].y);
}

void solve() {
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            if(i != j) {
                PLL tmp = make_pair(m[j].x - m[i].x, m[j].y - m[i].y);
                if(tmp.x == 0) ver[i] ++;
                else if(tmp.y == 0) hor[i] ++;
                else {
                    LL d = gcd(MyAbs(tmp.x), MyAbs(tmp.y));
                    tmp.x /= d;
                    tmp.y /= d;
                    if(mp[i].find(tmp) == mp[i].end()) mp[i][tmp] = 1;
                    else mp[i][tmp] ++;
                }
            }

    for(int i = 0; i < n; i ++) {
        ans += hor[i] * ver[i];
        LL add = 0;

        for(map<PLL, int> :: iterator it = mp[i].begin(); it != mp[i].end(); it ++) {
            PLL tmp = make_pair(it -> first.x, it -> first.y);
            LL b1 = it -> second;

            PLL vec;
            LL b2 = 0;

            vec = make_pair(-tmp.y, tmp.x);
            if(mp[i].find(vec) != mp[i].end()) b2 += mp[i][vec];

            vec = make_pair(tmp.y, -tmp.x);
            if(mp[i].find(vec) != mp[i].end()) b2 += mp[i][vec];

            add += b1 * b2;
        }

        ans += add / 2;
    }

    printf("%lld\n", ans);
}

int main()
{
    read();
    solve();

    return 0;
}
