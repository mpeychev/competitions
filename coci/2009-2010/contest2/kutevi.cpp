#include <stdio.h>
#include <queue>

int N,K;
int alpha[16],query;
bool able[512];

void bfs()
{
    std::queue<int> q;
    q.push(0);
    able[0]=1;
    
    while(!q.empty())
    {
        int angle=q.front();
        q.pop();
        for(int i=0;i<N;i++)
            if(!able[(angle+alpha[i])%360])
            {
                able[(angle+alpha[i])%360]=1;
                q.push((angle+alpha[i])%360);
            }
    }
    
    able[360]=1;
}

int main()
{
    scanf("%d %d",&N,&K);
    for(int i=0;i<N;i++)
        scanf("%d",&alpha[i]);
    bfs();
    for(int i=0;i<K;i++)
    {
        scanf("%d",&query);
        
        bool ans=false;
        for(int j=query;j<=360;j++)
            if(able[j] && able[j-query])
            {
                ans=true;
                break;
            }
        if(ans) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
