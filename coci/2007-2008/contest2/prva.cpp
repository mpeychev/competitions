#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#define pb push_back

using namespace std;

int r, c;
char s[32][32];
vector< string > words;

void read() {
    scanf("%d %d\n", &r, &c);
    for(int i = 0; i < r; i ++)
        scanf("%s", &s[i]);
}

bool blocked(int x, int y) {
    if(x < 0 || x >= r || y < 0 || y >= c) return true;
    return s[x][y] == '#';
}

void solve() {
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(s[i][j] != '#')
            {
                if(blocked(i, j - 1))
                {
                    string tmp;
                    for(int k = j; k < c; k ++)
                    {
                        if(s[i][k] == '#') break;
                        tmp.pb(s[i][k]);
                    }
                    if(tmp.size() >= 2) words.pb(tmp);
                }

                if(blocked(i - 1, j))
                {
                    string tmp;
                    for(int k = i; k < r; k ++)
                    {
                        if(s[k][j] == '#') break;
                        tmp.pb(s[k][j]);
                    }
                    if(tmp.size() >= 2) words.pb(tmp);
                }
            }

    string ans = words[0];
    for(int i = 1; i < words.size(); i ++)
        if(ans > words[i])
            ans = words[i];

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
