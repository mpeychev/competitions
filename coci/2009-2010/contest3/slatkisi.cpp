#include <stdio.h>
#include <iostream>

using namespace std;

int C,B=1,K;

int main()
{
    cin >> C >> K;
    for(int i=1;i<=K;i++) B*=10;
    if(B-(C%B)<=C%B) cout << (C/B+1)*B << endl;
    else cout << (C/B)*B << endl;

    return 0;
}
