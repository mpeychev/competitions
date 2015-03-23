/*
PROG: fracdec
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int n,d,used[1<<17],c;
string s;

int main()
{
    freopen("fracdec.in","r",stdin);
    freopen("fracdec.out","w",stdout);
    cin >> n >> d;
    if(n%d==0) { cout << n/d << ".0\n"; return 0; }
    c=n/d;
    n%=d;
    used[n]=1;
    for(int i=2;;i++)
    {
        n*=10;
        int tmp=n/d;
        n%=d;
        if(used[n])
        {
            if(n!=0) { s.push_back(tmp+'0'); s.insert(used[n]-1,1,'('); s.push_back(')'); }
            break;
        }
        s.push_back(tmp+'0');
        used[n]=i;
    }
    s.insert(0,1,'.');
    if(c==0) s.insert(0,1,'0');
    while(c) { s.insert(0,1,c%10+'0'); c/=10; }
    
    for(int i=0;i<s.size();i++)
    {
        cout << s[i];
        if((i+1)%76==0) cout << endl;
    }
    cout << endl;
    
    return 0;
}
