/*
PROG: cowlpha
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

#define pb push_back

using namespace std;

const int MAXP = 205;
const int MAXU = 256;
const int MOD = 97654321;

int u,l,p;
char s[MAXP][2];
vector<int> g[MAXP];
int dp[MAXP][MAXU] , dpCpy[MAXP][MAXU];

bool IsUp(char ch)
{
    if(ch >= 'A' && ch <= 'Z') return 1;
    return 0;
}

void Init()
{
    scanf("%d %d %d\n",&u,&l,&p);
    for(int i=0;i<p;i++)
        scanf("%c %c\n",&s[i][0],&s[i][1]);
    
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++)
            if(s[i][1] == s[j][0])
                g[i].pb(j);
}

void Solve()
{
    for(int i=0;i<p;i++)
		if(IsUp(s[i][0]) + IsUp(s[i][1]) <= u)
			dp[i][IsUp(s[i][0]) + IsUp(s[i][1])] = 1;
	
	for(int i=3;i<=u + l;i++)
	{
		memset(dpCpy , 0 , sizeof(dpCpy));
		for(int ver=0;ver<p;ver++)
			for(int j=0;j<g[ver].size();j++)
			{
				int nxt = g[ver][j];
				for(int up=0;up<=u && up<i;up++)
					if(up + IsUp(s[nxt][1]) <= u)
						dpCpy[nxt][up + IsUp(s[nxt][1])] = (dpCpy[nxt][up + IsUp(s[nxt][1])] + dp[ver][up]) % MOD;
			}
		
		memcpy(dp , dpCpy , sizeof(dpCpy));
	}
	
	int ans = 0;
	for(int i=0;i<p;i++)
		ans = (ans + dp[i][u]) % MOD;
	
	printf("%d\n",ans);
}

int main()
{    
    Init();
    Solve();
    
    return 0;
}
