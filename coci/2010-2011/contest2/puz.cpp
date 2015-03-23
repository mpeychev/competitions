/*
  Source: coci - 2010/2011 - contest2
  Task: Puz
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int a,b,v;

int main()
{
    scanf("%d %d %d",&a,&b,&v);
    v-=a;
    if(v%(a-b) == 0) printf("%d\n",v/(a-b) + 1);
    else printf("%d\n",v/(a-b) + 2);

    return 0;
}
