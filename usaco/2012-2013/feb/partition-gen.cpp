#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;



int main()
{
    freopen("partition.in", "w", stdout);

    srand(time(NULL));

    int n = 15, k = 14;

    cout << n << " " << k << endl;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++)
            cout << rand() % 1001 << " ";
        cout << endl;
    }

    return 0;
}
