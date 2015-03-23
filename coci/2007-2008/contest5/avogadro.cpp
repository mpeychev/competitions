#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

typedef vector<int> vi;

const int MAXN = 100100;

struct triple {
	int a, b, c;
};

int n;
triple vec[MAXN];
unsigned color[MAXN];
int prv[MAXN];
vector< vi > p1, p2;
vector< bool > added1, added2;
int inGroup1[MAXN], inGroup2[MAXN];
vi nums;
bool flag;
bool used[MAXN];

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		scanf("%d", &vec[i].a);
		vec[i].a --;
	}
	for(int i = 0; i < n; i ++) {
		scanf("%d", &vec[i].b);
		vec[i].b --;
	}
	for(int i = 0; i < n; i ++) {
		scanf("%d", &vec[i].c);
		vec[i].c --;
	}
}

bool cmp(triple x, triple y) {
	return x.a < y.a;
}

void dfs1(int cur) {
	color[cur] = 1;
	
	if(color[ vec[cur].b ] == 0) {
		prv[ vec[cur].b ] = cur;
		dfs1(vec[cur].b);
	}
	else if(color[ vec[cur].b ] == 1) {
		vi toAdd;
		int last = vec[cur].b;
		int tmp = cur;
		
		for( ; ; ) {
			toAdd.pb(tmp);
			if(tmp == last) break;
			tmp = prv[tmp];
		}
		
		p1.pb(toAdd);
	}
	
	color[cur] = 2;
}

void dfs2(int cur) {
	color[cur] = 1;
	
	if(color[ vec[cur].c ] == 0) {
		prv[ vec[cur].c ] = cur;
		dfs2(vec[cur].c);
	}
	else if(color[ vec[cur].c ] == 1) {
		vi toAdd;
		int last = vec[cur].c;
		int tmp = cur;
		
		for( ; ; ) {
			toAdd.pb(tmp);
			if(tmp == last) break;
			tmp = prv[tmp];
		}
		
		p2.pb(toAdd);
	}
	
	color[cur] = 2;
}

void go(int cur, int group) {
	if(group == 1 && !used[ inGroup1[cur] ]) {
		nums.pb(inGroup1[cur]);
		used[ inGroup1[cur] ] = true;
	}	
	
	int idx;
	
	if(group == 1) {
		idx = inGroup1[cur];
		added1[ idx ] = true;
		for(int i = 0; i < p1[idx].size(); i ++)
			if(inGroup2[ p1[idx][i] ] == -1) flag = false;
			else if(!added2[ inGroup2[ p1[idx][i] ] ]) go(p1[idx][i], 2);
	}
	else {
		idx = inGroup2[cur];
		added2[ idx ] = true;
		for(int i = 0; i < p2[idx].size(); i ++)
			if(inGroup1[ p2[idx][i] ] == -1) flag = false;
			else if(!added1[ inGroup1[ p2[idx][i] ] ])	go(p2[idx][i], 1);
	}
}

void solve() {
	sort(vec, vec + n, cmp);
	
	memset(prv, -1, sizeof(prv));
	for(int i = 0; i < n; i ++)
		if(!color[i])
			dfs1(i);
	
	memset(color, 0, sizeof(color));
	memset(prv, -1, sizeof(prv));
	for(int i = 0; i < n; i ++)
		if(!color[i])
			dfs2(i);
	
	memset(inGroup1, -1, sizeof(inGroup1));
	for(int i = 0; i < p1.size(); i ++)
		for(int j = 0; j < p1[i].size(); j ++)
			inGroup1[ p1[i][j] ] = i;
	
	memset(inGroup2, -1, sizeof(inGroup2));
	for(int i = 0; i < p2.size(); i ++)
		for(int j = 0; j < p2[i].size(); j ++)
			inGroup2[ p2[i][j] ] = i;
	
	added1.resize((int)p1.size());
	added2.resize((int)p2.size());
	
	int ans = n;
	for(int i = 0; i < n; i ++)
		if(inGroup1[i] != -1 && !added1[ inGroup1[i] ]) {
			nums.clear();
			flag = true;
			go(i, 1);
			
			if(flag) {
				for(int j = 0; j < nums.size(); j ++)
					ans -= (int)p1[ nums[j] ].size();
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
