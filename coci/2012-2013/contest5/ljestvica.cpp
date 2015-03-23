#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

string s;
int brA, brC;

void add(char ch) {
    if(ch == 'A' || ch == 'D' || ch == 'E') brA ++;
    if(ch == 'C' || ch == 'F' || ch == 'G') brC ++;
}

int main()
{
    cin >> s;
    add(s[0]);
    for(int i = 0; i < s.size(); i ++)
        if(s[i] == '|')
            add(s[i + 1]);

    if(brA > brC) cout << "A-mol\n";
    else if(brA < brC) cout << "C-dur\n";
    else {
        if(s[ s.size() - 1 ] == 'A') cout << "A-mol\n";
        else cout << "C-dur\n";
    }

    return 0;
}
