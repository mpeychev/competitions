#include <iostream>
#include <stdio.h>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 300300;

int n;
int b[MAXN];
int ans;
multiset<int> st;
multiset<int> :: iterator it;

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &b[i]);
}

bool cmp(int a, int b) {
    return a > b;
}

void solve() {
    sort(b, b + n, cmp);

    for(int i = 1; i < n; i ++)
        st.insert(b[i] + i);

    for(int i = 0; i < n; i ++) {
        it = st.end();
        it --;
        if(*it <= b[i] + n) ans ++;
        if(i != n - 1) {
            st.erase(b[i + 1] + i + 1);
            st.insert(b[i] + i + 1);
        }
    }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
