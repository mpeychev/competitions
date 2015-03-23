#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back

using namespace std;

typedef vector<int> vi;

const int MAXN = 1 << 15;

int n;
int tree[MAXN];

vi f(vi vec) {
    if(vec.size() == 1)
        return vec;

    vi vec1, vec2, ret1, ret2;
    for(int i = 0; i < vec.size(); i ++)
        if(i % 2 == 0) vec1.pb(vec[i]);
        else vec2.pb(vec[i]);

    ret1 = f(vec1);
    ret2 = f(vec2);

    for(int i = 0; i < ret2.size(); i ++)
        ret1.pb(ret2[i]);

    return ret1;
}

void write(int idx) {
    printf("%d", tree[idx]);

    if(idx == (1 << n) - 1) printf("\n");
    else printf(" ");

    if(2 * idx < (1 << n)) {
        write(2 * idx);
        write(2 * idx + 1);
    }
}

int main()
{
    cin >> n;

    if(n == 1) {
        cout << "1\n";
        return 0;
    }

    tree[1] = (1 << n) - 1;

    vi vec;
    for(int i = 1; i <= 1 << (n - 2); i ++)
        vec.pb(i);

    vec = f(vec);

    int r = 1 << (n - 2);
    for(int i = 0, j = 1 << (n - 1); i < vec.size(); i ++, j += 2) {
        tree[j] = vec[i];
        tree[j + 1] = tree[j] + r;
    }

    if(n == 2) {
        write(1);
        return 0;
    }

    int mx = tree[1] - 1, idx = 2;
    for(int i = 1; i <= n - 2; i ++) {
        vector<int> even, odd;
        for(int j = mx; j > mx - (1 << i); j --)
            if(j & 1) odd.pb(j);
            else even.pb(j);

        even = f(even);
        odd = f(odd);

        for(int j = 0; j < even.size(); j ++)
            tree[idx ++] = even[j];

        for(int j = 0; j < odd.size(); j ++)
            tree[idx ++] = odd[j];

        mx -= (1 << i);
    }

    write(1);

    return 0;
}
