#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1 << 5;
const int MAXK = 1 << 10;

struct Node {
	int nxt[4];
	int score;
	short int prev_node;
	short int prev_char;
	int dp[MAXK];
	bool terminal;
	int suffFunc;
	int nextFunc[4];
	
	void init() {
		memset(nxt, -1, sizeof(nxt));
		score = -1;
		prev_node = -1;
		prev_char = -1;
		memset(dp, -1, sizeof(dp));
		terminal = false;
		suffFunc = -1;
		memset(nextFunc, -1, sizeof(nextFunc));
	}
};

int n, k;
Node trie[305];
int cntNodes;
char s[32];

void initTrie() {
	for(int i = 0; i <= 300; i ++)
		trie[i].init();
}

void addWord() {
	int len = strlen(s);
	int curNode = 0;
	for(int i = 0; i < len; i ++) {
		int ch = s[i] - 'A';
		if(trie[curNode].nxt[ch] != -1) curNode = trie[curNode].nxt[ch];
		else {
			cntNodes ++;
			trie[curNode].nxt[ch] = cntNodes;
			trie[cntNodes].prev_node = curNode;
			trie[cntNodes].prev_char = ch;
			curNode = cntNodes;
		}
	}
	trie[curNode].terminal = true;
}

void buildTrie() {
	scanf("%d %d\n", &n, &k);
	for(int i = 0; i < n; i ++) {
		scanf("%s", &s);
		addWord();
	}
}

int getScore(int node);
int getSuff(int node);
int getNext(int node, int ch);

int getNext(int node, int ch) {
	int &ret = trie[node].nextFunc[ch];
	
	if(ret != -1)
		return ret;
	
	if(trie[node].nxt[ch] != -1) {
		ret = trie[node].nxt[ch];
		return ret;
	}
	
	if(node == 0) {
		ret = 0;
		return ret;
	}
	
	ret = getNext(getSuff(node), ch);
	return ret;
}

int getSuff(int node) {
	int &ret = trie[node].suffFunc;
	
	if(ret != -1)
		return ret;
	
	if(node == 0 || trie[node].prev_node == 0) {
		ret = 0;
		return ret;
	}
	
	ret = getNext(getSuff(trie[node].prev_node), trie[node].prev_char);
	return ret;
}

int getScore(int node) {
	int &ret = trie[node].score;
	
	if(ret != -1)
		return ret;
	
	if(node == 0) {
		ret = 0;
		return ret;
	}
	
	if(trie[node].terminal) ret = 1;
	else ret = 0;
	
	ret += getScore(getSuff(node));
	return ret;
}

int go(int node, int pos) {
	int &ret = trie[node].dp[pos];
	
	if(ret != -1)
		return ret;
	
	ret = getScore(node);
	
	if(pos == k)
		return ret;
	
	int mx = 0;
	for(int i = 0; i < 3; i ++) {
		int tmp = go(getNext(node, i), pos + 1);
		if(mx < tmp) mx = tmp;
	}
	
	ret += mx;
	return ret;
}

int main()
{
	initTrie();
	buildTrie();
	cout << go(0, 0) << endl;

    return 0;
}
