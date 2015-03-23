#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const LL INF = 1000000000LL;

LL n, p;
bool pr[100100];
// 0 - prime
// 1 - not prime
vector<int> vec;

void erato() {
    pr[0] = 1;
    pr[1] = 1;
    for(LL i = 2; i <= 100000; i ++)
        if(!pr[i])
            for(LL j = i * i; j <= 100000LL; j += i)
                pr[j] = 1;
}

bool check(int x) {
    for(int i = 0; i < vec.size() && vec[i] * vec[i] <= x; i ++)
        if(x % vec[i] == 0)
            return false;
    return true;
}

int main()
{
    erato();

    cin >> n >> p;

    if(p > 1000) {

        if(n == 1) {
            printf("%lld\n", p);
            return 0;
        }

        n --;
        for(int i = p; i <= INF / p; i ++)
            if(!pr[i]) {
                n --;
                if(!n) {
                    printf("%lld\n", p * i);
                    return 0;
                }
            }

        printf("0\n");
        return 0;
    }

    for(int i = 2; i < p; i ++)
        if(!pr[i])
            vec.pb(i);

    for(int i = p; i <= 100000;  i += p)
        if(check(i)) {
            n --;
            if(!n) {
                printf("%d\n", i);
                return 0;
            }
        }
    printf("0\n");

    return 0;
}
