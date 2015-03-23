#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define mp make_pair
#define pb push_back

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;

int n;
vi perm,target,next;
int p[10],br;
bool used[10];
int level[40320];
int prev[40320];
pii tmp;

queue< pii > pq;

int encode(vi m)
{
	int ret=0;
	memset(used,0,sizeof(used));
	for(int i=0;i<n;i++)
	{
		br=0;
		for(int j=1;j<m[i];j++)
			if(!used[j])
				br++;
		used[m[i]]=1;
		ret+=p[n-i-1]*br;
	}
	return ret;
}

vi decode(int num)
{
	vi ret;
	ret.resize(n);
	memset(used,0,sizeof(used));
	for(int i=0;i<n;i++)
	{
		br=0;
		for(int j=1;j<=n;j++)
			if(!used[j])
			{
				br++;
				if(num>=(br-1)*p[n-i-1]) ret[i]=j;
			}
		used[ret[i]]=1;
		br=0;
		for(int j=1;j<ret[i];j++)
			if(!used[j])
				br++;
		num-=br*p[n-i-1];
	}
	return ret;
}

void init()
{
	scanf("%d",&n);
	perm.resize(n);
	target.resize(n);
	for(int i=0;i<n;i++)
		scanf("%d",&perm[i]);
	for(int i=0;i<n;i++)
		scanf("%d",&target[i]);
	p[0]=1;
	for(int i=1;i<=n;i++)
		p[i]=p[i-1]*i;
}

vi repair(vi m)
{
	vi ret;
	int ind;
	for(int i=0;i<m.size();i++)
		if(m[i]==1)
		{
			ind=i;
			break;
		}
	for(int i=ind,j=0;j<n;j++,i=(i+1)%n)
		ret.pb(m[i]);
	return ret;
}

vi move(vi m,int ind)
{
	int b=m[ind];
	for(int i=ind;b;i=(i+1)%n,b--)
		swap(m[i],m[(i+1)%n]);
	return repair(m);
}

vi move_back(vi m,int ind)
{
	int b=ind;
	for(int i=0;i<n;i++)
		if(m[i]==ind)
		{
			ind=i;
			break;
		}
	for(int i=ind;b;i=(i-1+n)%n,b--)
		swap(m[i],m[(i-1+n)%n]);
	return repair(m);
}

void write(vi m)
{
	int ind=encode(m);
	if(prev[ind]==-1) return;
	write(move_back(m,prev[ind]));
	printf("%d\n",prev[ind]);
}

void bfs()
{
	prev[encode(perm)]=-1;
	level[encode(perm)]=1;
	pq.push(mp(encode(perm) , 0));
	while(!pq.empty())
	{
		tmp=pq.front();
		pq.pop();
		perm=decode(tmp.first);
		if(perm==target) { write(target); return; }
		for(int i=0;i<n;i++)
		{
			next=perm;
			next=move(next,i);
			int ind=encode(next);
			if(!level[ind])
			{
				level[ind]=tmp.second+1;
				prev[ind]=perm[i];
				pq.push(mp(ind,level[ind]));
			}
		}
	}
}

int main()
{
	init();
	bfs();
	return 0;
}
