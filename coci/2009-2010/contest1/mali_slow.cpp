#include <stdio.h>
#include <iostream>
#include <set>
using namespace std;

int n;
multiset<int> a,b;
multiset<int> ::iterator ita;
multiset<int> ::iterator itb;

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        
        a.insert(x);
        b.insert(y);
        int sol=0;
        itb=b.end();
        itb--;
        for(ita=a.begin(),itb=itb;ita!=a.end();ita++,itb--)
            if((*ita)+(*itb)>sol) sol=(*ita)+(*itb);
        printf("%d\n",sol);
    }
    
    return 0;
}
