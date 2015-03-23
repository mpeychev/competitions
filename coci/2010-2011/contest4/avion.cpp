/*
  Source: coci - 2010/2011 - contest4
  Task: avion
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#define pb push_back

using namespace std;

const int n = 5;
string s;
vector<int> ans;

bool Check()
{
    for(int i=0;i+2<s.size();i++)
        if(s[i] == 'F' && s[i+1] == 'B' && s[i+2] == 'I')
            return true;
    return false;
}

void Write()
{
    for(int i=0;i<ans.size();i++)
    {
        if(i) printf(" ");
        printf("%d",ans[i]);
    }
    printf("\n");
}

int main()
{
    for(int i=1;i<=n;i++)
    {
        cin >> s;
        if(Check()) ans.pb(i);
    }
    if(!ans.size()) printf("HE GOT AWAY!\n");
    else Write();

    return 0;
}
