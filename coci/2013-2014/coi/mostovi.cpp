#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <string.h>
#include <vector>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1000000 + 10;

int n, m;
set<int> up;
set<int> down;

set< PII > bridgesUp;
set< PII > bridgesDown;

void addEdge(int a, int b) {
	if(a > n) a ^= b ^= a ^= b;
	bridgesUp.insert(mp(a, b));
	bridgesDown.insert(mp(b, a));
}

void removeEdge(int a, int b) {
	if(a <= n) up.insert(min(a, b));
	else down.insert(max(a, b));
}

bool check(int source, int sink) {
	if(source == sink) return true;
	
	if(source <= n && sink <= n && source < sink) {
		set<int> :: iterator it = up.lower_bound(source);
		return (it == up.end() || *it >= sink);
	}
	
	if(source > n && sink > n && source > sink) {
		set<int> :: iterator it = down.upper_bound(sink);
		return (it == down.end() || *it > source);
	}
	
	if(source <= n && sink <= n && source > sink) {
		if(bridgesUp.empty()) return false;
		
		set< PII > :: iterator it1 = bridgesUp.lower_bound(mp(source, -1));
		set< PII > :: iterator it2 = bridgesUp.upper_bound(mp(sink + 1, -1));
		
		if(it2 == bridgesUp.begin() || it1 == bridgesUp.end()) return false;
		
		it2 --;
		return check(source, it1->first) && check(it1->second, it2->second) && check(it2->first, sink);
	}
	
	if(source > n && sink > n && source < sink) {
		if(bridgesDown.empty()) return false;
		
		set< PII > :: iterator it1 = bridgesDown.upper_bound(mp(source + 1, -1));
		set< PII > :: iterator it2 = bridgesDown.lower_bound(mp(sink, -1));
		
		if(it1 == bridgesDown.begin() || it2 == bridgesDown.end()) return false;
		
		it1 --;
		return check(source, it1->first) && check(it1->second, it2->second) && check(it2->first, sink);
	}
	
	if(source <= n && sink > n) {
		if(bridgesDown.empty()) return false;
		
		set< PII > :: iterator it = bridgesDown.lower_bound(mp(sink, -1));
		if(it == bridgesDown.end()) return false;
		
		if(it->second >= source) return check(source, it->second) && check(it->first, sink);
		
		it = bridgesUp.lower_bound(mp(source, -1));
		if(it == bridgesUp.end()) return false;
		
		return check(source, it->first) && check(it->second, sink);
	}
	
	if(source > n && sink <= n) {
		if(bridgesUp.empty()) return false;
		
		set< PII > :: iterator it = bridgesUp.lower_bound(mp(sink + 1, -1));
		
		if(it == bridgesUp.begin()) return false;
		
		it --;
		
		if(it->second <= source) return check(source, it->second) && check(it->first, sink);
		
		it = bridgesDown.lower_bound(mp(source + 1, -1));
		
		if(it == bridgesDown.begin()) return false;
		
		it --;
		return check(source, it->first) && check(it->second, sink);
	}
	
	return false;
}

int main()
{
	char cmd;
	int a, b;
	
	scanf("%d %d\n", &n, &m);
	
	for( ; m; m --) {
		scanf("%c %d %d\n", &cmd, &a, &b);
		
		if(cmd == 'A') addEdge(a, b);
		else if(cmd == 'B') removeEdge(a, b);
		else {
			if(check(a, b)) printf("DA\n");
			else printf("NE\n");
		}
	}
	
	return 0;
}
