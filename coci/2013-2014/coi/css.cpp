#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <string>
#include <vector>
#include <set>

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair< LL, LL > PLL;

const LL prime1 = 1583497LL;
const LL prime2 = 3963277LL;

const LL MOD1 = 1235394889LL;
const LL MOD2 = 2837536591LL;

PLL hash(string &str) {
	PLL ret = mp(0, 0);
	for(int i = 0; i < (int)str.size(); i ++) {
		ret.first = (ret.first * prime1 + (str[i] - 'a') + 1) % MOD1;
		ret.second = (ret.second * prime2 + (str[i] - 'a') + 1) % MOD2;
	}
	return ret;
}

struct Node {
	int index, parent;
	string name;
	vector< string > c;
	set< PLL > h;
	
	Node() {}
	Node(int _index, int _parent): index(_index), parent(_parent) {}
	
	void calcH() {
		for(int i = 0; i < (int)c.size(); i ++)
			h.insert(hash(c[i]));
	}
};

int n, m;
char s[5050];

int cntNodes;
stack<int> st;
vector< Node > g;

void read() {
	scanf("%d\n", &n);
	
	g.pb(Node(0, -1));
	st.push(0);
	cntNodes ++;
	
	for(int i = 0; i < n; i ++) {
		gets(s);
		if(s[1] == '/') st.pop();
		else {
			g.pb(Node(cntNodes, st.top()));
			st.push(cntNodes);
			
			int len = strlen(s);
			int endName = -1;
			
			for(int j = 9; j < len; j ++) {
				if(s[j] == '\'') {
					endName = j;
					break;
				}
				g[cntNodes].name.pb(s[j]);
			}
			
			string tmp;
			for(int j = endName + 9; j < len; j ++)
				if(s[j] == ' ' || s[j] == '\'') {
					g[cntNodes].c.pb(tmp);
					tmp.clear();
					if(s[j] == '\'') break;
				}
				else tmp.pb(s[j]);
			
			cntNodes ++;
		}
	}
}

vector< string > vec;
vector< bool > fl;
vector< vector< PLL > > ha;

short int cache[5050][2525];
short int ok[5050][2525];

short int checkSets(int nodeIndex, int pos) {
	if(ok[nodeIndex][pos] != -1)
		return ok[nodeIndex][pos];
	
	ok[nodeIndex][pos] = 1;
	for(int i = 0; i < (int)ha[pos].size(); i ++)
		if(g[nodeIndex].h.find( ha[pos][i] ) == g[nodeIndex].h.end()) {
			ok[nodeIndex][pos] = 0;
			break;
		}
	return ok[nodeIndex][pos];
}

short int check(int nodeIndex, int pos) {
	short int &ret = cache[nodeIndex][pos];
	
	if(ret != -1)
		return ret;
	
	if(nodeIndex == 0) {
		ret = 0;
		return ret;
	}
	
	if(fl[pos]) {
		if(!checkSets(nodeIndex, pos)) {
			ret = 0;
			return ret;
		}
		if(pos == 0) {
			ret = 1;
			return ret;
		}
		if(!check(g[nodeIndex].parent, pos - 1)) {
			ret = 0;
			return ret;
		}
		
		ret = 1;
		return ret;
	}
	
	if(pos == 0) {
		if(checkSets(nodeIndex, pos)) {
			ret = 1;
			return ret;
		}
		ret = check(g[nodeIndex].parent, pos);
		return ret;
	}
	
	if(checkSets(nodeIndex, pos) && check(g[nodeIndex].parent, pos - 1)) {
		ret = 1;
		return ret;
	}
	
	if(check(g[nodeIndex].parent, pos)) {
		ret = 1;
		return ret;
	}
	
	ret = 0;
	return ret;
}

void go() {
	vec.clear();
	fl.clear();
	ha.clear();
	
	int len = strlen(s);
	
	string tmp;
	for(int i = 0; i < len; i ++)
		if(s[i] == ' ') {
			vec.pb(tmp);
			tmp.clear();
			
			if(s[i + 1] == '>') {
				fl.pb(true);
				i += 2;
			}
			else fl.pb(false);
		}
		else tmp.pb(s[i]);
	
	vec.pb(tmp);
	fl.pb(true);
	
	ha.resize(vec.size());
	for(int i = 0; i < (int)vec.size(); i ++) {
		tmp.clear();
		for(int j = 1; j < (int)vec[i].size(); j ++)
			if(vec[i][j] == '.') {
				ha[i].pb(hash(tmp));
				tmp.clear();
			}
			else tmp.pb(vec[i][j]);
		ha[i].pb(hash(tmp));
	}
	
	vector< string > ans;
	
	memset(cache, -1, sizeof(cache));
	memset(ok, -1, sizeof(ok));
	for(int i = 1; i < cntNodes; i ++)
		if(check(i, ha.size() - 1))
			ans.pb(g[i].name);
	
	printf("%d", ans.size());
	for(int i = 0; i < (int)ans.size(); i ++)
		printf(" %s", ans[i].c_str());
	printf("\n");
}

void solve() {
	for(int i = 1; i < cntNodes; i ++)
		g[i].calcH();

	scanf("%d\n", &m);
	for(int i = 0; i < m; i ++) {
		gets(s);
		go();
	}
}

int main()
{
	read();
	solve();

    return 0;
}
