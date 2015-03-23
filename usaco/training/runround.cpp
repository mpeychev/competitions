/*
PROG: runround
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long long m;

bool valid(long long x)
{
     string num;
     int cnt[16]={0};
     bool used[16]={0};
     
     while(x)
     {
             num.push_back((x%10)+'0');
             if(used[x%10]) return false;
             used[x%10]=1;
             x/=10;
     }
     reverse(num.begin(),num.end());
     
     int tmp=0;
     for(int i=0;i<num.size();i++)
     {
             cnt[tmp]++;
             if(cnt[tmp]==2) return false;
             tmp=(tmp+(num[tmp]-'0'))%num.size();
     }
     if(tmp==0) return true;
     return false;
}

int main()
{
    freopen("runround.in","r",stdin);
    freopen("runround.out","w",stdout);
    
    cin >> m;
    
    for(m++;;m++) if(valid(m)) { cout << m << endl; break; }
    
    return 0;
}
