/*
  Source: usaco - 2004/2005 - qual
  Task: bullmath
  KeyW: long arithmetic
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

#define pb push_back

using namespace std;

string sum(string a, string b)
{
    string ret;
    int p = 0;

    while(a.size() < b.size()) a.insert(0, 1, '0');
    while(a.size() > b.size()) b.insert(0, 1, '0');

    for(int i = a.size() - 1; i >= 0; i --)
    {
        int d = (a[i] - '0') + (b[i] - '0') + p;
        ret.pb(d % 10 + '0');
        p = d / 10;
    }
    if(p) ret.pb('1');
    reverse(ret.begin(), ret.end());
    return ret;
}

string mul1(string a, int dig)
{
    string ret;
    int p = 0;

    for(int i = a.size() - 1; i >= 0; i --)
    {
        int d = (a[i] - '0') * dig + p;
        ret.pb(d % 10 + '0');
        p = d / 10;
    }
    if(p) ret.pb(p + '0');
    reverse(ret.begin(), ret.end());
    return ret;
}

string mul(string a, string b)
{
    string ret;

    for(int i = a.size() - 1; i >= 0; i --)
    {
        string add = mul1(b, a[i] - '0');
        for(int j = i + 1; j < a.size(); j ++) add.pb('0');
        ret = sum(ret, add);
    }
    return ret;
}

int main()
{
    string a, b;
    cin >> a >> b;
    cout << mul(a, b) << endl;

    return 0;
}
