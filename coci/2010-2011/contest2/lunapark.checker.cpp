#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int r, c;
int ma3x[1024][1024];
int sum, ans;
char s[1 << 20];

void read() {
    scanf("%d %d", &r, &c);
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            scanf("%d", &ma3x[i][j]);
}

bool check(int x, int y) {
    if(x < 0 || x >= r || y < 0 || y >= c) return false;
    return true;
}

int calc() {
    int i = 0, j = 0;
    int idx = 0;
    int ret = 0;
    for(int k = 0; k < strlen(s); k ++) {
        char cmd = s[k];
        switch(cmd) {
            case 'U': i --; break;
            case 'D': i ++; break;
            case 'L': j --; break;
            case 'R': j ++; break;
        }
        if(!check(i, j)) {
            printf("nevalidna posledovatelnost!\n");
            return -1;
        }
        ret += ma3x[i][j];
    }
    return ret;
}

void readAnswer() {
    FILE *in = fopen("lunapark.out.10", "r");
    fscanf(in, "%s", &s);
}

void readOutput() {
    FILE *in = fopen("mo.out", "r");
    fscanf(in, "%s", &s);
}

int main()
{
    read();
    readAnswer();
    ans = calc();
    readOutput();
    sum = calc();

    if(sum == ans) printf("ok\n");
    else printf("wa\n");

    return 0;
}
