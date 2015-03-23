/*
  Source: coci - 2010/2011 - contest4
  Task: parket
*/
#include <stdio.h>
#include <iostream>

using namespace std;

long long b,r;

int main()
{
    cin >> r >> b;
    for(int i=3;;i++)
        if(b%(i-2)==0)
        {
            int j=b/(i-2) + 2;
            if(2*i + 2*j - 4 == r)
            {
                cout << max(i,j) << " " << min(i,j) << endl;
                break;
            }
        }

    return 0;
}
