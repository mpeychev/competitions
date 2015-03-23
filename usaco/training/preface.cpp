/*
PROG: preface
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int n;
/*
        I   1     L   50    M  1000
        V   5     C  100
        X  10     D  500
*/
string s[]=
{
"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
"M", "MM", "MMM"
};

int ci,cv,cx,cl,cc,cd,cm;

int num(int ind)
{
    if(ind<=8) return ++ind;
    if(ind>=9 && ind<=17) return (ind-8)*10;
    if(ind>=18 && ind<=26) return (ind-17)*100;
    if(ind>=27) return (ind-26)*1000;
}

void dec2rom(int x)
{
     string tmp;
     while(x)
     {
             for(int i=29;i>=0;i--)
             {
                     int t=num(i);
                     if(t<=x) { tmp+=s[i]; x-=t; break; }
             }
     }
     for(int i=0;i<tmp.size();i++)
      switch(tmp[i])
      {
                    case 'I': ci++; break;
                    case 'V': cv++; break;
                    case 'X': cx++; break;
                    case 'L': cl++; break;
                    case 'C': cc++; break;
                    case 'D': cd++; break;
                    case 'M': cm++; break;
      }
}

int main()
{
    freopen("preface.in","r",stdin);
    freopen("preface.out","w",stdout);
    
    cin >> n;
    for(int i=1;i<=n;i++) dec2rom(i);
    
    if(ci) cout << "I " << ci << endl;
    if(cv) cout << "V " << cv << endl;
    if(cx) cout << "X " << cx << endl;
    if(cl) cout << "L " << cl << endl;
    if(cc) cout << "C " << cc << endl;
    if(cd) cout << "D " << cd << endl;
    if(cm) cout << "M " << cm << endl;
    
    return 0;
}
