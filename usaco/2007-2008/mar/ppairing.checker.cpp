#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int n, c;
int cnt[100100];

pair<int, int> tmp;
pair<int, int> ans[50500];
int sz;

void readInput() {
    FILE *in1 = fopen("ppairing.9.in", "r");
    fscanf(in1, "%d %d", &n, &c);
    for(int i = 1; i <= c; i ++)
        fscanf(in1, "%d", &cnt[i]);
}

void readAnswer() {
    FILE *in2 = fopen("mo.out", "r");
    while(fscanf(in2, "%d %d", &tmp.first, &tmp.second) == 2)
        ans[sz ++] = tmp;
}

void check() {
    if(2 * sz != n) {
        printf("wa1\n");
        return;
    }

    for(int i = 0; i < sz; i ++) {
        if(ans[i].first == ans[i].second) {
            printf("wa2\n");
            return;
        }
        cnt[ ans[i].first ] --;
        cnt[ ans[i].second ] --;
    }

    for(int i = 1; i <= c; i ++)
        if(cnt[i] != 0) {
            printf("wa3\n");
            return;
        }

    printf("ok\n");
}

int main()
{
    readInput();
    readAnswer();
    check();

    return 0;
}
