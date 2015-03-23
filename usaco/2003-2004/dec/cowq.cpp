/*
  Source: usaco - 2003/2004 - dec
  Task: cowq
  KeyW: Kodirane & Dekodirane.
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

const int MAXB = (1 << 5);

char s[2][MAXB];
int pos;
bool bound[2][MAXB];
int c[MAXB][MAXB];
int dp[2][MAXB][MAXB];
bool ans[MAXB];
int ones;
bool fl1, fl2;
int f[MAXB][MAXB];

void initC()
{
    c[0][0] = 1;
    c[1][0] = 1; c[1][1] = 1;
    for(int i = 2; i < MAXB; i ++)
    {
        c[i][0] = 1;
        for(int j = 1; j <= i; j ++)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
}

void init()
{
    scanf("%s", &s[0]);
    scanf("%s", &s[1]);
    scanf("%d", &pos);

    if(strcmp(s[0], "0") == 0)
    {
        if(pos == 1)
        {
            printf("0\n");
            exit(0);
        }

        s[0][0] = '1';
        pos --;
    }

    for(int k = 0; k < 2; k ++)
    {
        for(int i = MAXB - 1, j = strlen(s[k]) - 1; j >= 0; i --, j --)
            bound[k][i] = s[k][j] - '0';
    }
}

void calc()
{
    for(int idx = 0; idx < 2; idx ++)
    {
        int cnt = 0;
        for(int i = 0; i < MAXB; i ++)
            if(bound[idx][i])
            {
                for(int j = 0; j <= MAXB - i - 1; j ++)
                    dp[idx][i - 1][cnt + j] = c[MAXB - i - 1][j];
                cnt ++;
            }
        if(idx) dp[idx][MAXB - 1][cnt] ++;
    }
}

int get(int idx, int br)
{
    if(f[idx][br] != -1)
        return f[idx][br];

    if(idx == MAXB - 1)
    {
        if(br >= 1) return 0;
        if(bound[0][idx]) return 1;
        return 0;
    }

    if(br == 0)
    {
        int u = 0;
        for(int i = idx; i < MAXB; i ++)
            if(bound[0][i])
            {
                u = 1;
                break;
            }
        f[idx][br] = u;
        return u;
    }

    if(bound[0][idx]) f[idx][br] = get(idx + 1, br - 1) + c[MAXB - idx - 1][br];
    else f[idx][br] = get(idx + 1, br);

    return f[idx][br];
}

void solve()
{
    memset(f, -1, sizeof(f));

    pos --;
    for(int i = 1; i < MAXB; i ++)
    {
        int sum = 0;
        for(int j = 0; j < MAXB; j ++)
            sum += dp[1][j][i] - dp[0][j][i];

        if(sum > pos)
        {
            ones = i;
            break;
        }

        pos -= sum;
    }

    for(int i = MAXB - strlen(s[1]); i < MAXB; i ++)
    {
        if(!fl1 && bound[0][i])
        {
            ans[i] = 1;
            continue;
        }

        if(!fl2 && !bound[1][i]) continue;

        if(fl1 && fl2)
        {
            if(c[MAXB - i - 1][ones] <= pos)
            {
                pos -= c[MAXB - i - 1][ones];
                ans[i] = 1;
                ones --;
            }
            continue;
        }

        int r2, r1 = 0;

        r2 = c[MAXB - i - 1][ones];

        if(!fl1) r1 = get(i, ones);

        if(r2 - r1 <= pos)
        {
            pos -= (r2 - r1);
            ans[i] = 1;
            ones --;
            fl1 = true;
        }
        else fl2 = true;
    }
}

void write()
{
    bool print = false;
    for(int i = 0; i < MAXB; i ++)
        if(ans[i] || print)
        {
            printf("%d", ans[i]);
            print = true;
        }
    if(!print) printf("0");
    printf("\n");
}

int main()
{
    init();
    initC();
    calc();
    solve();
    write();

    return 0;
}
