#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int n, a, b, c, d, e;
string s[8];

void read() {
    for(int i = 0; i < 5; i ++)
        cin >> s[i];
}

inline int parse(string str) {
    if(str == "?") return -1;
    int ret = 0;
    for(int i = 0; i < str.size(); i ++)
        ret = ret * 10 + (str[i] - '0');
    return ret;
}

void solve() {
    a = parse(s[0]);
    b = parse(s[1]);
    c = parse(s[2]);
    d = parse(s[3]);
    e = parse(s[4]);

    if(b == -1 && c == -1 && e == -1) b = 0, c = 0, e = 0;

    if(b != -1 && c != -1) e = 3 * b + c;
    if(b != -1 && e != -1) c = e - 3 * b;
    if(c != -1 && e != -1) b = (e - c) / 3;

    if(b != -1 && c != -1 && e != -1) {
        if(a != -1) {
            d = a - b - c;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }
        if(d != -1) {
            a = b + c + d;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }
        a = b + c;
        d = 0;
        cout << a << " " << b << " " << c << " " << d << " " << e << endl;
        return;
    }

    if(b != -1) {
        if(d != -1 && a != -1) {
            c = a - b - d;
            e = 3 * b + c;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }

        if(d != -1) {
            a = b + d;
            c = 0;
            e = 3 * b;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }

        if(a != -1) {
            d = a - b;
            c = 0;
            e = 3 * b;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }

        a = b;
        c = 0;
        d = 0;
        e = 3 * b;
        cout << a << " " << b << " " << c << " " << d << " " << e << endl;
        return;
    }

    if(c != -1) {
        if(d != -1 && a != -1) {
            b = a - c - d;
            e = 3 * b + c;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }

        if(d != -1) {
            a = c + d;
            b = 0;
            e = c;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }

        if(a != -1) {
            d = a - c;
            b = 0;
            e = c;
            cout << a << " " << b << " " << c << " " << d << " " << e << endl;
            return;
        }

        a = c;
        b = 0;
        d = 0;
        e = c;
        cout << a << " " << b << " " << c << " " << d << " " << e << endl;
        return;
    }

    for(int i = 0; i <= 100; i ++)
        for(int j = 0; j <= 100; j ++)
            if(3 * i + j == e && i + j <= 100) {
                if(d != -1 && a != -1) {
                    if(i + j + d == a) {
                        cout << a << " " << i << " " << j << " " << d << " " << e << endl;
                        return;
                    }
                    continue;
                }

                if(d != -1 && i + j + d <= 100) {
                    a = i + j + d;
                    cout << a << " " << i << " " << j << " " << d << " " << e << endl;
                    return;
                }

                if(a != -1 && i + j <= a) {
                    d = a - i - j;
                    cout << a << " " << i << " " << j << " " << d << " " << e << endl;
                    return;
                }

                if(a == -1 && d == -1) {
                    a = i + j;
                    d = 0;
                    cout << a << " " << i << " " << j << " " << d << " " << e << endl;
                    return;
                }
            }

    cout << "no print\n";
}

int main()
{
    scanf("%d\n", &n);
    for( ; n; n --) {
        read();
        solve();
    }

    return 0;
}
