#include <stdio.h>
#include <iostream>

using namespace std;

int n;
char s[64];
int br1, br2;

int main()
{
    scanf("%d\n", &n);
    scanf("%s", &s);

    for(int i = 0; i < n; i ++)
        if(s[i] == 'L') br1 ++;
        else br2 ++;

    cout << min(n, (br1 / 2) + br2 + 1) << endl;

    return 0;
}
