/*
PROG: prefix
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

bool dp[1<<18];
string s[256],a;

bool check(int pos,int ind)
{
     if(s[ind].size()>pos) return false;
     if(!dp[pos-s[ind].size()]) return false;
     for(int i=pos,j=s[ind].size()-1;i>0 && j>=0;i--,j--) if(a[i]!=s[ind][j]) return false;
     return true;
}

int main()
{
    freopen("prefix.in","r",stdin);
    freopen("prefix.out","w",stdout);
    
    string tmp;
    
    int n=0;
    for( ; ; )
    {
         cin >> tmp;
         if(tmp==".") break;
         s[n]=tmp; n++;
    }
    
    char ch;
    a.push_back(' ');
    while(scanf("%c",&ch)==1) if(ch>='A' && ch<='Z') a.push_back(ch);
    
    dp[0]=1;
    for(int i=1;i<a.size();i++)
    {
            bool fl=false;
            for(int j=0;j<n;j++) if(check(i,j)) { fl=true; break; }
            dp[i]=fl;
    }
    
    for(int i=a.size()-1;i>=0;i--) if(dp[i]) { printf("%d\n",i); return 0; }
}
