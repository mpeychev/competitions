/*
PROG: zerosum
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int n;
char s[16];

void rec(int k)
{
     if(k==n)
     {
             int sum=0;
             int num=1;
             int op=1;
             for(int i=2;i<=n;i++)
             {
                     if(s[i-1]==' ') num=10*num+i;
                     else
                     {
                         if(op==1) sum+=num;
                         else sum-=num;
                         
                         if(s[i-1]=='+') op=1;
                         else op=2;
                         
                         num=i;
                     }
             }
             if(op==1) sum+=num;
             else sum-=num;
             if(sum==0)
             {
                       cout << 1;
                       for(int i=2;i<=n;i++) cout << s[i-1] << i;
                       cout << endl;
             }
             return;
     }
     s[k]=' ';
     rec(k+1);
     s[k]='+';
     rec(k+1);
     s[k]='-';
     rec(k+1);
}

int main()
{
    freopen("zerosum.in","r",stdin);
    freopen("zerosum.out","w",stdout);
    
    cin >> n;
    rec(1);
    
    return 0;
}
