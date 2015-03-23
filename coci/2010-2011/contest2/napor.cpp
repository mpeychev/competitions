/*
  Source: coci - 2010/2011 - contest2
  Task: Napor
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

int n;
string s;
vector<string> list;

bool cmp(string a,string b)
{
    if(a.size()<b.size()) return true;
    if(a.size()>b.size()) return false;
    return a<b;
}

void Add(string t)
{
    int l=t.size();
    string num;
    for(int i=0;i<t.size();i++)
        if(t[i]!='0')
        {
            for(int j=i;j<t.size();j++) num.pb(t[j]);
            list.pb(num);
            return;
        }
    list.pb("0");
}

void Parse()
{
    string tmp;
    for(int i=0;i<s.size();i++)
        if(s[i]>='a' && s[i]<='z')
        {
            if(tmp.size()) { Add(tmp); tmp.clear(); }
        }
        else tmp.pb(s[i]);
    if(tmp.size()) Add(tmp);
}

void Write()
{
    sort(list.begin(),list.end(),cmp);
    for(int i=0;i<list.size();i++)
        cout << list[i] << endl;
}

int main()
{
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> s;
        Parse();
    }
    Write();

    return 0;
}
