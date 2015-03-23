#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

int m,n;
ll x;
ll ans;
priority_queue<ll> pq;

int main()
{
	scanf("%d %d",&m,&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		pq.push(x);
	}
	
	for(int i=0;i<m;i++)
	{
		x=pq.top();
		pq.pop();
		pq.push(x-1);
	}
	
	while(!pq.empty())
	{
		x=pq.top();
		pq.pop();
		ans+=x*x;
	}
	
	cout << ans << endl;
	
	return 0;
}
