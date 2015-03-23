/*
  Source: usaco - 2004/2005
  Task: bankint
*/
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

double r, m;
int y;

int main()
{
    cin >> r >> m >> y;
    for(int i = 1; i <= y; i ++)
        m = m * (1.0 + r / 100);
    printf("%.0lf\n",floor(m));

    return 0;
}
