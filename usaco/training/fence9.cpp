/*
PROB: fence9
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int n,m,p;

int gcd(int a,int b)
{
    while(b)
    {
        int r=a%b;
        a=b;
        b=r;
    }
    return a;
}

int main()
{
    freopen("fence9.in","r",stdin);
    freopen("fence9.out","w",stdout);
    
    scanf("%d %d %d",&n,&m,&p);
    
    if(n==0 || n==p)
    {
        printf("%d\n",((m-1)*(p-1)-gcd(m,p)+1)/2);
        return 0;
    }
    
    if(n<p)
    {
        printf("%d\n",((m-1)*(n-1)-gcd(m,n)+1)/2 + m-1 + ((m-1)*(p-n-1)-gcd(m,p-n)+1)/2);
        return 0;
    }
    
    printf("%d\n",((n-1)*(m-1)-gcd(m,n)+1)/2 - gcd(m,n-p)+1 - ((m-1)*(n-p-1)-gcd(m,n-p)+1)/2);
    return 0;
}
