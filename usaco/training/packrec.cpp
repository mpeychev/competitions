/*
PROG: packrec
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>

#define n 4

using namespace std;

typedef long long ll;

struct rect
{
       int a,b;
};

rect m[4];
bool used[4];

vector<int> tmp;
vector<vector<int> > perm;

int sol=500000;
vector< rect > v;

void permutation(int x)
{
	if(x==n)
	{
		perm.push_back(tmp);
		return;
	}
	for(int i=0;i<n;i++)
	 if(!used[i])
	 {
		used[i]=1;
		tmp[x]=i+1;
		permutation(x+1);
		
		tmp[x]=(i+1)*10;
		permutation(x+1);
		used[i]=0;
	 }
}

int max4(int a, int b, int c, int d)
{
	if(a>=b && a>=c && a>=d) return a;
	if(b>=a && b>=c && b>=d) return b;
	if(c>=a && c>=b && c>=d) return c;
	if(d>=a && d>=b && d>=c) return d;
}

int max3(int a,int b,int c)
{
	if(a>=b && a>=c) return a;
	if(b>=a && b>=c) return b;
	if(c>=a && c>=b) return c;
}

void ans(int g,int f)
{
	if(sol<g*f) return;
	if(g>f) swap(g,f);
	rect push;
	push.a=g; push.b=f;
	if(sol==g*f) v.push_back(push);
	else { sol=g*f; v.erase(v.begin(),v.end()); v.push_back(push); }
}

bool cmp(rect x,rect y)
{
     if(x.a<y.a) return true;
     return false;
}

int main()
{
    freopen("packrec.in","r",stdin);
    freopen("packrec.out","w",stdout);
    
    for(int i=0;i<n;i++) scanf("%d %d",&m[i].a,&m[i].b);
	for(int i=0;i<4;i++) tmp.push_back(0);
    permutation(0);
	
	for(int i=0;i<perm.size();i++)
	{
		int h[4];
		int w[4];
		for(int j=0;j<4;j++)
		{
			int ind;
			if(perm[i][j]%10==0)
			{
				ind=perm[i][j]/10-1;
				h[j]=m[ind].b;
				w[j]=m[ind].a;
			}
			else
			{
				ind=perm[i][j]-1;
				h[j]=m[ind].a;
				w[j]=m[ind].b;
			}
		}
		int ww,hh;
    
		hh = max4(h[0], h[1], h[2], h[3]);
		ww = w[0] + w[1] + w[2] + w[3];
		ans(ww, hh);
    
		hh = max3(h[0], h[1], h[2]) + h[3];
		ww = max(w[0] + w[1] + w[2], w[3]);
		ans(ww, hh);
    
		hh = max( max(h[0], h[1]) + h[3], h[2]);
		ww = max(w[0] + w[1], w[3]) + w[2];
		ans(ww, hh);
    
		hh = max3(h[0] + h[1], h[2], h[3]);
		ww = max(w[0], w[1]) + w[2] + w[3];
		ans(ww, hh);
    
		hh = max(h[0] + h[1], h[2] + h[3]);
		ww = max(w[0] + w[3], w[1] + w[2]);
		if (h[0] + h[2] > hh && w[0] + w[2] > ww) continue;
		if (h[1] + h[3] > hh && w[1] + w[3] > ww) continue;
		ans(ww, hh);
	}
	
	printf("%d\n",sol);
    sort(v.begin(),v.end(),cmp);
    printf("%d %d\n",v[0].a,v[0].b);
    for(int i=1;i<v.size();i++)
     if(v[i].a!=v[i-1].a && v[i].b!=v[i-1].b)
      printf("%d %d\n",v[i].a,v[i].b);
	
    return 0;
}
