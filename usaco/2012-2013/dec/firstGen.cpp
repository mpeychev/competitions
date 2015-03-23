#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int n = 30000;

int main()
{
    freopen("first.in", "w", stdout);

    srand(time_t(NULL));

    cout << n << endl;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < 10; j ++)
            printf("%c", rand() % 26 + 'a');
        printf("\n");
    }

    return 0;
}
