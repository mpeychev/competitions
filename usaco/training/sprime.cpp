/*
ID: mompej951
TASK: sprime
LANG:C++
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

int n;
queue<ll> q;

bool prime(ll x)
{
     for(int i=2;i<=sqrt(x);i++) if(x%i==0) return false;
     return true;
}

int b(ll x)
{
    int br=0;
    while(x) { x/=10; br++; }
    return br;
}

int main()
{
    freopen("sprime.in","r",stdin);
    freopen("sprime.out","w",stdout);
    
    cin >> n;
    q.push(2);
    q.push(3);
    q.push(5);
    q.push(7);
    
    while(1)
    {
               ll a=q.front();
               if(b(a)==n) break;
               q.pop();
               ll tmp;
               tmp=a*10+1;
               if(prime(tmp)) q.push(tmp);
               tmp=a*10+3;
               if(prime(tmp)) q.push(tmp);
               tmp=a*10+7;
               if(prime(tmp)) q.push(tmp);
               tmp=a*10+9;
               if(prime(tmp)) q.push(tmp);
    }
    
    while(!q.empty()) { printf("%lld\n",q.front()); q.pop(); }
    
    return 0;
}
