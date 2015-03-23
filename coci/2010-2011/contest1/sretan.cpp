#include <stdio.h>

using namespace std;

int k,dig;

int main()
{
	scanf("%d",&k);
	k--;
	for(int i=1;;i++)
	{
		dig=i;
		if(k-(1<<i)>=0) k-=(1<<i);
		else break;
	}
	for(int i=dig-1;i>=0;i--)
		if(k-(1<<i)>=0) { printf("7"); k-=(1<<i); }
		else printf("4");
	printf("\n");
	return 0;
}
