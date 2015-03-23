#include <iostream>
#include <stdio.h>
#include <bitset>
#include <vector>
#include <time.h>
#include <stdlib.h>

#define mp make_pair
#define pb push_back

using namespace std;

const int MAXN = 30005;

typedef vector<int> vi;

struct Node {
	int number;
	int priority;
	int treeSize;
	bitset<MAXN> allNums;
	Node *left, *right;
};

typedef Node* PNode;

PNode T[MAXN];
vi groups[MAXN];
int inGroup[MAXN];

PNode createNode(int num) {
	PNode ret = new Node;
	ret -> number = num;
	ret -> priority = (rand() << 15) | rand();
	ret -> treeSize = 1;
	ret -> allNums[num] = true;
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

void printTreap(PNode t) {
	if(!t) return;
	printTreap(t -> left);
	cout << t -> number << " ";
	printTreap(t -> right);
}

int getSize(PNode t) {
	if(!t) return 0;
	return t -> treeSize;
}

bitset<MAXN> getAllNums(PNode t) {
	if(!t) return 0;
	return t -> allNums;
}

void fix(PNode &t) {
	if(!t) return;
	t -> treeSize = getSize(t -> left) + 1 + getSize(t -> right);
	t -> allNums = getAllNums(t -> left) | getAllNums(t -> right);
	t -> allNums[t -> number] = true;
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
	
	if(le -> priority > ri -> priority) {
		merge(le -> right, ri, le -> right);
		t = le;
	}
	else {
		merge(le, ri -> left, ri -> left);
		t = ri;
	}
	
	fix(t);
}

pair<int, bool> find(PNode t, int target) {
	if(!t) return mp(0, false);
	
	if(t -> allNums[target] == false)
		return mp(t -> treeSize, false);
	
	pair<int, bool> tmp = find(t -> right, target);
	if(tmp.second) return tmp;
	
	if(t -> number == target) {
		tmp.second = true;
		return tmp;
	}
	
	pair<int, bool> ret = find(t -> left, target);
	ret.first += tmp.first + 1;
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
	}
	else {
		targetGroup = x;
		
		while(!groups[y].empty()) {
			groups[x].pb(groups[y].back());
			inGroup[ groups[y].back() ] = targetGroup;
			groups[y].pop_back();
		}
		
		merge(T[x], T[y], T[x]);
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
			pair<int, bool> ans = find(T[ inGroup[x] ], x);
			printf("%d\n", ans.first);
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
