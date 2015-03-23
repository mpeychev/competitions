#include <stdio.h>
#include <iostream>

using namespace std;

int n;

int main()
{
    cin >> n;
    int a = n / 2;
    int b = n - a;
    cout << (a + 1) * (b + 1) << endl;

    return 0;
}
