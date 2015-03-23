#include <stdio.h>
#include <iostream>

using namespace std;

int n, m;
int j, a, s;
int l, r;

int main()
{
    cin >> n >> m;
    cin >> j;
    
    l = 1; r = m;
    for(int i = 0; i < j; i ++)
    {
        cin >> a;
        if(a < l)
        {
            s += l - a;
            l = a;
            r = l + m - 1;
        }
        else if(a > r)
        {
            s += a - r;
            r = a;
            l = r - m + 1;
        }
    }
    
    cout << s << endl;
    
    return 0;
}
