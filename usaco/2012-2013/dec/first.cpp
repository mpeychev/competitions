#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 30005;

struct PII {
    short int c;
    int nextNode;

    PII() {}
    PII(short int _c, int _nextNode): c(_c), nextNode(_nextNode) {}
};

struct node {
    int parent;
    short int upChar;
    vector< PII > nxt;

    int getNextNode(short int kc) {
        for(int i = 0; i < nxt.size(); i ++)
            if(nxt[i].c == kc)
                return nxt[i].nextNode;
        return -1;
    }
};

node createNode(int _parent, short int _upChar) {
    node ret;
    ret.parent = _parent;
    ret.upChar = _upChar;
    return ret;
}

int n;
string str[MAXN];
int endNode[MAXN];

vector< node > trie;
int countNodes;
bool finish[300005];

short int cmp[32][32];
short int col[32];

bool ans[MAXN];
int br;

int add(string s) {
    int len = s.size();
    int curNode = 0;

    for(int i = 0; i < len; i ++) {
        short int nextChar = s[i] - 'a';
        int nextNode = trie[curNode].getNextNode(nextChar);
        if(nextNode == -1) {
            nextNode = countNodes ++;
            trie[curNode].nxt.pb(PII(nextChar, nextNode));
            trie.pb(createNode(curNode, nextChar));
        }
        curNode = nextNode;
    }

    finish[curNode] = true;
    return curNode;
}

void read() {
    trie.pb(createNode(-1, -1));
    countNodes ++;

    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++) {
        cin >> str[i];
        endNode[i] = add(str[i]);
    }
}

bool dfs(int cur) {
    col[cur] = 1;
    for(int i = 0; i < 26; i ++)
        if(cmp[cur][i]) {
            if(col[i] == 1) return true;
            if(!col[i] && dfs(i))
                return true;
        }
    col[cur] = 2;
    return false;
}

bool cycle() {
    memset(col, 0, sizeof(col));

    for(int i = 0; i < 26; i ++)
        if(!col[i] && dfs(i))
            return true;

    return false;
}

bool check(int curNode) {
    memset(cmp, 0, sizeof(cmp));

    int nodeUp;
    short int ch;

    while(1) {
        nodeUp = trie[curNode].parent;
        if(nodeUp == -1) break;

        if(finish[nodeUp]) return false;

        ch = trie[curNode].upChar;
        for(int i = 0; i < trie[nodeUp].nxt.size(); i ++) {
            short int tmpCh = trie[nodeUp].nxt[i].c;
            if(ch == tmpCh) continue;
            cmp[ch][tmpCh] = 1;
//            cout << (char)(ch + 'a') << " " << (char)(tmpCh + 'a') << endl;
        }

        curNode = nodeUp;
    }
//    cout << endl;

    return !cycle();
}

void solve() {
    for(int i = 0; i < n; i ++)
        if(check(endNode[i])) {
            br ++;
            ans[i] = true;
        }
}

void write() {
    printf("%d\n", br);
    for(int i = 0; i < n; i ++)
        if(ans[i])
            cout << str[i] << "\n";
}

int main()
{
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);

    read();
    solve();
    write();

    return 0;
}
