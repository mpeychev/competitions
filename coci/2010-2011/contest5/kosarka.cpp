#include <stdio.h>
#include <iostream>

using namespace std;

int n;
short int scores[3000];
short int team;
char s[8];
int res[2];
int ans[2];

void Write(int x)
{
    int mins = x/60;
    int secs = x%60;
    if(mins<10) printf("0");
    printf("%d",mins);
    printf(":");
    if(secs<10) printf("0");
    printf("%d",secs);
    printf("\n");
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d %s",&team,&s);
        int mins = (s[0]-'0')*10 + (s[1]-'0');
        int secs = (s[3]-'0')*10 + (s[4]-'0');
        scores[mins*60 + secs] = team;
    }
    
    for(int i=0;i<48*60;i++)
    {
        if(scores[i]) res[scores[i]-1]++;
        if(res[0] > res[1]) ans[0] ++;
        if(res[0] < res[1]) ans[1] ++;
    }
    
    Write(ans[0]);
    Write(ans[1]);
    
    return 0;
}
