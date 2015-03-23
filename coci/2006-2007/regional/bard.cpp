#include <iostream>
#include <stdio.h>
#include <bitset>
#include <vector>

#define pb push_back

using namespace std;

int n, e, k, songs;
bitset<64> s[128];

int main()
{
    scanf("%d", &n);
    scanf("%d", &e);
    for( ; e; e --) {
        scanf("%d", &k);

        vector<int> vec(k);
        bool fl = false;
        for(int i = 0; i < k; i ++) {
            scanf("%d", &vec[i]);
            if(vec[i] == 1) fl = true;
        }

        if(fl) {
            for(int i = 0; i < k; i ++)
                s[ vec[i] ][songs] = true;
            songs ++;
        }
        else {
            bitset<64> all;
            for(int i = 0; i < k; i ++)
                all |= s[ vec[i] ];
            for(int i = 0; i < k; i ++)
                s[ vec[i] ] = all;
        }
    }

    for(int i = 1; i <= n; i ++)
        if(s[i].count() == songs)
            printf("%d\n", i);

    return 0;
}
