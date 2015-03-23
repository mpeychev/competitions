#include <stdio.h>
#include <algorithm>
using namespace std;

int m[4];
int a,b,c;
char s[4];

int print(char ch)
{
    if(ch=='A') return m[0];
    if(ch=='B') return m[1];
    if(ch=='C') return m[2];
}

int main()
{
    scanf("%d %d %d",&m[0],&m[1],&m[2]);
    scanf("%s",&s);
    
    sort(m,m+3);
    
    printf("%d %d %d\n",print(s[0]),print(s[1]),print(s[2]));
    
    return 0;
}
