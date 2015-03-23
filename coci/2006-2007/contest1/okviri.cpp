#include <iostream>
#include <string>
using namespace std;

int n;
string s;

void p()
{
    for(int i=1;i<=n;i++)
    {
        cout << "..";
        if(i%3) cout << "#";
        else cout << "*";
        cout << ".";
    }
    cout << ".\n";
}

void mid()
{
    cout << "#";
    for(int i=1;i<=n;i++)
    {
        if(i%3==1 || (i%3==2 && i==n)) cout << "." << s[i-1] << ".#";
        else cout << "." << s[i-1] << ".*";
    }
    cout << endl;
}

void q()
{
    for(int i=1;i<=n;i++)
    {
        if(i%3) cout << ".#.#";
        else cout << ".*.*";
    }
    cout << ".\n";
}

int main()
{
    cin >> s;
    n=s.size();
    
    p();
    q();
    mid();
    q();
    p();
    
    return 0;
}
