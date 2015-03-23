/*
  Source: baoi-2002
  Task: Robots
  KeyW: dp + coordinates hashing
*/
#include <stdio.h>
#include <string.h>

const int MAXR = (1<<4);
const int SIZE = (1<<7);
const int MAXA = (1<<6);

const int movex[] = {1,0,-1,0};
const int movey[] = {0,1,0,-1};

int r,c,n,d;
char com;
int dp[MAXR][SIZE][SIZE][4];
int posx[MAXR],posy[MAXR];
int tx,ty,f,g;

void init()
{
    scanf("%d",&r);
    for(int i=0;i<r;i++)
    {
        scanf("%d %d %d %d\n",&posx[i],&posy[i],&c,&n);

        memset(dp[i],-1,sizeof(dp[i]));
        memset(dp[10],-1,sizeof(dp[10]));

        dp[i][50][50][c/90]=0;
        for(int j=0;j<n;j++)
        {
            scanf("%c\n",&com);
            if(com=='S')
            {
                for(int k=0;k<=100;k++)
                    for(int h=0;h<=100;h++)
                        for(int dir=0;dir<4;dir++)
                            if(dp[i][k][h][dir]!=-1)
                            {
                                // don't use this command
                                if(dp[10][k][h][dir]==-1 || dp[10][k][h][dir]>dp[i][k][h][dir]+1)
                                    dp[10][k][h][dir]=dp[i][k][h][dir]+1;
                                // use this command
                                if(dp[10][k+movex[dir]][h+movey[dir]][dir]==-1 || dp[10][k+movex[dir]][h+movey[dir]][dir]>dp[i][k][h][dir])
                                    dp[10][k+movex[dir]][h+movey[dir]][dir]=dp[i][k][h][dir];
                            }
            }
            else
            {
                scanf("%d\n",&d);
                d/=90;

                for(int k=0;k<=100;k++)
                    for(int h=0;h<=100;h++)
                        for(int dir=0;dir<4;dir++)
                            if(dp[i][k][h][dir]!=-1)
                            {
                                // don't use this command
                                if(dp[10][k][h][dir]==-1 || dp[10][k][h][dir]>dp[i][k][h][dir]+1)
                                    dp[10][k][h][dir]=dp[i][k][h][dir]+1;
                                // use this command
                                if(dp[10][k][h][(dir+d)%4]==-1 || dp[10][k][h][(dir+d)%4]>dp[i][k][h][dir])
                                    dp[10][k][h][(dir+d)%4]=dp[i][k][h][dir];
                            }
            }

            memcpy(dp[i],dp[10],sizeof(dp[10]));
            memset(dp[10],-1,sizeof(dp[10]));
        }
    }
}

inline int get(int rob,int xx,int yy)
{
    int ret=MAXA;
    for(int i=0;i<4;i++)
        if(dp[rob][xx][yy][i]!=-1 && dp[rob][xx][yy][i]<ret)
            ret=dp[rob][xx][yy][i];
    return ret;
}

void solve()
{
    bool fl=false,valid;

    int ans;
    int solx,soly;
    int sum;

    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            if(get(0,i,j)!=MAXA)
            {
                valid=true;
                sum=get(0,i,j);

                f=50-posx[0];
                g=50-posy[0];
                int x=i-f;
                int y=j-g;

                for(int w=1;w<r;w++)
                {
                    int ff=50-posx[w];
                    int gg=50-posy[w];
                    int id1=x+ff;
                    int id2=y+gg;

                    if(id1<0 || id1>100 || id2<0 || id2>100 || get(w,id1,id2)==MAXA) { valid=false; break; }
                    sum+=get(w,id1,id2);
                }

                if(valid)
                {
                    if(fl)
                    {
                        if(ans>sum) { ans=sum; solx=x; soly=y; }
                    }
                    else
                    {
                        fl=true;
                        ans=sum; solx=x; soly=y;
                    }
                }
            }
    if(fl) printf("%d\n%d %d\n",ans,solx,soly);
    else printf("-1\n");
}

int main()
{
    init();
    solve();

    return 0;
}
