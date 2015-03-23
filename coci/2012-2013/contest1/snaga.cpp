#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

LL find(LL x) {
    for(int i = 1; ; i ++)
        if(x % i)
            return i;
}

LL strength(LL x) {
    LL ret = 1;
    while(x != 2) {
        x = find(x);
        ret ++;
    }
    return ret;
}

LL gcd(LL a, LL b) {
    while(b) {
        LL r = a % b;
        a = b; b = r;
    }
    return a;
}

LL nok(LL a, LL b) {
    return (a * b) / gcd(a, b);
}

LL get(LL x) {
    LL cnt[64];
    memset(cnt, 0, sizeof(cnt));

    cnt[2] = x / 2 - (x % 2 == 0);

    LL t = x / 2;
    LL br = t / 3;
    cnt[3] = t - 1 - br;

    LL countNumbers = cnt[2] + cnt[3];
    LL n = 6;

    int last = 3;

    for(int i = 4; countNumbers < x - 2; i ++) {
        LL prvNok = n;
        t = x / n;
        n = nok(n, i);

        LL div = n / prvNok;
        cnt[i] = t - t / div;

        countNumbers += cnt[i];
        last = i;
    }

    LL ret = 0;
    for(int i = 2; i <= last; i ++)
        ret += cnt[i] * (strength(i) + 1);
/*
    for(int i = 2; i <= last; i ++)
        cout << i << " " << cnt[i] << "\n";
    cout << ret << endl;
    cout << endl;
*/
    return ret;
}

LL solve(LL a, LL b) {
    return get(b) - get(a - 1);
}

int main()
{
    LL a, b;
    cin >> a >> b;

    LL ans = 0;

    while(a < 100) {
        ans += strength(a);
//        cout << a << ": " << strength(a) << "\n";
        a ++;
        if(a > b) {
            cout << ans << endl;
            return 0;
        }
    }

    ans += solve(a, b);

    cout << ans << endl;

    return 0;
}
