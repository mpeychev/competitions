#include <iostream>
#include <stdio.h>

using namespace std;

typedef long long LL;

LL ans;
int cnt[64];

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

int main()
{
    LL a, b;
    cin >> a >> b;
    for(LL i = a; i <= b; i ++)
        ans += strength(i);
/*
    for(int i = 2; i <= 10; i ++)
        cout << i << " " << cnt[i] << endl;
*/
    cout << ans << endl;

    return 0;
}
