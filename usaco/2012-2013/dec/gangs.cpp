#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
#include <string.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXM = 1 << 7;

int n, m;
int cnt[MAXM], cpy[MAXM];
int x;
vector<int> ans;

struct cmp {
    bool operator()(PII g1, PII g2) {
        if(g1.first > g2.first) return true;
        if(g1.first < g2.first) return false;
        return g1.second > g2.second;
    }
};

set< PII > active;
set< PII, cmp > st;

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i ++)
        cin >> cnt[i];
}

bool check() {
    int sum = 0, mx = 0;
    for(int i = 1; i <= m; i ++) {
        sum += cpy[i];
        if(mx < cpy[i]) mx = cpy[i];
    }

    return (sum % 2 == 0 && sum / 2 >= mx);
}

int getMax(int gangNumber) {
    set< PII, cmp > :: iterator it2;
    it2 = st.begin();
    if((*it2).second == gangNumber) return (*it2).first - 1;
    return (*it2).first;
}

void solve() {
    if(m == 1) {
        printf("YES\n");
        printf("%d\n", n);
        for(int i = 0; i < n; i ++)
            printf("1\n");
        return;
    }

    for(int i = cnt[1]; i >= 1; i --) {
        memcpy(cpy, cnt, sizeof(cnt));
        cpy[1] -= i;
        if(check()) {
            x = i;
            break;
        }
    }

    if(!x) {
        printf("NO\n");
        return;
    }

    printf("YES\n");
    printf("%d\n", x);

    int tmp = 0, curS = 0;

    if(cnt[1] - x > 0) {
        curS = cnt[1] - x;
        active.insert(mp(1, cnt[1] - x));
        st.insert(mp(cnt[1] - x, 1));
    }

    for(int i = 2; i <= m; i ++) {
        curS += cnt[i];
        active.insert(mp(i, cnt[i]));
        st.insert(mp(cnt[i], i));
    }

    while(!active.empty()) {
        set< PII > :: iterator it;

        if(tmp == 0) {
            it = active.begin();
            PII p = *it;
            tmp = p.second;
            for(int i = 0; i < p.second; i ++)
                ans.pb(p.first);
            active.erase(p);
            st.erase(mp(p.second, p.first));
            curS -= p.second;
        }
        else {
            curS --;
            tmp --;
            int s2 = tmp + curS;

            for(it = active.begin(); it != active.end(); it ++) {
                int gangNumber = (*it).first;
                int count = (*it).second;

                if(s2 / 2 >= getMax(gangNumber)) {
                    ans.pb(gangNumber);

                    PII p = mp(count, gangNumber);
                    st.erase(p);

                    if(count > 1) {
                        p = mp(count - 1, gangNumber);
                        st.insert(p);
                    }

                    p = mp(gangNumber, count);
                    active.erase(it);

                    if(p.second > 1) {
                        p.second --;
                        active.insert(p);
                    }

                    break;
                }
            }
        }
    }

    int ones = 0;
    for(int i = 0; i < ans.size(); i ++)
        if(ans[i] != 1) break;
        else ones ++;

    if(ones * 2 == ans.size()) {
        for(int i = 0; i < x; i ++)
            printf("1\n");
        for(int i = 0; i < ans.size(); i ++)
            printf("%d\n", ans[i]);
    }
    else {
        for(int i = 0; i < ans.size(); i ++)
            printf("%d\n", ans[i]);
        for(int i = 0; i < x; i ++)
            printf("1\n");
    }
}

int main()
{
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);

    read();
    solve();

    return 0;
}
