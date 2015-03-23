#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
#include <string>

#define mp make_pair
#define pb push_back

using namespace std;

struct Node {
	bool isTerminal;
	map<int, int> cache;
	int nxt[32];
};

int k, c, d;
char cows[32][8];
char word[16];
int cowLens[32];

Node trie[1 << 11];
int nodesCount;

string seq;

void addWord() {
	int l = strlen(word);
	int curNode = 0;
	for(int i = 0; i < l; i ++) {
		int ch = word[i] - 'A';
		if(trie[curNode].nxt[ch] == -1) {
			trie[curNode].nxt[ch] = nodesCount;
			memset(trie[nodesCount].nxt, -1, sizeof(trie[nodesCount].nxt));
			nodesCount ++;
		}
		
		curNode = trie[curNode].nxt[ch];
	}
	trie[curNode].isTerminal = true;
}

void init() {
	memset(trie[nodesCount].nxt, -1, sizeof(trie[nodesCount].nxt));
	nodesCount ++;
	
	scanf("%d %d %d\n", &k, &c, &d);
	for(int i = 0; i < c; i ++)
		scanf("%s", &cows[i]);
	
	for(int i = 0; i < c; i ++)
		for(int j = i + 1; j < c; j ++)
			if(strcmp(cows[i], cows[j]) > 0)
				swap(cows[i], cows[j]);
	
	for(int i = 0; i < c; i ++)
		cowLens[i] = strlen(cows[i]);
	
	for(int i = 0; i < d; i ++) {
		scanf("%s", &word);
		addWord();
	}
}

int go(int node, int mask);

int step(int node, int cow, int pos, int mask) {
	if(pos == cowLens[cow])
		return go(node, mask | (1 << cow));
	
	int ch = cows[cow][pos] - 'A';
	int ret = 0;
	
	if(trie[node].nxt[ch] != -1)
		ret += step(trie[node].nxt[ch], cow, pos + 1, mask);
	
	if(trie[node].isTerminal)
		ret += step(0, cow, pos, mask);
	
	return ret;
}

int go(int node, int mask) {
	if(trie[node].cache.find(mask) != trie[node].cache.end())
		return trie[node].cache[mask];
	
	int ret;
	
	if(mask == (1 << c) - 1) {
		ret = 0;
		if(node == 0 || trie[node].isTerminal) ret = 1;
		trie[node].cache.insert(mp(mask, ret));
		return ret;
	}
	
	ret = 0;
	for(int i = 0; i < c; i ++)
		if(!((mask >> i) & 1))
			ret += step(node, i, 0, mask);
	
	trie[node].cache.insert(mp(mask, ret));
	return ret;
}

bool findSmallest(int node, int mask);

bool step2(int node, int cow, int pos, int mask) {
	if(pos == cowLens[cow])
		return findSmallest(node, mask | (1 << cow));
	
	int ch = cows[cow][pos] - 'A';
	
	if(trie[node].isTerminal) {
		if(step2(0, cow, pos, mask)) {
			seq.pb(' ');
			return true;
		}
	}
	
	if(trie[node].nxt[ch] != -1) {
		if(step2(trie[node].nxt[ch], cow, pos + 1, mask)) {
			seq.pb(cows[cow][pos]);
			return true;
		}
	}
	
	return false;
}

bool findSmallest(int node, int mask) {
	if(mask == (1 << c) - 1)
		return (node == 0 || trie[node].isTerminal);
	
	for(int i = 0; i < c; i ++)
		if(!((mask >> i) & 1))
			if(step2(node, i, 0, mask))
				return true;
	
	return false;
}

void solve() {
	int ans = go(0, 0);
	
	if(!ans) {
		cout << "NOSOLUTIONS\n";
		return;
	}
	
	findSmallest(0, 0);
	reverse(seq.begin(), seq.end());
	
	cout << seq << endl;
	cout << ans << endl;
}

int main()
{
	init();
	solve();

    return 0;
}
