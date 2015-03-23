/*
  Source: usaco - 2006/2007
  Task: guess
  KeyW: bs; interactive
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int n;
char s[4];
char reply;

int main()
{
    scanf("%d",&n);

    int l = 1, r = n, mid;
    while(l <= r)
    {
        mid = (l + r) / 2;
        cout << mid << "\n" << flush;

        scanf("%s",&s);
        if(s[0] == 'H') r = mid - 1;
        else if(s[0] == 'L') l = mid + 1;
        else if(s[0] == 'O') break;
    }

    return 0;
}
