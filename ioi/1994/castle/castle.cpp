#include <stdio.h>
#include <iostream>
using namespace std;

struct pos
{
    int o;
    
    bool used;
    bool dir[4];
    int nom;
};

int m,n;
pos a[64][64];
int size[64*64];
int num,sz=-1,br;

void dfs(int x,int y)
{
//     printf("%d %d\n",x,y);
     br++;
     a[x][y].used=1;
     a[x][y].nom=num;
     if(a[x][y].dir[0] && !a[x][y+1].used) dfs(x,y+1);
     if(a[x][y].dir[1] && !a[x+1][y].used) dfs(x+1,y);
     if(a[x][y].dir[2] && !a[x][y-1].used) dfs(x,y-1);
     if(a[x][y].dir[3] && !a[x-1][y].used) dfs(x-1,y);
}

int main()
{
    scanf("%d %d",&m,&n);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
     {
             scanf("%d",&a[i][j].o);
             a[i][j].used=0;
             for(int k=0;k<4;k++) a[i][j].dir[k]=1;
             if(a[i][j].o>=8) { a[i][j].o-=8; a[i][j].dir[1]=0; }
             if(a[i][j].o>=4) { a[i][j].o-=4; a[i][j].dir[0]=0; }
             if(a[i][j].o>=2) { a[i][j].o-=2; a[i][j].dir[3]=0; }
             if(a[i][j].o>=1) { a[i][j].o-=1; a[i][j].dir[2]=0; }
     }
    /*
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      printf("%d %d %d %d %d %d %d\n",i,j,a[i][j].used,a[i][j].dir[0],a[i][j].dir[1],a[i][j].dir[2],a[i][j].dir[3]);
    */
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
      if(a[i][j].used==0)
      {
                         num++;
                         br=0;
                         dfs(i,j);
                         //printf("%d %d %d\n",i,j,num);
                         if(br>sz) sz=br;
                         size[num]=br;
      }
    
    printf("%d\n%d\n",num,sz);
    
    int solx,soly,direction;
    int mx=-1;
    for(int i=n;i>=1;i--)
     for(int j=1;j<=m;j++)
     {
             if(a[i][j].dir[3]==0 && a[i-1][j].nom>0 && a[i-1][j].nom!=a[i][j].nom)
             {
                                  int cnt=size[ a[i][j].nom ]+size[ a[i-1][j].nom ];
                                  if(cnt>mx) { mx=cnt; solx=i; soly=j; direction=3; }
                                  if(cnt==mx && soly>j) { mx=cnt; solx=i; soly=j; direction=3; }
             }
             if(a[i][j].dir[0]==0 && a[i][j+1].nom>0 && a[i][j+1].nom!=a[i][j].nom)
             {
                                  int cnt=size[ a[i][j].nom ]+size[ a[i][j+1].nom ];
                                  if(cnt>mx) { mx=cnt; solx=i; soly=j; direction=0; }
                                  if(cnt==mx && soly>j) { mx=cnt; solx=i; soly=j; direction=0; }
             }
     }
    
    printf("%d\n%d %d ",mx,solx,soly);
    switch(direction)
    {
                     case 0: printf("E\n"); break;
                     case 3: printf("N\n"); break;
    }
    
    
    return 0;
}
