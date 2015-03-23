/*
  Source: coci - 2010/2011 - contest2
  Task: Knjige
*/
#include <stdio.h>
#include <iostream>
#include <deque>

#define pushf push_front
#define popf pop_front

using namespace std;

int n,a;
deque <int> List;
int ans;

void Init()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a);
        List.pushf(a);
    }
}

void Solve()
{
    for(int i=0;i<List.size();i++)
    {
        while(i<List.size() && i+List[i]!=n)
        {
            ans++;
            List.popf();
        }
    }
    printf("%d\n",ans);
}

int main()
{
    Init();
    Solve();

    return 0;
}
