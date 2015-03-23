#include <stdio.h>
#include <iostream>

using namespace std;

const int st[] = {1, 1, 2, 2, 2, 8};
int a;

int main()
{
    for(int i = 0; i < 6; i ++) {
        cin >> a;
        cout << st[i] - a;
        if(i != 5) cout << " ";
        else cout << endl;
    }

    return 0;
}
