#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

int n,a,b;
vector<int> grades[8];
int sol=-1,ans;

int get(int g)
{
	if(grades[g].size()==0) return 0;
	int tmp=1,ret=1;
	for(int i=1;i<grades[g].size();i++)
		if(grades[g][i]==grades[g][i-1]+1) tmp++;
		else
		{
			if(tmp>ret) ret=tmp;
			tmp=1;
		}
	if(tmp>ret) ret=tmp;
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&a,&b);
		grades[a].pb(i);
		if(b!=a) grades[b].pb(i);
	}
	for(int i=1;i<=5;i++)
	{
		int num=get(i);
		if(sol<num)
		{
			sol=num;
			ans=i;
		}
	}
	printf("%d %d\n",sol,ans);
	return 0;
}
