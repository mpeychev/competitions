#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 100010;

int n;
ll m,br,ans;
ll wanted[MAXN];

void init()
{
	scanf("%d %d",&m,&n);
	for(int i=0;i<n;i++)
		scanf("%d",&wanted[i]);
	wanted[n]=0; n++;
	sort(wanted,wanted+n);
}

void solve()
{
	br=1;
	for(int i=n-2;i>=0;i--)
		if(wanted[i]==wanted[i+1]) br++;
		else
		{
			if(m>=br*(wanted[i+1]-wanted[i])) { m-=br*(wanted[i+1]-wanted[i]); br++; }
			else
			{
				for(int j=0;j<=i;j++) ans+=(wanted[j]*wanted[j]);
				ll amount=wanted[i+1];
				ll r=m%br;
				amount-=m/br;
				ans+=r*(amount-1)*(amount-1);
				ans+=(br-r)*amount*amount;
				cout << ans << endl;
				return;
			}
		}
}

int main()
{
	init();
	solve();
	
	return 0;
}
