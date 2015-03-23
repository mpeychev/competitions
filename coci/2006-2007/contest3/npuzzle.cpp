#include <stdio.h>

int sol;
char s[4][4];
char tab[4][4]=
{
    {'A','B','C','D'},
    {'E','F','G','H'},
    {'I','J','K','L'},
    {'M','N','O','.'},
};

int abs(int x)
{
    if(x<0) return -x;
    return x;
}

int dist(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2)+abs(y1-y2);
}

int find(char ch,int x,int y)
{
    for(int i=0;i<4;i++)
     for(int j=0;j<4;j++)
      if(tab[i][j]==ch)
       return dist(i,j,x,y);
}

int main()
{
    for(int i=0;i<4;i++) scanf("%s",&s[i]);
    for(int i=0;i<4;i++)
     for(int j=0;j<4;j++)
      if(s[i][j]!='.') sol+=find(s[i][j],i,j);
    
    printf("%d\n",sol);
    
    return 0;
}
