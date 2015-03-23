#include <iostream>
#include <stdio.h>
#include <set>

#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

const int MAXN = 34567 + 10;

int n, t;
int a[MAXN];
LL ps[MAXN];
LL dp[MAXN];
set< PLL > st;
set< PLL > :: iterator i1, i2;

void read() {
	scanf("%d %d", &n, &t);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		ps[i] = ps[i - 1] + a[i];
	}
}

void solve() {
	st.insert(mp(0, 0));
	for(LL i = 1; i <= n; i ++) {
		for(i1 = st.begin(); i1 != st.end(); i1 ++) {
			if(i1 == st.begin()) continue;
			while(1) {
				if(i1 == st.begin()) break;
				i2 = i1;
				i2 --;
				if(i2->first * i + i2->second > i1->first * i + i1->second) break;
				st.erase(i2);
			}
		}
		i1 = st.begin();
		dp[i] = i1->first * i + i1->second + ps[i] * i - t;
		st.insert(mp(-ps[i], dp[i]));
	}
	cout << dp[n] << endl;
}

int main()
{
	read();
	solve();
	
	return 0;
}
