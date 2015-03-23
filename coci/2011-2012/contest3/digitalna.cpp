#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

const string s1 = "BLJTV1";
const string s2 = "BLJTV2";

int n;
string s[128];

int find(string t)
{
    for(int i = 0; i < n; i ++)
        if(s[i] == t)
            return i;
    return -1;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++)
        cin >> s[i];
    
    int idx;
    idx = find(s1);
    
    for(int i = 1; i <= idx; i ++)
        printf("1");
    for(int i = 1; i <= idx; i ++)
        printf("4");
    
    for(int i = idx; i >= 1; i --)
        s[i] = s[i - 1];
    s[0] = s1;
    
//    for(int i = 0; i < n; i ++)
//        cout << s[i] << endl;
    
    idx = find(s2);
    
    for(int i = 1; i <= idx; i ++)
        printf("1");
    for(int i = 2; i <= idx; i ++)
        printf("4");
    
    printf("\n");
    
    return 0;
}
