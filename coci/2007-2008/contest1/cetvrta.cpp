#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int x[4], y[4];
int maxX, maxY, minX, minY;

void read() {
    for(int i = 0; i < 3; i ++)
        cin >> x[i] >> y[i];
}

void check(int X, int Y) {
    for(int i = 0; i < 3; i ++)
        if(x[i] == X && y[i] == Y)
            return;
    cout << X << " " << Y << endl;
    exit(0);
}

void solve() {
    maxX = x[0];
    minX = x[0];
    
    maxY = y[0];
    minY = y[0];
    
    for(int i = 1; i < 3; i ++) {
        maxX = max(maxX, x[i]);
        minX = min(minX, x[i]);
        
        maxY = max(maxY, y[i]);
        minY = min(minY, y[i]);
    }
    
    check(minX, minY);
    check(minX, maxY);
    check(maxX, minY);
    check(maxX, maxY);
}

int main()
{
    read();
    solve();
    
    return 0;
}
