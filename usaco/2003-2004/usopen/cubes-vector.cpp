#include <iostream>
#include <stdio.h>
#include <bitset>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#define mp make_pair
#define pb push_back

using namespace std;

const int MAXN = 30005;

typedef vector<int> vi;

struct Node {
	int number;
	int priority;
	int treeSize;
	vi allNums;
	Node *left, *right;
};

typedef Node* PNode;

PNode T[MAXN];
vi groups[MAXN];
int inGroup[MAXN];
bool found;

PNode createNode(int num) {
	PNode ret = new Node;
	ret -> number = num;
	ret -> priority = (rand() << 15) | rand();
	ret -> treeSize = 1;
	ret -> allNums.pb(num);
	ret -> left = NULL;
	ret -> right = NULL;
	return ret;
}

void init() {
	for(int i = 1; i <= 30000; i ++) {
		T[i] = createNode(i);
		groups[i].pb(i);
		inGroup[i] = i;
	}
}

int getSize(PNode t) {
	if(!t) return 0;
	return t -> treeSize;
}

void fix(PNode &t) {
	if(!t) return;
	t -> treeSize = getSize(t -> left) + 1 + getSize(t -> right);
}

void merge(PNode le, PNode ri, PNode &t) {
	if(!le) {
		t = ri;
		return;
	}
	
	if(!ri) {
		t = le;
		return;
	}
	
	vector<int> vec1, vec2, vec;
	vec1 = le -> allNums;
	vec2 = ri -> allNums;
	int i = 0, j = 0;
	int sz1 = (int)vec1.size();
	int sz2 = (int)vec2.size();
	
	while(i < sz1 || j < sz2) {
		int val1 = MAXN, val2 = MAXN;
		
		if(i < sz1) val1 = vec1[i];
		if(j < sz2) val2 = vec2[j];
		
		if(val1 < val2) {
			vec.pb(val1);
			i ++;
		}
		else {
			vec.pb(val2);
			j ++;
		}
	}
	
	if(le -> priority > ri -> priority) {
		merge(le -> right, ri, le -> right);
		t = le;
		t -> allNums = vec;
	}
	else {
		merge(le, ri -> left, ri -> left);
		t = ri;
		t -> allNums = vec;
	}
	
	fix(t);
}

int find(PNode t, int target) {
	if(!t) return 0;
	
	if(binary_search(t -> allNums.begin(), t -> allNums.end(), target) == false)
		return t -> treeSize;
	
	int tmp = find(t -> right, target);
	if(found) return tmp;
	
	if(t -> number == target) {
		found = true;
		return tmp;
	}
	
	int ret = find(t -> left, target);
	ret += tmp + 1;
	return ret;
}

void update(int x, int y) {
	x = inGroup[x];
	y = inGroup[y];
	
	int targetGroup;
	if((int)groups[x].size() < (int)groups[y].size()) {
		targetGroup = y;
		
		while(!groups[x].empty()) {
			groups[y].pb(groups[x].back());
			inGroup[ groups[x].back() ] = targetGroup;
			groups[x].pop_back();
		}
		
		merge(T[x], T[y], T[y]);
		T[x] = NULL;
	}
	else {
		targetGroup = x;
		
		while(!groups[y].empty()) {
			groups[x].pb(groups[y].back());
			inGroup[ groups[y].back() ] = targetGroup;
			groups[y].pop_back();
		}
		
		merge(T[x], T[y], T[x]);
		T[y] = NULL;
	}
}

void solve() {
	int p, x, y;
	char cmd;
	
	scanf("%d\n", &p);
	for(int i = 0; i < p; i ++) {
		scanf("%c", &cmd);
		
		if(cmd == 'M') {
			scanf("%d %d\n", &x, &y);
			update(x, y);
		}
		else {
			scanf("%d\n", &x);
			found = false;
			printf("%d\n", find(T[ inGroup[x] ], x));
		}
	}
}

int main()
{
	srand(time(NULL));
	
	init();
	solve();

    return 0;
}
