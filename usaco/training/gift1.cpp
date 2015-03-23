/*
PROG: gift1
LANG: C++
ID: mompej951
*/
#include <fstream>
#include <string>
using namespace std;
struct data { string name; int s; } m[10];
int n;
int main()
{
    string name;
    int a,b;
    
    ifstream fin;
    fin.open("gift1.in");
    
    fin >> n;
    for(int i=0;i<n;i++) fin >> m[i].name;
    for(int i=0;i<n;i++)
    {
         fin >> name;
         fin >> a >> b;
         if(b==0) continue;
         for(int j=0;j<n;j++) if(m[j].name==name) { m[j].s=m[j].s-a+a%b; break; }
         for(int j=0;j<b;j++)
         {
                 fin >> name;
                 for(int k=0;k<n;k++) if(m[k].name==name) { m[k].s=m[k].s+a/b; break; }
         }
    }
    
    ofstream write;
    write.open("gift1.out");
    
    for(int i=0;i<n;i++) write << m[i].name << " " << m[i].s << endl;
    
    fin.close();
    return 0;
}
