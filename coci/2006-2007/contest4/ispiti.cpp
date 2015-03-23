#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string.h>
#include <map>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 200005;

inline int max(int x, int y) {
    if(x < y) return y;
    return x;
}

struct PII {
    int a, b;

    PII() {}
    PII(int _a, int _b): a(_a), b(_b) {}
};

struct Record {
    char cmd;
    int a, b;
};

struct Student {
    PII val;
    int index;

    Student() {}
    Student(PII _val, int _index): val(_val), index(_index) {}
};

int n;
Record inp[MAXN];
vector< PII > vec;
vector< Student > vec2;
int groupsLen, groupsCount;
int A[MAXN];
int maxA[500];

void solveSlow() {
    char cmd;
    int a, b, x;

    for(int i = 0; i < n; i ++) {
        scanf("%c", &cmd);
        if(cmd == 'D') {
            scanf("%d %d\n", &a, &b);
            vec.pb(PII(a, b));
        }
        else {
            scanf("%d\n", &x);
            x --;

            int idx = -1;
            for(int j = 0; j < vec.size(); j ++)
                if(j != x && vec[j].a >= vec[x].a && vec[j].b >= vec[x].b) {
                    if(idx == -1) idx = j;
                    else {
                        if(vec[j].b < vec[idx].b) idx = j;
                        else if(vec[j].b == vec[idx].b && vec[j].a < vec[idx].a) idx = j;
                    }
                }

            if(idx == -1) printf("NE\n");
            else printf("%d\n", idx + 1);
        }
    }
}

void read() {
    for(int i = 0; i < n; i ++) {
        scanf("%c", &inp[i].cmd);
        if(inp[i].cmd == 'D') {
            scanf("%d %d\n", &inp[i].a, &inp[i].b);
            vec.pb(PII(inp[i].a, inp[i].b));
            vec2.pb(Student(PII(inp[i].a, inp[i].b), vec.size()));
        }
        else {
            scanf("%d\n", &inp[i].a);
            inp[i].a --;
        }
    }
}

bool cmpPII(PII p1, PII p2) {
    if(p1.b < p2.b) return true;
    if(p1.b > p2.b) return false;
    return p1.a < p2.a;
}

bool cmpStudents(Student p1, Student p2) {
    return cmpPII(p1.val, p2.val);
}

int getIndex(PII k) {
    int le = 0, ri = vec2.size() - 1, mid;
    while(le <= ri) {
        mid = (le + ri) >> 1;

        if(k.a == vec2[mid].val.a && k.b == vec2[mid].val.b) return mid;

        if(cmpPII(k, vec2[mid].val)) ri = mid - 1;
        else le = mid + 1;
    }

    return -1;
}

void solve() {
    groupsLen = (int)sqrt(vec.size());
    if(groupsLen * groupsLen < vec.size()) groupsLen ++;

    groupsCount = vec.size() / groupsLen;
    if(groupsCount * groupsLen < vec.size()) groupsCount ++;

    sort(vec2.begin(), vec2.end(), cmpStudents);

    int idx;

    for(int i = 0; i < n; i ++)
        if(inp[i].cmd == 'D') {
            idx = getIndex(PII(inp[i].a, inp[i].b));

            if(idx == -1) {
                printf("Index -1 ..\n");
                continue;
            }

            A[idx] = inp[i].a;
            maxA[idx / groupsLen] = max(maxA[idx / groupsLen], A[idx]);
        }
        else {
            idx = getIndex(vec[ inp[i].a ]);

            if(idx == -1) {
                printf("Index -1 ..\n");
                continue;
            }

            int limitA = vec2[idx].val.a;

            int groupIdx = idx / groupsLen;

            bool fl = false;
            for(int j = idx + 1; j < vec.size() && j % groupsLen; j ++)
                if(A[j] >= limitA) {
                    printf("%d\n", vec2[j].index);
                    fl = true;
                    break;
                }

            if(fl) continue;

            int start = -1;
            for(int j = groupIdx + 1; j < groupsCount; j ++)
                if(maxA[j] >= limitA) {
                    start = j * groupsLen;
                    break;
                }

            if(start == -1) {
                printf("NE\n");
                continue;
            }

            for(int j = start; ; j ++)
                if(A[j] >= limitA) {
                    printf("%d\n", vec2[j].index);
                    break;
                }
        }
}

int main()
{
    scanf("%d\n", &n);

    if(n <= 1000) {
        solveSlow();
        return 0;
    }

    read();
    solve();

    return 0;
}
