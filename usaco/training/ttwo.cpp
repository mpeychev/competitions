/*
PROG: ttwo
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int sol=0;
int xc,yc,xf,yf,dirc=1,dirf=1;
int dx[]={0,-1,0,1};
int dy[]={-1,0,1,0};
string s[16];

bool ok(int x,int y)
{
    if(x<0 || x>=10 || y<0 || y>=10) return false;
    if(s[x][y]=='*') return false;
    return true;
}

int main()
{
    freopen("ttwo.in","r",stdin);
    freopen("ttwo.out","w",stdout);
    for(int i=0;i<10;i++) cin >> s[i];
    
    for(int i=0;i<10;i++)
     for(int j=0;j<10;j++)
     {
            if(s[i][j]=='F') { xf=i; yf=j; }
            if(s[i][j]=='C') { xc=i; yc=j; }
     }
    
    while(1)
    {
        if(sol>160000) { printf("0\n"); return 0; }
        sol++;
        if(!ok(xc+dx[dirc],yc+dy[dirc]) ) { dirc++; dirc%=4; }
        else { xc+=dx[dirc]; yc+=dy[dirc]; }
        if(!ok(xf+dx[dirf],yf+dy[dirf]) ) { dirf++; dirf%=4; }
        else { xf+=dx[dirf]; yf+=dy[dirf]; }
        if(xf==xc && yf==yc) { printf("%d\n",sol); return 0; }
    }
}
