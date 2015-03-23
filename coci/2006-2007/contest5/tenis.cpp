#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const string fed = "federer";

string a, b;
char res[128];
int n;

bool check1(PII t) {
    int x = t.first;
    int y = t.second;

    if(x > 7 || y > 7) return false;
    if(x < 6 && y < 6) return false;

    if(x == 6) return (y == 7 || y <= 4);
    if(x == 7) return (y == 6 || y == 5);
    if(y == 6) return (x <= 4);
    if(y == 7) return x == 5;

    return false;
}

bool check2(PII t) {
    int x = t.first;
    int y = t.second;

    if(x == y) return false;

    if(x > y) {
        if(x < 6) return false;
        if(x == 6) return y <= 4;
        return x - 2 == y;
    }

    if(y < 6) return false;
    if(y == 6) return x <= 4;
    return y - 2 == x;
}

short int win(PII t) {
    if(t.first > t.second) return 1;
    return 2;
}

void solve() {
    int n = strlen(res);

    vector< PII > vec;

    for(int i = 0; i < n; i ++)
        if(res[i] == ':') {
            int x = 0, y = 0, p = 1;
            for(int j = i + 1; j < n; j ++) {
                if(!isdigit(res[j])) break;
                y = y * 10 + (res[j] - '0');
            }
            for(int j = i - 1; j >= 0; j --) {
                if(!isdigit(res[j])) break;
                x = x + p * (res[j] - '0');
                p *= 10;
            }
            vec.pb(mp(x, y));
        }

    if(vec.size() < 2 || vec.size() > 3) {
        printf("ne\n");
        return;
    }

    if(!check1(vec[0])) {
        printf("ne\n");
        return;
    }
    if(!check1(vec[1])) {
        printf("ne\n");
        return;
    }
    if(vec.size() == 3 && !check2(vec[2])) {
        printf("ne\n");
        return;
    }

    if(vec.size() == 2 && win(vec[0]) != win(vec[1])) {
        printf("ne\n");
        return;
    }
    if(vec.size() == 3 && win(vec[0]) == win(vec[1])) {
        printf("ne\n");
        return;
    }

    if(a == fed) {
        if(vec.size() == 3) {
            printf("ne\n");
            return;
        }

        if(win(vec[0]) == 2) {
            printf("ne\n");
            return;
        }
    }

    if(b == fed) {
        if(vec.size() == 3) {
            printf("ne\n");
            return;
        }

        if(win(vec[0]) == 1) {
            printf("ne\n");
            return;
        }
    }

    printf("da\n");
}

int main()
{
    cin >> a >> b;
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++) {
        gets(res);
        solve();
    }

    return 0;
}
