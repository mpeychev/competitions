#include <iostream>
#include <string>
#include <vector>
using namespace std;

string s;
vector<int> pos;
int m[16];
long long sol=0;

int vow(char ch)
{
    if(ch=='_') return -1;
    if(ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U') return 1;
    return 0;
}

bool ok()
{
    for(int i=0;i<s.size()-2;i++)
    {
     if(vow(s[i])==1 && vow(s[i+1])==1 && vow(s[i+2])==1) return false;
     if(!vow(s[i]) && !vow(s[i+1]) && !vow(s[i+2])) return false;
    }
    return true;
}

bool L()
{
    bool L=false;
    for(int i=0;i<s.size();i++) if(s[i]=='L') L=true;
    return L;
}

void solve(int k)
{
    if(k==pos.size())
    {
        if(!ok() || !L()) return;
        long long tmp=1;
        for(int i=0;i<pos.size();i++)
         if(m[i]==0) tmp*=5;
         else if(m[i]==1) tmp*=20;
        sol+=tmp;
        return;
    }
    m[k]=0;
    s[pos[k]]='A';
    solve(k+1);
    
    m[k]=1;
    s[pos[k]]='B';
    solve(k+1);
    
    m[k]=2;
    s[pos[k]]='L';
    solve(k+1);
}

int main()
{
    cin >> s;
    if(!ok()) { cout << "0\n"; return 0; }
    for(int i=0;i<s.size();i++) if(s[i]=='_') pos.push_back(i);
    /*
    for(int i=0;i<pos.size();i++) cout << pos[i] << " ";
    cout << endl;
    */
    solve(0);
    cout << sol << endl;
    
    return 0;
}
