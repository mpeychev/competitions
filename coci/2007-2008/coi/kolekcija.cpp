#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXM = 300300;
const int INF = 2000000000;

struct Node {
	int minValue;
	int optj;
	
	Node() {}
	Node(int _minValue, int _optj): minValue(_minValue), optj(_optj) {}
};

int n, k, m;
int inp[MAXM];
int p[MAXM];

vector< PII > vec;

int dp[MAXM];
int lvs;
Node tree[1 << 20];

int jump[MAXM];
bool opt[MAXM];

void read() {
	scanf("%d %d", &n, &k);
	scanf("%d", &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d", &inp[i]);
		p[i] = inp[i];
	}
}

void initTree(int node) {
	if(node >= lvs)
		return;
	
	initTree(node << 1);
	initTree((node << 1) + 1);
	
	if(tree[node << 1].minValue <= tree[(node << 1) + 1].minValue) tree[node] = tree[node << 1];
	else tree[node] = tree[(node << 1) + 1];
}

void update(int i, int val) {
	int idx = i + lvs;
	tree[idx].minValue = val;
	idx >>= 1;
	while(idx) {
		if(tree[idx].minValue > val) tree[idx] = Node(val, i);
		idx >>= 1;
	}
}

Node getRMQ(int node, int le, int ri, int a, int b) {
	if(ri < a || b < le)
		return Node(INF, -1);
	
	if(a <= le && ri <= b)
		return tree[node];
	
	int mid = (le + ri) >> 1;
	Node leftAnswer = getRMQ(node << 1, le, mid, a, b);
	Node rightAnswer = getRMQ((node << 1) + 1, mid + 1, ri, a, b);
	
	if(leftAnswer.minValue <= rightAnswer.minValue) return leftAnswer;
	return rightAnswer;
}

int bs(int i) {
	int le = i + 1, ri = m - 1, mid;
	int ret = m;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(p[i] + k <= p[mid]) {
			ret = mid;
			ri = mid - 1;
		}
		else le = mid + 1;
	}
	return ret;
}

void fillAll(int le, int ri) {
	int curPos = le;
	while(1) {
		if(curPos + k - 1 < ri) {
			vec.pb(mp(curPos, curPos + k - 1));
			curPos += k;
		}
		else {
			vec.pb(mp(ri - k + 1, ri));
			break;
		}
	}
}

void solve() {
	sort(p, p + m);
	
	if(p[m - 1] - p[0] <= k) {
		if(p[0] + k - 1 <= n) vec.pb(mp(p[0], p[0] + k - 1));
		else vec.pb(mp(n - k + 1, n));
		
		return;
	}
	
	lvs = 1;
	while(lvs <= m) lvs <<= 1;
	
	for(int i = 0; i < lvs; i ++)
		tree[i + lvs] = Node(INF, i);
	
	initTree(1);
	
	dp[m] = 0;
	for(int i = m - 1; i >= 0; i --) {
		int opt1 = INF, opt2 = INF;
		
		int start = bs(i);
		opt1 = k + dp[start];
		
		Node rmq = Node(INF, -1);
		if(start != m) {
			rmq = getRMQ(1, 0, lvs - 1, start, m - 1);
			opt2 = rmq.minValue - p[i];
		}
		
		if(opt1 <= opt2) {
			dp[i] = opt1;
			jump[i] = start;
		}
		else {
			dp[i] = opt2;
			opt[i] = true;
			jump[i] = rmq.optj + 1;
		}
		
		update(i, dp[i + 1] + p[i] + 1);
	}
	
	int curPos = 0;
	while(curPos < m) {
		if(!opt[curPos]) {
			if(p[curPos] + k - 1 <= n) vec.pb(mp(p[curPos], p[curPos] + k - 1));
			else vec.pb(mp(n - k + 1, n));
		}
		else fillAll(p[curPos], p[ jump[curPos] - 1 ]);
		
		curPos = jump[curPos];
	}
}

void findAnswer(int x) {
	int le = 0, ri = (int)vec.size() - 1, mid;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(x < vec[mid].first) ri = mid - 1;
		else {
			if(x <= vec[mid].second) {
				printf("%d %d\n", vec[mid].first, vec[mid].second);
				return;
			}
			le = mid + 1;
		}
	}
}

void write() {
	printf("%d\n", dp[0]);
	
	for(int i = 0; i < m; i ++)
		findAnswer(inp[i]);
}

int main()
{
	read();
	solve();
	write();

    return 0;
}
