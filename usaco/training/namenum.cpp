/*
PROG: namenum
LANG: C++
ID: mompej951
*/
#include <fstream>
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;

ifstream fin,kkk;
ofstream fout;

string let[16][4]={
    {"","",""}, // 0
    {"","",""}, // 1
    {"A","B","C"}, // 2
    {"D","E","F"}, // 3
    {"G","H","I"}, // 4
    {"J","K","L"}, // 5
    {"M","N","O"}, // 6
    {"P","R","S"}, // 7
    {"T","U","V"}, // 8
    {"W","X","Y"} // 9
};
string n,dict;
bool fl=false;
map<string,bool> m,whole;

void rec(string tmp,int pos)
{
    if(!m[tmp]) return;
    if(pos==n.size())
    {
        if(whole[tmp]) { fl=true; fout << tmp << endl; }
        return;
    }
    rec(tmp+let[n[pos]-'0'][0],pos+1);
    rec(tmp+let[n[pos]-'0'][1],pos+1);
    rec(tmp+let[n[pos]-'0'][2],pos+1);
}

int main()
{
    kkk.open("dict.txt");
    fin.open("namenum.in");
    fout.open("namenum.out");
    
    while(kkk >> dict)
    {
        string r;
        for(int i=0;i<dict.size();i++)
        {
            r.push_back(dict[i]);
            m[r]=1;
        }
        whole[dict]=1;
    }
    
    fin >> n;
    m[""]=1;
    rec("",0);
    
    if(!fl) fout << "NONE\n";

    return 0;
}
