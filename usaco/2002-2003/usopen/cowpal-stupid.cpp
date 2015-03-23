/// Potentially better results

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 3010;

int n, group[MAXN];
int mx, cnt[MAXN];
vector<int> target;
int queriesCount;

void init() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		scanf("%d", &group[i]);
		mx = max(mx, group[i]);
		cnt[ group[i] ] ++;
	}
	
	for(int i = 0; i <= mx; i ++)
		if(cnt[i])
			target.pb(cnt[i]);
	
	sort(target.begin(), target.end());
}

string query(string q) {
	queriesCount ++;
	
	if((int)q.size() != n) {
		printf("invalid question size\n");
		exit(0);
	}
	
	for(int i = 0; i < n; i ++)
		if(q[i] != '0' && q[i] != '1') {
			printf("invalid question format\n");
			exit(0);
		}
	
	string ret;
	ret.resize(n, '0');
	
	set<int> st;
	for(int i = 0; i < (int)q.size(); i ++)
		if(q[i] == '1')
			st.insert(group[i]);
	
	for(int i = 0; i < n; i ++)
		if(st.find(group[i]) != st.end())
			ret[i] = '1';
	
	return ret;
}

vector<int> ans;

void solution() {
	sort(ans.begin(), ans.end());
	
	if(target == ans) {
		cout << "ok\n";
		cout << "cows " << n << endl;
		cout << "queries " << queriesCount << endl;
		return;
	}
	
	cout << "wa\n";
	cout << "real solution: ";
	for(int i = 0; i < target.size(); i ++)
		cout << target[i] << " ";
	cout << endl;
	cout << "your solution: ";
	for(int i = 0; i < ans.size(); i ++)
		cout << ans[i] << " ";
	cout << endl;
}

bool used[MAXN];

void solve() {
	string str (n, '0');
	for(int i = 0; i < n; i ++)
		if(!used[i]) {
			str[i] = '1';
			string a = query(str);
			str[i] = '0';
			
			int cnt = 0;
			for(int j = 0; j < n; j ++)
				if(a[j] == '1') {
					used[j] = true;
					cnt ++;
				}
			ans.pb(cnt);
		}
	
	solution();
}

int main()
{
	init();
	solve();

    return 0;
}
