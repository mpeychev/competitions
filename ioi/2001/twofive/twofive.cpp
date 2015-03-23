/*
  Source: ioi - 2001
  Task: twofive
  KeyW: dp po shablon
*/

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

typedef vector<int> vi;

const int n = 5;
const int MAX_STATE = (1<<13);
const int MAX_LEN = (1<<5);
const int coef[]={1296,216,36,6,1};

int dp[MAX_STATE];
bool used[MAX_LEN];
int rend[n],cend[n];
int prevr,prevc;

vi p;
char key;
int no;
char s[MAX_LEN];

int index(vi pos)
{
    int ret=0;
    for(int i=n-1;i>=0;i--) ret+=pos[i]*coef[i];
    return ret;
}

int calc(vi pos)
{
    int ind=index(pos);
    if(!ind) return 1;
    if(dp[ind]!=-1) return dp[ind];
    
    int ret=0;
    for(int i=0;i<n*n;i++)
        if(!used[i])
        {
            used[i]=1;
            for(int j=0;j<n;j++)
                if(pos[j] && (j==0 || pos[j]>pos[j-1]) && rend[j]<i && cend[n-pos[j]]<i)
                {
                    pos[j]--;
                    ret+=calc(pos);
                    pos[j]++;
                }
            used[i]=0;
            break;
        }
    
    dp[ind]=ret;
    return dp[ind];
}

void word2num()
{
    for(int i=0;i<n*n;i++)
    {
        for(char let='A';let<s[i];let++)
            if(!used[let-'A'] && rend[i/n]<let-'A' && cend[i%n]<let-'A')
            {
                prevr=rend[i/n]; prevc=cend[i%n];
                used[let-'A']=1; rend[i/n]=let-'A'; cend[i%n]=let-'A'; p[i/n]--;
                
                memset(dp,-1,sizeof(dp));
                no+=calc(p);
                used[let-'A']=0; rend[i/n]=prevr; cend[i%n]=prevc; p[i/n]++;
            }
        
        used[s[i]-'A']=1; rend[i/n]=s[i]-'A'; cend[i%n]=s[i]-'A'; p[i/n]--;
    }
    printf("%d\n",no+1);
}

void num2word()
{
    no--;
    for(int i=0;i<n*n;i++)
        for(char let='A';let<'Z';let++)
            if(!used[let-'A'] && rend[i/n]<let-'A' && cend[i%n]<let-'A')
            {
                prevr=rend[i/n]; prevc=cend[i%n];
                used[let-'A']=1; rend[i/n]=let-'A'; cend[i%n]=let-'A'; p[i/n]--;
                
                memset(dp,-1,sizeof(dp));
                if(no<calc(p))
                {
                    s[i]=let;
                    break;
                }
                else
                {
                    no-=calc(p);
                    used[let-'A']=0; rend[i/n]=prevr; cend[i%n]=prevc; p[i/n]++;
                }
            }
    for(int i=0;i<n*n;i++) printf("%c",s[i]);
    printf("\n");
}

int main()
{
    p.resize(n);
    for(int i=0;i<n;i++) p[i]=n;
    memset(rend,-1,sizeof(rend));
    memset(cend,-1,sizeof(cend));
    
    scanf("%c",&key);
    if(key=='W')
    {
        scanf("%s",&s);
        word2num();
    }
    else
    {
        scanf("%d",&no);
        num2word();
    }
    
    return 0;
}
