#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

typedef vector<int> vi;
typedef vector< vi > Grid;

int n,k,m;
char s[8];
Grid tmp;
vector< Grid > saves;

void Init()
{
	scanf("%d %d %d\n",&n,&k,&m);
	
	tmp.resize(n);
	for(int i=0;i<n;i++)
		tmp[i].resize(n);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			tmp[i][j] = 1;
}

void Write()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(j) printf(" ");
			printf("%d",tmp[i][j]);
		}
		printf("\n");
	}
}

void Paint(int col,int sx,int sy,int ex,int ey)
{
	//cout << col << " " << sx << " " << sy << " " << ex << " " << ey << endl;
	
	for(int i=sx;i<=ex;i++)
		for(int j=sy;j<=ey;j++)
			if((i-sx+j-sy)%2 == 0)
				tmp[i][j] = col;
	
	//Write();
	//cout << endl;
}

void Solve()
{
	for(int i=0;i<m;i++)
	{
		scanf("%s",&s);
		if(s[0] == 'P')
		{
			int c,x1,y1,x2,y2;
			scanf("%d %d %d %d %d\n",&c,&x1,&y1,&x2,&y2);
			Paint(c,x1,y1,x2,y2);
		}
		else if(s[0] == 'S') saves.pb(tmp);
		else
		{
			int x;
			scanf("%d\n",&x);
			x--;
			tmp = saves[x];
		}
	}
}

int main()
{
	Init();
	Solve();
	Write();
	
	return 0;
}
