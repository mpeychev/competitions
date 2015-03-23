#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

#define pb push_back

using namespace std;

FILE *in = fopen("dict-twalk.txt", "r");

typedef long long LL;

const int MAXN = 1 << 5;
const int MAXNODES = 3200;

int n, m;
char ma3x[MAXN][MAXN];

char s[8], prv[8];
int cntNodes;
int trie[MAXNODES][26];
int parent[MAXNODES];
vector<int> vec[26];
bool terminal[MAXNODES];

int dp[MAXN][MAXN][MAXNODES];

void read() {
    scanf("%d %d\n", &n, &m);
    for(int i = 0; i < n; i ++)
        scanf("%s", &ma3x[i]);
}

void addWord() {
    int len = strlen(s);
    int tmpNode = 0;
    for(int i = 0; i < len; i ++) {
        int c = s[i] - 'A';
        if(trie[tmpNode][c] == -1) {
            trie[tmpNode][c] = cntNodes;
            parent[cntNodes] = tmpNode;
            vec[c].pb(cntNodes);
            cntNodes ++;
        }
        tmpNode = trie[tmpNode][c];
    }
    terminal[tmpNode] = true;
}

void build() {
    memset(trie, -1, sizeof(trie));
    cntNodes = 1;
    while(fscanf(in, "%s", &s)) {
        if(strcmp(prv, s) == 0) break;
        addWord();
        strcpy(prv, s);
    }
}

void solve() {
    for(int i = n - 1; i >= 0; i --)
        for(int j = 0; j < m; j ++) {
            int c = ma3x[i][j] - 'A';
            for(int k = 0; k < vec[c].size(); k ++) {
                int node = vec[c][k];
                if(parent[node] == 0) dp[i][j][node] = 1;
                else {
                    for(int h = i; h < n; h ++)
                        for(int f = 0; f <= j; f ++)
                            if(h != i || f != j)
                                dp[i][j][node] += dp[h][f][ parent[node] ];
                }
            }
        }

    LL ans = 0;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            for(int k = 1; k < cntNodes; k ++)
                if(terminal[k])
                    ans += dp[i][j][k];

    cout << ans << endl;
}

int main()
{
    read();
    build();
    solve();

    return 0;
}
