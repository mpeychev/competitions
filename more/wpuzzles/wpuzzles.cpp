// Aho-Corasick

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int n, m, w;
char ma3x[1 << 10][1 << 10];
char s[1 << 10];
int len[1 << 10];

int trie[1 << 20][26];
vector< int > levels[1 << 10];
int cntNodes, maxLevel;
int endNode[1 << 10];
pair<int, char> parent[1 << 20];
int suff[1 << 20];
int next[1 << 20][26];

pair< pair<int, int>, int > matched[1 << 20];

void init() {
    memset(trie, -1, sizeof(trie));
    cntNodes = 1;

    for(int i = 0; i <= maxLevel; i ++)
        levels[i].clear();
    maxLevel = 0;

    memset(next, -1, sizeof(next));
}

void addWord(int wi) {
    int curNode = 0;
    len[wi] = strlen(s);

    if(maxLevel < len[wi]) maxLevel = len[wi];

    for(int i = 0; i < len[wi]; i ++) {
        if(trie[curNode][ s[i] - 'A' ] == -1) {
            trie[curNode][ s[i] - 'A' ] = cntNodes;
            parent[cntNodes] = make_pair(curNode, s[i]);
            curNode = cntNodes ++;
            levels[i + 1].push_back(curNode);
        }
        else curNode = trie[curNode][ s[i] - 'A' ];
    }
    endNode[wi] = curNode;
}

void read() {
    scanf("%d %d %d\n", &n, &m, &w);
    for(int i = 0; i < n; i ++)
        scanf("%s", &ma3x[i]);
    for(int i = 0; i < w; i ++) {
        scanf("%s", &s);
        addWord(i);
    }
}

int getNext(int v, char c) {
    int idx = c - 'A';

    if(next[v][idx] != -1)
        return next[v][idx];

    if(trie[v][idx] == -1) {
        if(!v) next[v][idx] = 0;
        else next[v][idx] = getNext(suff[v], c);
    }
    else next[v][idx] = trie[v][idx];

    return next[v][idx];
}

void solve() {
    suff[0] = 0;
    for(int i = 0; i < levels[1].size(); i ++)
        suff[ levels[1][i] ] = 0;

    for(int i = 2; i <= maxLevel; i ++)
        for(int j = 0; j < levels[i].size(); j ++) {
            int node = levels[i][j];
            suff[node] = getNext(suff[ parent[node].first ], parent[node].second);
        }

    for(int i = 1; i < cntNodes; i ++)
        matched[i] = make_pair(make_pair(-1, -1), '0');

    int curNode, x, y;
    for(int i = 0; i < n; i ++) {
        // C
        curNode = 0;
        for(int j = 0; j < m; j ++) {
            curNode = getNext(curNode, ma3x[i][j]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(i, j), 'C');
        }

        // G
        curNode = 0;
        for(int j = m - 1; j >= 0; j --) {
            curNode = getNext(curNode, ma3x[i][j]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(i, j), 'G');
        }
    }

    for(int j = 0; j < m; j ++) {
        // E
        curNode = 0;
        for(int i = 0; i < n; i ++) {
            curNode = getNext(curNode, ma3x[i][j]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(i, j), 'E');
        }

        // A
        curNode = 0;
        for(int i = n - 1; i >= 0; i --) {
            curNode = getNext(curNode, ma3x[i][j]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(i, j), 'A');
        }
    }

    for(int i = 0; i < m; i ++) {
        x = 0, y = i;
        curNode = 0;
        while(x < n && y >= 0) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'F');
            x ++, y --;
        }

        x = 0, y = i;
        curNode = 0;
        while(x < n && y < m) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'D');
            x ++, y ++;
        }
    }

    for(int i = 0; i < m; i ++) {
        x = n - 1, y = i;
        curNode = 0;
        while(x >= 0 && y < m) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'B');
            x --, y ++;
        }

        x = n - 1, y = i;
        curNode = 0;
        while(x >= 0 && y >= 0) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'H');
            x --, y --;
        }
    }

    for(int i = 0; i < n; i ++) {
        x = i, y = 0;
        curNode = 0;
        while(x >= 0 && y < m) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'B');
            x --, y ++;
        }

        x = i, y = 0;
        curNode = 0;
        while(x < n && y < m) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'D');
            x ++, y ++;
        }
    }

    for(int i = 0; i < n; i ++) {
        x = i, y = m - 1;
        curNode = 0;
        while(x < n && y >= 0) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'F');
            x ++, y --;
        }

        x = i, y = m - 1;
        curNode = 0;
        while(x >= 0 && y >= 0) {
            curNode = getNext(curNode, ma3x[x][y]);
            if(curNode && matched[curNode].second == '0') matched[curNode] = make_pair(make_pair(x, y), 'H');
            x --, y --;
        }
    }

    for(int i = maxLevel; i >= 2; i --)
        for(int j = 0; j < levels[i].size(); j ++) {
            int node = levels[i][j];
            if(suff[node] && matched[ suff[node] ].second == '0')
                matched[ suff[node] ] = matched[node];
        }
}

void write() {
    for(int i = 0; i < w; i ++) {
        pair< pair<int, int>, char > ans = matched[ endNode[i] ];
        printf("%d %d %c\n", ans.first.first - (len[i] - 1) * dx[ans.second - 'A'],
                             ans.first.second - (len[i] - 1) * dy[ans.second - 'A'],
                             ans.second);
    }
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    //t = 1;
    for( ; t; t --) {
        init();
        read();
        solve();
        write();
    }

    return 0;
}
