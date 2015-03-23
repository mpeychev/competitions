/*
PROG: friday
LANG: C++
ID: mompej951
*/
#include <fstream>
using namespace std;
int n;
int pon,vt,sr,chetv,pet,syb,ned;
int m[]={6,2,2,5,0,3,5,1,4,6,2,4};
bool vis(int g)
{
     if((g%4==0 && g%100!=0) || g%400==0) return true;
     return false;
}
int main()
{
    ifstream fin;
    fin.open("friday.in");
    fin >> n;
    ofstream write;
    write.open("friday.out");
    pon=1; vt=3; sr=1; chetv=2; pet=2; syb=2; ned=1;
    for(int i=1901;i<=1900+n-1;i++)
    {
            if(vis(i-1)) { m[0]=(m[0]+2)%7; m[1]=(m[1]+2)%7; }
            else { m[0]=(m[0]+1)%7; m[1]=(m[1]+1)%7; }
            if(vis(i)) for(int j=2;j<=11;j++) m[j]=(m[j]+2)%7;
            else for(int j=2;j<=11;j++) m[j]=(m[j]+1)%7;
            for(int j=0;j<=11;j++)
            {
             //write << m[j] << " ";
             if(m[j]==0) ned++;
             else if(m[j]==1) pon++;
             else if(m[j]==2) vt++;
             else if(m[j]==3) sr++;
             else if(m[j]==4) chetv++;
             else if(m[j]==5) pet++;
             else if(m[j]==6) syb++;
            }
            //write << "\n";
    }
    write << syb << " " << ned << " " << pon << " " << vt << " " << sr << " " << chetv << " " << pet << endl;
    fin.close();
    return 0;
}
