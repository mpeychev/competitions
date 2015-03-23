#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const LL INF = (LL)1e9;
const LL MAXP = 20000000;

LL n, p;
bool pr[MAXP + 10];
// 0 - ok
// 1 - not ok
vector<int> vec;
int sz;

void read() {
    cin >> n >> p;
}

void erato1() {
    pr[0] = 1;
    for(LL i = 2; i < p && i * p <= INF; i ++)
        if(!pr[i]) {
            pr[i] = 1;
            for(LL j = i * i; j * p <= INF; j += i)
                pr[j] = 1;
        }
}

void get1() {
    for(LL i = 1; i * p <= INF; i ++)
        if(!pr[i]) {
            n --;
            if(!n) {
                printf("%lld\n", i * p);
                return;
            }
        }
    printf("0\n");
}

bool isPrime(int x) {
    for(int i = 2; i * i <= x; i ++)
        if(x % i == 0)
            return false;
    return true;
}

void gen() {
    for(int i = 2; i < p; i ++)
        if(isPrime(i)) {
            vec.pb(i);
            sz ++;
        }
}

int calc(int x) {
    int ret = 0;
    for(int i = 0; i < (1 << sz); i ++) {
        LL t = 1;
        int cnt = 0;

        for(int j = 0; j < sz; j ++)
            if((i >> j) & 1) {
                cnt ++;
                t = t * vec[j];
                if(t > x) break;
            }

        if(t > x) continue;

        if(cnt & 1)
            ret -= x / t;
        else
            ret += x / t;
    }

    return ret;
}

void solve() {
    if(p >= 50) {
        erato1();
        get1();
    }
    else {
        gen();

        int l = 1, r = INF / p, mid;
        while(l < r) {
            mid = (l + r) >> 1;
            int tmp = calc(mid);
            if(tmp >= n) r = mid - 1;
            else l = mid + 1;
        }
        if(calc(l) == n) printf("%lld\n", (LL)l * p);
        else {
            l ++;
            if(calc(l) == n) printf("%lld\n", (LL)l * p);
            else printf("0\n");
        }
    }
}

int main()
{
    read();
    solve();

    return 0;
}
