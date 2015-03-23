#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

string s;
int th, tm, ts;
int fh, fm, fs;
int ans;

void read() {
    cin >> s;
    th = (s[0] - '0') * 10 + (s[1] - '0');
    tm = (s[3] - '0') * 10 + (s[4] - '0');
    ts = (s[6] - '0') * 10 + (s[7] - '0');

    cin >> s;
    fh = (s[0] - '0') * 10 + (s[1] - '0');
    fm = (s[3] - '0') * 10 + (s[4] - '0');
    fs = (s[6] - '0') * 10 + (s[7] - '0');
}

void write(int x) {
    if(x < 10) cout << "0";
    cout << x;
}

void solve() {
    for( ; ; ) {
        ans ++;
        if(ts < 59) ts ++;
        else {
            ts = 0;
            tm ++;
            if(tm == 60) {
                tm = 0;
                th ++;
                if(th == 24) th = 0;
            }
        }

        if(th == fh && tm == fm && ts == fs) break;
    }

    write(ans / 3600);
    printf(":");
    ans %= 3600;

    write(ans / 60);
    printf(":");
    ans %= 60;

    write(ans);
    printf("\n");
}

int main()
{
    read();
    solve();

    return 0;
}
