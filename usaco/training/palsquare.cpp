/*
PROG: palsquare
LANG: C++
ID: mompej951
*/
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

ifstream fin;
ofstream fout;

int b;

string dig[]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K"};

string base(int a)
{
       string sol;
       sol.erase(sol.begin(),sol.end());
       while(a)
       {
               sol+=dig[a%b];
               a/=b;
       }
       
       reverse(sol.begin(),sol.end());
       return sol;
}

int main()
{
    fin.open("palsquare.in");
    fout.open("palsquare.out");
    
    fin >> b;
    for(int i=1;i<=300;i++)
    {
            string s=base(i*i);
            string s2=s;
            reverse(s2.begin(),s2.end());
            if(s2==s) { fout << base(i) << " " << s << endl; }
    }

    return 0;
}
