/*
  Source: usaco - 2006/2007 - nov
  Task: plank - test generator
*/
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int n = 20;

int main()
{
    srand(time_t(0));
    cout << n << "\n";
    for(int i = 0; i < n; i ++)
        cout << rand() % 30 + 1 << " ";
    cout << endl;

    return 0;
}
