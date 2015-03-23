/*
ID: mompej951
TASK: nuggets
LANG: C++
*/
#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int s = 10000000;

int n;
int a[16];
bool dp[s + 10];
int d;

int main()
{
	freopen("nuggets.in","r",stdin);
	freopen("nuggets.out","w",stdout);
	
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d",&a[i]);
		if(!i) d = a[i];
		else d = __gcd(d, a[i]);
	}
	
	sort(a, a + n);
	
	if(a[0] == 1 || d != 1)
	{
		printf("0\n");
		return 0;
	}
	
	dp[0] = 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j + a[i] <= s; j++)
			if(dp[j])
				dp[j + a[i]] = 1;
	
	for(int i = s - 1; ;i--)
		if(!dp[i])
		{
			printf("%d\n",i);
			break;
		}
	
	return 0;
}
