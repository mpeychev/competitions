#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 100010;

int n,s;
int a[MAXN],sum[MAXN];

int SumLR(int le,int ri) { return sum[ri] - sum[le-1]; }

int MaxK(int ind,int lim)
{
	int l = 0 , r = lim , mid;
	//cout << ind << " " << l << " " << r << endl;
	while(l < r)
	{
		mid = (l + r + 1)/2;
		//cout << l << " " << r << " " << mid << " " << ind << " " << ind + mid -1 << " " << SumLR(ind , ind + mid - 1) << endl;
		if(SumLR(ind , ind + mid - 1) > s) r = mid-1;
		else l = mid;
	}
	return l;
}

int MaxLen(int ind)
{
    for(int k=MaxK( ind , (n-ind+1)/2 );k>=1;k--)
        if(SumLR(ind,ind+k-1)<=s && SumLR(ind+k,ind+2*k-1)<=s)
            return 2*k;
    return 0;
}

int main()
{
    scanf("%d %d",&n,&s);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        sum[i] = sum[i-1] + a[i];
    }
    
    for(int i=1;i<=n;i++)
        printf("%d\n",MaxLen(i));
        
    return 0;
}
