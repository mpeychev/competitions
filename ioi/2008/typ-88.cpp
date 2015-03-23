#include <stdio.h>
#include <iostream>
#include <string.h>
#include <deque>

#define pb push_back

using namespace std;

struct Trie {
    int iEnd, dwn;
    Trie *nxt[26];
};

void initTrie(Trie* &T){
    T = new Trie;
    T -> iEnd = 0;
    T -> dwn = 0;
    for(int i = 0; i < 26; i ++)
        T -> nxt[i] = NULL;
}

int len;
deque<char> ans;

void add(char *word, int pos, Trie* &T) {
    if(pos == len) {
        T -> iEnd ++;
        return;
    }

    int let = word[pos] - 'a';
    if(T -> nxt[let] == NULL) {
        Trie *newTrie;
        initTrie(newTrie);
        T -> nxt[let] = newTrie;
    }

    add(word, pos + 1, T -> nxt[let]);
    T -> dwn = max(T -> dwn, T -> nxt[let] -> dwn + 1);
}

void build(Trie* &T) {
    initTrie(T);

    int n;
    char s[32];

    scanf("%d\n", &n);
    for( ; n; n --) {
        scanf("%s", &s);
        len = strlen(s);
        add(s, 0, T);
    }
}

void dfs(Trie *T) {
    if(T -> iEnd) {
        for(int i = 0; i < T -> iEnd; i ++)
            ans.pb('P');
    }
    if(T -> dwn == 0) return;
    int idx = -1;
    for(int i = 0; i < 26; i ++)
        if(T -> nxt[i] != NULL) {
            if(idx == -1) idx = i;
            else if(T -> nxt[i] -> dwn > T -> nxt[idx] -> dwn) idx = i;
        }

    for(int i = 0; i < 26; i ++)
        if(T -> nxt[i] != NULL && idx != i) {
            ans.pb(i + 'a');
            dfs(T -> nxt[i]);
            ans.pb('-');
        }
    ans.pb(idx + 'a');
    dfs(T -> nxt[idx]);
    ans.pb('-');
}

void write() {
    while(ans.back() == '-') ans.pop_back();
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i ++)
        printf("%c\n", ans[i]);
}

int main()
{
    Trie *T;
    build(T);
    dfs(T);
    delete T;
    write();

    return 0;
}
