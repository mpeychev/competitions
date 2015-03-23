#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const string ones[]={"","I","II","III","IV","V","VI","VII","VIII","IX"};
const string tens[]={"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};

string B;

bool check(int x)
{
    string s=tens[x/10]+ones[x%10];
    sort(s.begin(),s.end());
    return B==s;
}

int main()
{
    cin >> B;
    sort(B.begin(),B.end());
    for(int i=1;;i++)
        if(check(i))
        {
            cout << tens[i/10]+ones[i%10] << endl;
            break;
        }

    return 0;
}
