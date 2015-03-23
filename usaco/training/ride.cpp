/*
PROG: ride
LANG: C++
ID: mompej951
*/
#include <fstream>
#include <string>
using namespace std;
int main()
{
    ifstream fin;
    fin.open("ride.in");
    string a,b;
    fin >> a >> b;
    long long p1=1,p2=1;
    for(int i=0;i<a.size();i++) p1*=(a[i]-'A'+1);
    for(int i=0;i<b.size();i++) p2*=(b[i]-'A'+1);
    ofstream write;
    write.open("ride.out");
    if(p1%47==p2%47) write << "GO";
    else write << "STAY";
    write << endl;
    fin.close();
    return 0;
}
