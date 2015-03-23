#include <iostream>
#include <stdio.h>

using namespace std;

int n, a, b, d;

int main()
{
    cin >> n >> a >> b;
    d = a * a + b * b;
    for(int i = 1; i <= n; i ++) {
        cin >> a;
        if(d >= a * a) printf("DA\n");
        else printf("NE\n");
    }

    return 0;
}
