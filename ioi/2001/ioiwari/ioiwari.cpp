/*
  Source: ioi - 2001
  Task: ioiwari
  KeyW: game theory
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi;

const int n = 7;
const int MAXP = 300000;

vi state;
int s[16];
pii game[MAXP];
bool seen[MAXP];

int pos2num(vi pos)
{
    int ret=0,p=1;
    for(int i=n-1;i>=0;i--)
    {
        ret+=p*pos[i];
        p*=6;
    }
    return ret;
}

vi num2pos(int num)
{
    vi a;
    a.resize(n);
    for(int i=0;i<n;i++)
    {
        a[i]=num/s[n-i-1];
        num%=s[n-i-1];
    }
    return a;
}

void init()
{
    state.resize(n);
    for(int i=0;i<n;i++) scanf("%d",&state[i]);

    s[0]=1;
    for(int i=1;i<n;i++) s[i]=s[i-1]*6;

    seen[0]=1;
    game[0]=mp(0,0);
}

vi move(vi pos,int ind,int &score)
{
    score=0;

    int hand=pos[ind];
    pos[ind]=0;
    ind=(ind+1)%n;

    while(hand)
    {
        if(hand>1)
        {
            if(pos[ind]==5) { pos[ind]--; score++; }
            else { pos[ind]++; hand--; }
        }
        else
        {
            if(pos[ind]>=1 && pos[ind]<=4) { score+=hand+pos[ind]; hand=0; pos[ind]=0; }
            else hand=0;
        }

        ind=(ind+1)%n;
    }

    return pos;
}

pii go(vi pos)
{
    int c=pos2num(pos);

    if(seen[c]) return game[c];

    int best=-100,ind,sum=0,sum_left,score_now;

    for(int i=0;i<n;i++) sum+=pos[i];

    for(int i=0;i<n;i++)
        if(pos[i])
        {
            vi copy;

            copy=pos;
            copy=move(copy,i,score_now);

            sum_left=0;
            for(int j=0;j<n;j++) sum_left+=copy[j];

            int tmp=score_now + sum_left - go(copy).first;
            if(tmp>best) { best=tmp; ind=i; }
        }

    seen[c]=1;
    game[c]=mp(best,ind);
    return game[c];
}

void solve()
{
    while(1)
    {
        int h=go(state).second,x;
        printf("%d\n",h+1); fflush(stdout);
        state=move(state,h,x);

        if(pos2num(state)==0) break;

        scanf("%d",&h);
        state=move(state,h-1,x);

        if(pos2num(state)==0) break;
    }
}

int main()
{
    init();
    solve();

    return 0;
}
