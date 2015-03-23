/*
  Source: coci - 2010/2011 - contest2
  Task: Igra
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

#define pb push_back
#define mp make_pair
#define let first
#define ind second

using namespace std;

typedef pair<char , int> Type;

const int MAXN = 100010;

int n;
char s[MAXN];
bool Used[MAXN];
Type data[MAXN];
string Slavko,Mirko;

bool cmp(Type a,Type b)
{
    if(a.let<b.let) return true;
    if(a.let>b.let) return false;
    return a.ind>b.ind;
}

void Init()
{
    scanf("%d\n",&n);
    scanf("%s",&s);

    for(int i=0;i<n;i++)
        data[i]=mp(s[i],i);
    sort(data,data+n,cmp);
}

void BuildWords()
{
    Mirko.pb(s[n-1]);
    Used[n-1]=1;
    int r = n-2;

    for(int i=0;i<n;i++)
    {
        if(Used[data[i].ind]) continue;

        Slavko.pb(data[i].let);
        Used[data[i].ind] = 1;

        while(r>=0 && Used[r]) r--;
        if(r>=0) { Mirko.pb(s[r]); Used[r]=1; }
        r--;
    }
}

void Write()
{
    if(Slavko<Mirko) printf("DA\n");
    else printf("NE\n");
    cout << Slavko << endl;
}

int main()
{
    Init();
    BuildWords();
    Write();

    return 0;
}
