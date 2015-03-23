/*
PROG: transform
LANG: C++
ID: mompej951
*/
#include <fstream>
using namespace std;

ifstream in;
ofstream out;

int n;
char a[16][16],b[16][16],c[16][16],d[16][16];

bool same()
{
     for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
       if(b[i][j]!=c[i][j]) return false;
     return true;
}

void cpy()
{
     for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
       c[i][j]=d[i][j];
}

int main()
{
    in.open("transform.in");
    out.open("transform.out");
    
    in >> n;
    in.get();
    for(int i=0;i<n;i++)
    {
            for(int j=0;j<n;j++) in.get(a[i][j]);
            in.get();
    }
    
    for(int i=0;i<n;i++)
    {
            for(int j=0;j<n;j++) in.get(b[i][j]);
            in.get();
    }
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      c[i][j]=a[n-1-j][i];
    if(same()) { out << "1\n"; return 0; }
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      c[i][j]=a[n-1-i][n-1-j];
    if(same()) { out << "2\n"; return 0; }
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      c[i][j]=a[j][n-1-i];
    if(same()) { out << "3\n"; return 0; }
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
     {
      c[i][j]=a[i][n-1-j];
      d[i][j]=c[i][j];
     }
    if(same()) { out << "4\n"; return 0; }
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      c[i][j]=d[n-1-j][i];
    if(same()) { out << "5\n"; return 0; }
    
    cpy();
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      c[i][j]=d[n-1-i][n-1-j];
    if(same()) { out << "5\n"; return 0; }
    
    cpy();
    
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      c[i][j]=d[j][n-1-i];
    if(same()) { out << "5\n"; return 0; }
    
    bool fl=true;
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      if(b[i][j]!=a[i][j]) fl=false;
    if(fl) { out << "6\n"; return 0; }
    
    out << "7\n";

    return 0;
}
