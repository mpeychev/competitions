#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n1,n2,t;
string a,b,s;
int move[32];

int main()
{
    scanf("%d %d",&n1,&n2);
    cin >> a >> b;
    reverse(a.begin(),a.end());
    scanf("%d",&t);
    
    for(int i=0;i<a.size();i++) move[ a[i]-'A' ]=1;
    for(int j=0;j<b.size();j++) move[ b[j]-'A' ]=2;
    
    s=a+b;
    for(;t;t--)
    {
        for(int i=0;i<s.size()-1;i++)
         if(move[s[i]-'A']==1 && move[s[i+1]-'A']==2)
         {
                swap(s[i],s[i+1]);
                i++;
         }
    }
    cout << s << endl;
    
    return 0;
}
