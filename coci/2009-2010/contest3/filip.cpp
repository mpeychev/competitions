#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

string A,B;

int main()
{
    cin >> A >> B;
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());
    if(A>B) cout << A << endl;
    else cout << B << endl;

    return 0;
}
