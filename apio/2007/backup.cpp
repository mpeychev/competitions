#include <iostream>
#include <stdio.h>
#include <set>

#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef pair< LL , PII > PLII;

const int MAXN = 100100;

int n, k;
LL s[MAXN];
set< PLII > st;
int ple[MAXN], pri[MAXN];
LL cle[MAXN], cri[MAXN];
LL ans;

void read() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%lld", &s[i]);
}

void solve() {
	ple[1] = -1;
	for(int i = 2; i <= n; i ++) {
		ple[i] = i - 1;
		cle[i] = s[i] - s[i - 1];
	}
	
	pri[n] = -1;
	for(int i = n - 1; i >= 1; i --) {
		pri[i] = i + 1;
		cri[i] = s[i + 1] - s[i];
	}
	
	for(int i = 1; i < n; i ++)
		st.insert(mp(cri[i], mp(i, i + 1)));
	
	for(int i = 0; i < k; i ++) {
		set< PLII > :: iterator it = st.begin();
		LL cost = (*it).first;
		int left = (*it).second.first;
		int right = (*it).second.second;
		st.erase(mp(cost, mp(left, right)));
		
		ans += cost;
		
		if(st.empty()) break;
		
		int cnt = 0;
		int newLeft, newRight;
		LL newCost;
		
		if(ple[left] != -1) {
			newLeft = ple[left];
			pri[newLeft] = -1;
			st.erase(mp(cle[left], mp(newLeft, left)));
			cnt ++;
		}
		
		if(pri[right] != -1) {
			newRight = pri[right];
			ple[newRight] = -1;
			st.erase(mp(cri[right], mp(right, newRight)));
			cnt ++;
		}
		
		if(cnt == 2) {
			newCost = cle[left] + cri[right] - cost;
			st.insert(mp(newCost, mp(newLeft, newRight)));
			pri[newLeft] = newRight; cri[newLeft] = newCost;
			ple[newRight] = newLeft; cle[newRight] = newCost;
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
