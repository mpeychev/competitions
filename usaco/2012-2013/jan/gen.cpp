#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int n = 200;
int m = 5000;

int main()
{
    freopen("seating.in", "w", stdout);

    srand(time(NULL));

    cout << n << " " << m << endl;
    for(int i = 0; i < m; i ++) {
        if(rand() % 2) {
            cout << "A " << rand() % n + 1 << endl;
        }
        else {
            cout << "L ";
            int a = rand() % n + 1;
            int b = rand() % n + 1;
            if(a > b) swap(a, b);
            cout << a << " " << b << endl;
        }
    }

    return 0;
}
