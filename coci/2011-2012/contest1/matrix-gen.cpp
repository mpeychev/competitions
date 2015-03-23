#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;



int main()
{
    srand(time_t(0));
    
    cout << 400 << endl;
    for(int i = 0; i < 400; i ++)
    {
        for(int j = 0; j < 400; j ++)
            cout << rand() % 1000 + 1 << " ";
        cout << endl;
    }
    
    return 0;
}
