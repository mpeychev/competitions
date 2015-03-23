#include <stdio.h>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

struct dice
{
    int front, back;
    vector<int> roll;
    
    void init()
    {
        front = 2;
        back = 5;
        roll.pb(1);
        roll.pb(4);
        roll.pb(6);
        roll.pb(3);
    }
    
    void rollRight()
    {
        int first = roll[0];
        for(int i = 0; i < 3; i ++)
            roll[i] = roll[i + 1];
        roll[3] = first;
    }
    
    void rollLeft()
    {
        int last = roll[3];
        for(int i = 3; i > 0; i --)
            roll[i] = roll[i - 1];
        roll[0] = last;
    }
    
    void rollDown()
    {
        int f2 = roll[0];
        int b2 = roll[2];
        roll[0] = back;
        roll[2] = front;
        front = f2;
        back = b2;
    }
    
    int getSum()
    {
        int ret = 0;
        for(int i = 0; i < 4; i ++)
            ret += roll[i];
        return ret;
    }
};

int r, c;
long long ans;
dice d;

int main()
{
    scanf("%d %d", &r, &c);
    
    d.init();
    
    for(int i = 1; i <= r; i ++)
    {
        ans += d.getSum() * (c / 4);
        if(c % 4)
        {
            ans += d.roll[0];
            for(int j = 1; j < c % 4; j ++)
                if(i & 1)
                {
                    d.rollRight();
                    ans += d.roll[0];
                }
                else
                {
                    d.rollLeft();
                    ans += d.roll[0];
                }
        }
        d.rollDown();
    }
    
    cout << ans << endl;
    
    return 0;
}
