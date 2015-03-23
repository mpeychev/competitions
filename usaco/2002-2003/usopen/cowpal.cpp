#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <set>

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

void go(string g) {
	string part = g;
	
	int t = 0, bitsCount = 0;
	for(int i = 0; i < n; i ++) {
		t += (g[i] == '1');
		bitsCount += (g[i] == '1');
	}
	
	int index = n;
	bool fl = false;
	for(int k = bitsCount / 2; k; k >>= 1) {
		for(int i = index - 1; i >= 0; i --)
			if(g[i] == '1') {
				part[i] = '0';
				t --;
				
				if(t == k) {
					index = i;
					break;
				}
			}
		
		string a = query(part);
		string b (n, '0');
		if(a != g) {
			for(int i = 0; i < n; i ++)
				if(g[i] == '1' && a[i] == '0')
					b[i] = '1';
			
			fl = true;
			go(a);
			go(b);
			break;
		}
	}
	
	if(!fl) {
		ans.pb(bitsCount);
		return;
	}
}

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

void solve() {
	go(string (n, '1'));
	solution();
}

int main()
{
	init();
	solve();
	
	return 0;
}
